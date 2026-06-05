#pragma once

#include <vector>
#include <memory>
#include <string>
#include <functional>

#define HOG_ARCHIVE_MAGIC		0xDEADBEAF

#define HOG_COMPRESSION_METHOD_NONE			0
#define HOG_COMPRESSION_METHOD_ZLIB			1
#define HOG_COMPRESSION_METHOD_OODLE		2

#define HOG_ENCRYPTION_METHOD_NONE			0
#define HOG_ENCRYPTION_METHOD_AES			1

namespace Hog
{
	/**
	 * These are files that can contain or embed other files in a virtual file system
	 * that you can mount at run-time and then have access to the data.
	 * 
	 * The binary format is as follows:
	 *   - header
	 *   - index (array of file entries)
	 *   - string table (array of null-terminated strings)
	 *   - pad (zeros)
	 *   - data blocks
	 * 
	 * Each data block will be on a specified alignment boundary.
	 * Zeros are used to pad the space between data blocks.
	 */
	class Archive
	{
	public:
		Archive();
		virtual ~Archive();

		/**
		 * Open a hog file and then be ready for subsequent data requests.
		 * The only work performed here is to load the header and index into memory.
		 * Once that's done, the caller can request any virtual file's data using
		 * the @ref GetVirtualFileData method.
		 * 
		 * @param[in] hogFilePath Fully qualified path to the hog file on disk.
		 * @return True is returned on success, false on failure.
		 */
		bool Mount(const std::string& hogFilePath);
		
		/**
		 * Serialize this hog archive's data to disk.  Note that the index and
		 * data blocks are always written in an order sorted by virtual file path.
		 * This ensures determinism in the result, provided the data blocks are
		 * themselves deterministically generated.
		 * 
		 * @param[in] hogFilePath Fully qualified path to where the hog file should be written on disk.
		 * @param[in] numThreads Use this many threads to expedite the process.
		 * @param[in] progressFunc This gets called as the data blocks are written so that the caller can track progress.
		 */
		bool Generate(const std::string& hogFilePath, int numThreads, std::function<void(float)> progressFunc);

		/**
		 * Look-up the given file's entry in our loaded index, then use that to
		 * retrieve the file's data.  Decryption and/or decompression is performed
		 * here if necessary.  Raw file data is cached so that subsequent requests
		 * do not require any decryption or decompression.
		 */
		bool GetVirtualFileData(const std::string& virtualFilePath, std::vector<uint8_t>& fileData);

		/**
		 * Remove the given file from this archive's index.  Note that this does
		 * not delete the embedded file's data.  Rather, the data will be omitted
		 * when next the archive is serialized to disk.
		 * 
		 * @param[in] virtualFilePath A file to delete by this name/path is looked for within the index.
		 * @return True is returned on success, false on failure.
		 */
		bool DeleteVirtualFile(const std::string& virtualFilePath);

		/**
		 * Add the given file to this archive's index.  Note that this does not add
		 * embedded file data.  Rather, the data will be added when next the archive
		 * is serailized to disk.
		 * 
		 * @param[in] virtualFilePath The file will be known by this name/path within this archive.
		 * @param[in] physicalFilePath This is a fully-qualified path to the file on disk that we'd like to embed in the archive.
		 * @return True is returned on success, false on failure.
		 */
		bool AddVirtualFile(const std::string& virtualFilePath, const std::string& physicalFilePath);

	protected:

		struct Header
		{
			uint32_t magic;							/// This helps us detect the need for byte-swapping.
			uint32_t version;						/// This gets bumped with each file format change.
			uint64_t dataBlocksOffset;				/// Byte offset from start of file to the data blocks region.
			uint64_t dataBlockSize;					/// Size in bytes of the data blocks region.
			uint64_t dataBlockAlign;				/// All data block offsets will be multiples of this.
			uint32_t numFileEntries;				/// The number of file entries in the index.  Also, the number of data blocks.
			uint16_t stringTableCompressionMethod;	/// The method used to compress the string table.
			uint16_t stringTableEncryptionMethod;	/// The method used to encrypted the string table.
		};

		struct FileEntry
		{
			uint32_t pathOffset;					/// Byte offset from the start of the string table to this entry's path string.
			uint64_t dataBlockOffset;				/// Byte offset from the start of the data block region to this entry's data block.
			uint16_t dataBlockComperssionMethod;	/// The method used to compress the data block.
			uint16_t dataBlockEncryptionMethod;		/// The method used to encrypted the data block.
		};

		class VirtualFile
		{
		public:
			VirtualFile();
			virtual ~VirtualFile();

			std::vector<uint8_t> fileDataCache;		/// This gets move-temped into the caller's array unless the cache can persist.
		};

		class EmbeddedFile : public VirtualFile
		{
		public:
			EmbeddedFile();
			virtual ~EmbeddedFile();
			
			FileEntry fileEntry;
		};

		class ExternalFileEntry : public VirtualFile
		{
		public:
			ExternalFileEntry();
			virtual ~ExternalFileEntry();

			std::string physicalFilePath;
		};

		Header header;

		std::vector<std::shared_ptr<VirtualFile>> virtualFileArray;
	};
}
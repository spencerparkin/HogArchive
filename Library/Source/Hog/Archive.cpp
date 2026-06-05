#include "Archive.h"

using namespace Hog;

//---------------------------------- Archive ----------------------------------

Archive::Archive()
{
	::memset(&this->header, 0, sizeof(Header));
}

/*virtual*/ Archive::~Archive()
{
}

bool Archive::Mount(const std::string& hogFilePath)
{
	return false;
}

bool Archive::Generate(const std::string& hogFilePath, int numThreads, std::function<void(float)> progressFunc)
{
	return false;
}

bool Archive::GetVirtualFileData(const std::string& virtualFilePath, std::vector<uint8_t>& fileData)
{
	return false;
}

bool Archive::DeleteVirtualFile(const std::string& virtualFilePath)
{
	return false;
}

bool Archive::AddVirtualFile(const std::string& virtualFilePath, const std::string& physicalFilePath)
{
	return false;
}

//---------------------------------- Archive::VirtualFile ----------------------------------

Archive::VirtualFile::VirtualFile()
{
}

/*virtual*/ Archive::VirtualFile::~VirtualFile()
{
}

//---------------------------------- Archive::EmbeddedFile ----------------------------------

Archive::EmbeddedFile::EmbeddedFile()
{
	::memset(&this->fileEntry, 0, sizeof(FileEntry));
}

/*virtual*/ Archive::EmbeddedFile::~EmbeddedFile()
{
}

//---------------------------------- Archive::ExternalFileEntry ----------------------------------

Archive::ExternalFileEntry::ExternalFileEntry()
{
}

/*virtual*/ Archive::ExternalFileEntry::~ExternalFileEntry()
{
}
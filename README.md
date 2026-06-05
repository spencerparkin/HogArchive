# HogArchive

Hog files are an archive format supporting encryption and compression.  Such files can be mounted, at which point, the embedded files become available through what you might call a virtual file system.

One of the primary features is a simple reading and writing API.  It should be just as easy to generate a hog file as it is to read its contents.  In fact, the process of generating a hog file is to create and mount the vacuous case -- an empty hog file.  You then add files to the index.  The index is a list of file entries that either point to an embedded file in the hog data section or point to external files on disk.  When you're ready, just serialize the hog file to disk.  Removing files from the hog is just as easy.  When the hog gets reserialized, certain of the embedded files are simply omitted.

Note also that when hog files are written, the contents are always ordered lexographically based on the virtual file paths.  This way, as long as the embedded content is deterministic, hog files will be likewise.  Determinism is an important feature in many patching schemes.

Another feature is that the tool-time and run-time support for hog files is the same.  That is, a tool or engine that reads or writes hog files links against the hog archive format C++ library.  This library could distribute as source code instead of binaries in order to support different platforms.  All byte-swapping (to handle little-endian or big-endian) will be taken care of at a low-level against which the higher-level binary format parsing code is insulated.  The need for byte-swapping can be easily detected when reading the hog file header.

Embedded files can be compressed, encrypted, compressed and encrypted, or neither, on an individual basis.  The index can also be compressed and/or encrypted.  The compression and encryption methods can very in all cases, but typically would be uniform throughout.  Files initially added to the index are neither compressed nor encrypted simply because they're external to the hog file until serialization occurs.

A GUI tool is also provided that can be used to open (mount) hog files to display their contents.  You can then use the GUI to add or remove files to/from the index and then regenerate the archive.  This is in stark contrast to abismal archiving formats such as Unreal's PAK or UCAS/UTOC.  However, the relative run-time performance of hog files versus PAK, for example, remains to be seen.

Admittedly, the name "hog file" is stolen from a file format used for an identical purpose from many, many years ago.  It was a proprierty, in-house format, but the format here has little to no resemblance to that old format; if for no other reason, because I don't remember at all what that old format was.  What I've come up with here is all new, even if not in any way novel.

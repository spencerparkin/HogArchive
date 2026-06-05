# CMakeLists.txt for HogArchive C++ library.

set(HOG_ARCHIVE_SOURCES
	Source/Hog/Archive.cpp
	Source/Hog/Archive.h
)

add_library(HogArchive STATIC ${HOG_ARCHIVE_SOURCES})

target_include_directories(HogArchive PUBLIC Source)
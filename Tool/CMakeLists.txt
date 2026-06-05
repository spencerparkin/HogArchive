# CMakeLists.txt for Hog Archive Tool.

set(HOG_ARCHIVE_TOOL_SOURCE
	Source/App.cpp
	Source/App.h
	Source/Frame.cpp
	Source/Frame.h
)

add_executable(HogArchiveTool WIN32
	${HOG_ARCHIVE_TOOL_SOURCE}
	${CMAKE_CURRENT_SOURCE_DIR}/wx_dpi_aware_pmv2.manifest
)

target_compile_definitions(HogArchiveTool PUBLIC
	__WXMSW__
	_UNICODE
)

target_link_libraries(HogArchiveTool
	wx::core
	wx::base
	HogArchive
)
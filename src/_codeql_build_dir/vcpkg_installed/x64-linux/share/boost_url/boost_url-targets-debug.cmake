#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Boost::url" for configuration "Debug"
set_property(TARGET Boost::url APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Boost::url PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/libboost_url.a"
  )

list(APPEND _cmake_import_check_targets Boost::url )
list(APPEND _cmake_import_check_files_for_Boost::url "${_IMPORT_PREFIX}/debug/lib/libboost_url.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

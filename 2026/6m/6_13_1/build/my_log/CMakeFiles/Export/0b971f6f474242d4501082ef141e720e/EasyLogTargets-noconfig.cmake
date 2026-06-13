#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "EasyLog::EasyLog" for configuration ""
set_property(TARGET EasyLog::EasyLog APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(EasyLog::EasyLog PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libEasyLog.a"
  )

list(APPEND _cmake_import_check_targets EasyLog::EasyLog )
list(APPEND _cmake_import_check_files_for_EasyLog::EasyLog "${_IMPORT_PREFIX}/lib/libEasyLog.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

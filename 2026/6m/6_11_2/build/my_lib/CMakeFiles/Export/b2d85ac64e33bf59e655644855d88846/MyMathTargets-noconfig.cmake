#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "MyMath::MyMath" for configuration ""
set_property(TARGET MyMath::MyMath APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(MyMath::MyMath PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libMyMath.so.1.2.3"
  IMPORTED_SONAME_NOCONFIG "libMyMath.so.20"
  )

list(APPEND _cmake_import_check_targets MyMath::MyMath )
list(APPEND _cmake_import_check_files_for_MyMath::MyMath "${_IMPORT_PREFIX}/lib/libMyMath.so.1.2.3" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

file(GLOB SRC_LISTS "src/*.cpp")

add_library(EasyLog STATIC ${SRC_LISTS})

target_include_directories(EasyLog
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  INTERFACE
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(EasyLog PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

include(GNUInstallDirs)

install(TARGETS EasyLog
  EXPORT EasyLogTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/easylog
  FILES_MATCHING PATTERN "*.h"
)

export(EXPORT EasyLogTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/EasyLogTargets.cmake
)

install(EXPORT EasyLogTargets
  FILE EasyLogTargets.cmake
  NAMESPACE EasyLog::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/EasyLog
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/EasyLogConfig.cmake
  INSTALL_DESTINATION "lib/cmake/EasyLog"
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/EasyLogConfig.cmake
  DESTINATION "lib/cmake/EasyLog"
)
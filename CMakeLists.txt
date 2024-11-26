cmake_minimum_required(VERSION 3.10)

# ccmake can control these variables, but need to be set before project()
set(CMAKE_BUILD_TYPE
    Release
    CACHE STRING "Build type")
set(CMAKE_CXX_COMPILER
    /usr/bin/c++
    CACHE FILEPATH "C++ compiler")
set(CMAKE_CXX_FLAGS
    "-Wall -Wextra -Wpedantic -Werror"
    CACHE STRING "Compiler flags")
set(CMAKE_CXX_STANDARD
    20
    CACHE STRING "C++ standard")
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "Export compile commands")
option(BUILD_TESTING "Enable building tests" ON)

project(
  mylib
  VERSION 1.2.3
  DESCRIPTION "A test of cmake utilities"
  HOMEPAGE_URL "https://github.com/HuaTsai/mylib"
  LANGUAGES CXX)

# Messages
message(STATUS "Message Categories:")
message(STATUS "This is a STATUS message")
message(WARNING "This is a WARNING message")
message(AUTHOR_WARNING "This is an AUTHOR_WARNING message")
message(
  STATUS "SEND_ERROR message will output error, and therefore is not shown here"
)
message(
  STATUS
    "FATAL_ERROR message will stop the build, and therefore is not shown here")
set(CMAKE_WARN_DEPRECATED true)
message(
  DEPRECATION
    "This is an DEPRECATION message (enabled by CMAKE_WARN_DEPRECATED)")

# Variables
message(STATUS "Package Information:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Major Version: ${PROJECT_VERSION_MAJOR}")
message(STATUS "  Minor Version: ${PROJECT_VERSION_MINOR}")
message(STATUS "  Patch Version: ${PROJECT_VERSION_PATCH}")
message(STATUS "  Description: ${PROJECT_DESCRIPTION}")
message(STATUS "  Homepage URL: ${PROJECT_HOMEPAGE_URL}\n")

message(STATUS "Common Variables:")
message(STATUS "  CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "  CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "  CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "  CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "  PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "  PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}\n")

message(STATUS "System Information:")
message(STATUS "  CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "  CMAKE_SYSTEM_VERSION: ${CMAKE_SYSTEM_VERSION}")
message(STATUS "  CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "  CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
message(STATUS "  CMAKE_CXX_COMPILER_ABI: ${CMAKE_CXX_COMPILER_ABI}")

# Check
message(CHECK_START "Find config/myconfig.h.in") # After CMake 3.17
if(EXISTS ${CMAKE_SOURCE_DIR}/config/myconfig.h.in)
  message(CHECK_PASS "found")
else()
  message(CHECK_FAIL "not found")
endif()

# Generated header
set(CONFIG_OUTPUT_DIR ${CMAKE_BINARY_DIR}/generated)
configure_file(config/myconfig.h.in ${CONFIG_OUTPUT_DIR}/myconfig.h)

# Build
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

add_library(mylib SHARED src/myadd.cc src/myminus.cc)
target_include_directories(
  mylib PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # Build library
               $<INSTALL_INTERFACE:include> # Expose the header location
)

add_executable(mymain src/mymain.cc)
target_include_directories(
  mymain PRIVATE # No need to expose how it is built
                 ${CONFIG_OUTPUT_DIR} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mymain Eigen3::Eigen ${Boost_LIBRARIES})

# Ctest testing
enable_testing()
if(BUILD_TESTING)
  message(STATUS "Enable building tests")
  include(GoogleTest)
  file(GLOB_RECURSE ALL_TESTS "tests/*.cc")
  foreach(FILE_PATH ${ALL_TESTS})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME_WE)
    add_executable(${FILE_NAME} ${FILE_PATH})
    target_link_libraries(${FILE_NAME} mylib gtest gtest_main)
    gtest_discover_tests(${FILE_NAME})
  endforeach(FILE_PATH)
endif()

# Install
install(
  TARGETS mylib
  EXPORT ${PROJECT_NAME}Targets # For cmake config
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES
  DESTINATION include # Tell the users where the headers are
)

install(TARGETS mymain RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)

install(FILES "${CONFIG_OUTPUT_DIR}/myconfig.h" DESTINATION include)

# Cmake config
include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

install(FILES "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME})

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION lib/cmake/${PROJECT_NAME})

# Man files
file(GLOB RST_FILES docs/*.rst)
foreach(RST_FILE ${RST_FILES})
  get_filename_component(BASE_NAME ${RST_FILE} NAME_WE)
  string(REGEX MATCH "\\.[1-9]\\." SECTION_MATCH ${RST_FILE})
  if(NOT SECTION_MATCH)
    message(FATAL_ERROR "Invalid man section in file: ${RST_FILE}")
  endif()
  string(SUBSTRING ${SECTION_MATCH} 1 1 SECTION)
  set(MAN_DIRECTORY ${CMAKE_BINARY_DIR}/man/man${SECTION})
  if(NOT EXISTS ${MAN_DIRECTORY})
    file(MAKE_DIRECTORY ${MAN_DIRECTORY})
  endif()
  set(MAN_FILE ${MAN_DIRECTORY}/${BASE_NAME}.${SECTION})
  set(MAN_FILE_GZ ${MAN_FILE}.gz)
  add_custom_command(
    OUTPUT ${MAN_FILE_GZ}
    COMMAND rst2man ${RST_FILE} ${MAN_FILE}
    COMMAND gzip -n ${MAN_FILE}
    COMMENT "Generating ${MAN_FILE_GZ} man page"
    VERBATIM)
  add_custom_target(gen_${BASE_NAME}_${SECTION} ALL DEPENDS ${MAN_FILE_GZ})
endforeach()

install(DIRECTORY ${CMAKE_BINARY_DIR}/man/ DESTINATION share/man)

# CPack debian package
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME ${PORJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "HuaTsai <huatsai42@gmail.com>")
set(CPACK_PACKAGE_MAINTAINER "HuaTsai")
set(CPACK_PACKAGE_VENDOR "HuaTsai")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libstdc++6, libeigen3-dev")
set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")

include(CPack)

# Uninstall
configure_file("${CMAKE_SOURCE_DIR}/cmake/uninstall.cmake.in"
               "${CMAKE_BINARY_DIR}/cmake/uninstall.cmake" IMMEDIATE @ONLY)
add_custom_target(
  uninstall
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake/uninstall.cmake
  COMMENT "Uninstall ${PROJECT_NAME}")

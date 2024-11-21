cmake_minimum_required(VERSION 3.16)

# Init VCPKG
set(vcpkg "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
if(NOT CMAKE_TOOLCHAIN_FILE AND EXISTS "${vcpkg}")
  set(CMAKE_TOOLCHAIN_FILE "${vcpkg}"
      CACHE FILEPATH "CMake toolchain file")
  message(STATUS "vcpkg toolchain found: ${CMAKE_TOOLCHAIN_FILE}")
endif()

# Add installed path to PREFIX
list(APPEND CMAKE_PREFIX_PATH "$ENV{VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}")

Project(Stag)

# Download STag from github
include(FetchContent)
FetchContent_Declare(
  stag-download
  GIT_REPOSITORY  https://github.com/ManfredStoiber/stag
  GIT_TAG         master
  BINARY_DIR      ${CMAKE_BINARY_DIR}/stag-build
  SOURCE_DIR      ${CMAKE_BINARY_DIR}/stag-src
)
FetchContent_MakeAvailable(stag-download)

# Add empty target for post build commands
add_custom_target(stag-builded ALL)
add_dependencies(stag-builded staglib)

# Copy .lib to output folder
add_custom_command(
  TARGET stag-builded POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_LINKER_FILE:staglib> ../STagSharpExtern/libs)

# Copy .pdb to output folder if in Debug
if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
  add_custom_command(
      TARGET stag-builded POST_BUILD 
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PDB_FILE:staglib> ../STagSharpExtern/libs)
endif()

# Copy stag.h to output folder
add_custom_command(
  TARGET stag-builded POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/stag-src/src/Stag.h ../STagSharpExtern/include)
  
# cmake --build . --target staglib --config Release
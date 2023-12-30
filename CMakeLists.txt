cmake_minimum_required(VERSION 3.22 )

project(simple-compiler VERSION 1.0)
set(CMAKE_COMPILER_EXPORT_COMMANDS ON)
# Need to add llvm library, basically can get from https://github.com/llvm/llvm-project/releases
# llvm-config binary 
find_package(LLVM CONFIG REQUIRED)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message("LLVM STATUS:
  Definitions ${LLVM_DEFINITIONS}
  Includes    ${LLVM_INCLUDE_DIRS}
  Libraries   ${LLVM_LIBRARY_DIRS}"
)
option(CMAKE_COMPILER_EXPORT_COMMANDS "Generate lsp database" ON)
# Binary and library output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

## Import LLVM_Library and header files
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${LLVM_LIBRARY_DIRS})

file(GLOB_RECURSE SOURCE src/*.cpp)

add_executable(toy_compiler ${SOURCE})







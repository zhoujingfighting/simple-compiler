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

# NOTE: Very important for building this program
if(NOT LLVM_ENABLE_RTTI)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

## Import LLVM_Library and header files
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${LLVM_LIBRARY_DIRS})

## Import gtest
find_package(GTest)
if (NOT GTEST_FOUND)
    message(WARNING "GTEST not found, trying another way......")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

file(GLOB_RECURSE SOURCE src/*.cpp)

add_executable(toy_compiler ${SOURCE})
target_link_libraries(toy_compiler PRIVATE LLVMCore LLVMSupport)

enable_testing()

add_subdirectory(test)





cmake_minimum_required (VERSION 2.6)
project (Pingcap_HW)

# # The version number

# # set (Tutorial_VERSION_MAJOR 1)
# # set (Tutorial_VERSION_MINOR 4)

# # configure_file (
# #   "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
# #   "${PROJECT_SOURCE_DIR}/TutorialConfig.h"
# # )

# # 检查c++编译器标志，设置c++11支持变量
# include(CheckCXXCompilerFlag)
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# # 使用变量设置编译标志
# if(COMPILER_SUPPORTS_CXX11)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# elseif(COMPILER_SUPPORTS_CXX0X)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
# else()
# message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
# endif()

include_directories("${PROJECT_BINARY_DIR}/src")

add_executable(hash_index src/main/main.cpp)
cmake_minimum_required(VERSION 3.28.0)

project(data_structure
    VERSION 0.0.1
    DESCRIPTION "Data Structure based on C"
    HOMEPAGE_URL "https://github.com/platinum-livehand/Data-Structure.git"
    LANGUAGES C
)

# 检测操作系统
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Configuring on/for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring on/for macOs")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Configuring on/for Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "AIX")
    message(STATUS "Configuring on/for IBM AIX")
else()
    message(STATUS "Configuring on/for ${CMAKE_SYSTEM_NAME}")
endif()

# 检查空指针类型的大小
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Target is 64 bits")
else()
    message(STATUS "Target is 32 bits")
endif()

# 通过定义目标编译定义，让预处理器了解主机处理器架构
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i386")
    message(STATUS "i386 architecture detected")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i686")
    message(STATUS "i686 architecture detected")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
    message(STATUS "x86_64 architecture detected")
else()
    message(STATUS "host processor architecture is unknown")
endif()

# 当前使用的编译器以及版本
# message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER_ID}")
# message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER_ID}")
message(STATUS "MAKE_C_COMPILER_VERSION: ${CMAKE_C_COMPILER_VERSION}")

# 设置C语言标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)
message(STATUS "C_STANDARD: ${CMAKE_C_STANDARD}")

# # 查看编译类型
# message(STATUS "CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
    # DEBUG 输出目录
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/lib/Debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/lib/Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin/Debug)
    message(STATUS "Debug mode:${CMAKE_C_FLAGS_DEBUG}")

elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3")
    # RELEASE 输出目录
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/lib/Release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/lib/Release)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin/Release)
    message(STATUS "Release mode:${CMAKE_C_FLAGS_RELEASE}")

else()
    message(STATUS "else:${CMAKE_BUILD_TYPE}")
    message(STATUS "else:${CMAKE_C_FLAGS_RELEASE}")

endif()

# 添加子目录
add_subdirectory(src)

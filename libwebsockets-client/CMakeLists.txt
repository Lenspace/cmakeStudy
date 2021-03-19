cmake_minimum_required (VERSION 3.10)
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 17)

set(Demo_VERSION_MAJOR 0)
set(Demo_VERSION_MINOR 1)

# 项目信息
project(libwsClient LANGUAGES CXX)

# 查找当前目录下所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 源码所在目录，猜测是CMakeLists.txt所在目录
include_directories("${PROJECT_SOURCE_DIR}/../include/libwebsockets")
link_directories("${PROJECT_SOURCE_DIR}/../lib/libwebsockets")


# 增加编译选项
#add_compile_options(-pthread) # 这个仅增加编译期间，链接期间会出现问题
set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")
# 显示编译过程
set(CMAKE_VERBOSE_MAKEFILE on)

message(STATUS "option: -pthread")  # 提示信息

# 指定生成目标
add_executable(lws-client ${DIR_SRCS})
target_link_libraries(lws-client libwebsockets.so)
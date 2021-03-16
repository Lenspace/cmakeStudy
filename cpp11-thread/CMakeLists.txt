cmake_minimum_required (VERSION 3.10)
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 17)

set(Demo_VERSION_MAJOR 0)
set(Demo_VERSION_MINOR 1)


#set(CMAKE_EXE_LINKER_FLAGS "-pthread")
# 项目信息
project(Demo1 LANGUAGES CXX)

# 增加编译选项
#add_compile_options(-pthread)
set(CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")
message(STATUS "option: -pthread")

# 查找当前目录下所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)



# 指定生成目标
add_executable(cpp11Thread ${DIR_SRCS})
cmake_minimum_required (VERSION 3.10)
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 17)

set(Demo_VERSION_MAJOR 0)
set(Demo_VERSION_MINOR 1)

# 项目信息
project(Demo1 LANGUAGES CXX)

# 查找当前目录下所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 源码所在目录，猜测是CMakeLists.txt所在目录
include_directories("${PROJECT_SOURCE_DIR}/include")

# 指定生成目标
add_executable(Demo ${DIR_SRCS})

cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 14)

# 添加 func 子目录（假设 func/CMakeLists.txt 定义了 myFunc 库）
add_subdirectory(func)

# 只将 main.cpp 添加到可执行文件
add_executable(MyProject main.cpp)

# 链接 myFunc 库
target_link_libraries(MyProject PRIVATE myFunc)
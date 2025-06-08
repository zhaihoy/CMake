CMake 学习路线：从筑基到精通

🎯 核心目标

理解 CMake 不仅是"构建工具"，而是跨平台构建系统生成器，用于生成实际构建系统（Makefile, Ninja, VS Solution等）的配置文件。

🧭 学习路线（四个阶段）

📍 第一阶段：筑基篇（核心概念和基本操作）

为什么需要 CMake？
理解手动管理构建的困难（命令行编译、手动管理依赖、平台差异）

CMake 的价值：

跨平台性

简化复杂项目

管理依赖

与 IDE 集成

社区支持

安装与环境设置
安装方法：

Windows：官网下载安装包

Linux：sudo apt-get install cmake

macOS：brew install cmake

验证安装：cmake --version

推荐编辑器/IDE：VS Code, CLion, Visual Studio

Hello World 项目

CMakeLists.txt

cmake_minimum_required(VERSION 3.10) # 指定最低 CMake 版本
project(MyProject)                  # 定义项目名称
add_executable(myapp main.c)       # 添加可执行文件目标

命令行构建流程

mkdir build && cd build   # 推荐源外构建
cmake ..                  # 生成构建系统
cmake --build .           # 执行构建
运行程序 (Windows: myapp.exe, Linux/macOS: ./myapp)

核心语法基础
命令：add_executable(), add_library(), message(), set(), if(), foreach()（不区分大小写）

变量：set(), ${VAR_NAME}, 环境变量 ENV{VAR_NAME}

注释：#开头

字符串操作：基本拼接和引用

添加源文件和生成目标

添加多个源文件

add_executable(myapp main.cpp util.cpp)

创建库

add_library(mylib STATIC lib.cpp)  # 静态库
add_library(mylib SHARED lib.cpp)  # 动态库

链接目标

target_link_libraries(myapp PRIVATE mylib)

修饰符     作用描述

PRIVATE 依赖项仅用于构建当前目标
PUBLIC 依赖项用于构建当前目标及其使用者
INTERFACE 依赖项不用于当前目标，但传递给使用者

📍 第二阶段：进阶实践（项目结构和依赖管理）

目录结构与模块化

项目结构示例

project/
├── CMakeLists.txt
├── src/
├── CMakeLists.txt

└── main.cpp

├── include/
└── utils.h

└── libs/
    ├── CMakeLists.txt
    └── mylib.cpp

父目录 CMakeLists.txt

add_subdirectory(src)
add_subdirectory(libs)

包含目录(Include Directories)

全局方式（谨慎使用）

include_directories(./include)

目标级方式（推荐）

target_include_directories(mylib PUBLIC ./include)

查找和使用外部库

find_package(OpenSSL REQUIRED)  # 查找库

链接库

target_link_libraries(myapp PRIVATE ${OpenSSL_LIBRARIES})
target_include_directories(myapp PRIVATE ${OpenSSL_INCLUDE_DIRS})

编译器选项与特性

设置C++标准

target_compile_features(myapp PRIVATE cxx_std_17)

添加编译选项

target_compile_options(myapp PRIVATE -Wall -Wextra -pedantic)

安装规则

install(TARGETS myapp DESTINATION bin)
install(TARGETS mylib
        ARCHIVE DESTINATION lib   # 静态库
        LIBRARY DESTINATION lib)  # 共享库
install(DIRECTORY include/ DESTINATION include)

执行安装：cmake --install . 或 make install

📍 第三阶段：精通技巧与最佳实践

现代 CMake 理念
Target-oriented：围绕目标配置（target_开头的命令）

Property-based：通过属性控制目标行为

Exporting & Importing Targets：使目标可被外部项目使用

Generator 表达式

条件包含路径

target_include_directories(mylib INTERFACE 
    <BUILD_INTERFACE:{CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

条件编译定义

target_compile_definitions(myapp PRIVATE <<CONFIG:Debug>:DEBUG_MODE=1>)

自定义命令与构建依赖

自定义命令

add_custom_command(
    OUTPUT generated.cpp
    COMMAND generator input.txt > generated.cpp
    DEPENDS input.txt
)

自定义目标

add_custom_target(generate ALL DEPENDS generated.cpp)

配置文件和选项

定义选项

option(USE_FEATURE_X "Enable feature X" ON)

配置文件生成

configure_file(config.h.in config.h)

测试支持

enable_testing()
add_test(NAME MyTest COMMAND myapp --test)
include(CTest)  # 包含CTest模块

运行测试：ctest 或 cmake --build . --target test

工具链和交叉编译

cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain.cmake ..

📍 第四阶段：掌握专业级应用

复杂项目管理
Superbuild 模式：使用ExternalProject管理依赖

包管理器集成：Conan, vcpkg等与CMake协同工作

调试 CMake 脚本

message(STATUS "Variable value: ${MY_VAR}")  # 输出调试信息

命令行调试选项：
cmake --trace ..
cmake --debug-output ..
cmake --graphviz=graph.dot ..  # 生成依赖图

性能调优与最佳实践
避免不必要的configure_file()

最小化无效缓存

有效管理自定义命令依赖

保持CMakeLists.txt整洁有序

深入学习资源
https://cmake.org/cmake/help/latest/

https://cliutils.gitlab.io/modern-cmake/

Craig Scott: https://crascit.com/professional-cmake/

Daniel Pfeifer: https://www.youtube.com/watch?v=bsXLMQ6WgIk

📌 重要提示
理论结合实践：学完概念后立即动手练习

版本意识：注意特性与cmake_minimum_required的兼容性

优先使用 Modern CMake：Target-oriented方式更安全可靠

利用资源：Stack Overflow有大量优质CMake问答

模块化思维：封装通用功能到.cmake脚本

保持耐心：CMake学习曲线陡峭但值得投入

🚀 学习路线总结：  
基础语法 → 项目结构 → 包含目录/链接 → 外部库 → 编译选项 → 安装规则 → 现代CMake理念 → 生成器表达式 → 自定义命令 → 配置选项 → 测试 → 调试 → 高级主题

坚持练习，由简入繁，掌握强大的工具！💪

# 递归找到所有的.cpp文件
file(GLOB_RECURSE FUNC "*.cpp")
# 将FUNC变量中的所有.cpp文件添加到库中
add_library(myFunc ${FUNC})
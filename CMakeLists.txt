cmake_minimum_required(VERSION 3.17)
project(DataStructure)

set(CMAKE_CXX_STANDARD 11)

# 指定头文件路径，就可以不将头文件添加到add_executable中
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/array/include)

# 工具类
file(GLOB utils "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp")

# 将目录下全部源文件，一起添加到可执行文件中
file(GLOB arrayFiles "${CMAKE_CURRENT_SOURCE_DIR}/array/*.cpp")
add_executable(Array ${arrayFiles} ${utils})

# 下面是编译多个可执行文件，一个cpp文件编译出一个可执行文件
file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach (file ${files})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file} ${utils})
endforeach ()

#add_executable(DataStructure sort.cpp)
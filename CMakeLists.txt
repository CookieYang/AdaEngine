cmake_minimum_required (VERSION 2.8)
SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
project(AdaEngine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/glew/lib)
add_executable(AdaEngine main.cpp)
target_link_libraries(AdaEngine glew opengl32)


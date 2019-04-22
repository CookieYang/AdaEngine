cmake_minimum_required (VERSION 2.8)
SET(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
project(AdaEngine)
aux_source_directory(. DIR_SRCS)
include_directories(${PROJECT_SOURCE_DIR}/thirdParty/glad/include
 ${PROJECT_SOURCE_DIR}/thirdParty/glfw-3.3/include
 ${PROJECT_SOURCE_DIR}/core/head)
link_directories(${PROJECT_SOURCE_DIR}/thirdParty/glfw-3.3/lib)
add_subdirectory(${PROJECT_SOURCE_DIR}/thirdParty/glad)
add_subdirectory(${PROJECT_SOURCE_DIR}/core)
add_executable(AdaEngine main.cpp)
target_link_libraries(AdaEngine glad core glfw3 opengl32)


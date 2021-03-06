cmake_minimum_required(VERSION 3.5)
project(dkr VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if(MSVC)
  # /wd4005  macro-redefinition
  # /wd4068  unknown pragma
  # /wd4244  conversion from 'type1' to 'type2'
  # /wd4267  conversion from 'size_t' to 'type2'
  # /wd4800  force value to bool 'true' or 'false' (performance warning)
  add_compile_options(/wd4005 /wd4068 /wd4244 /wd4267 /wd4800)
  add_definitions(/DNOMINMAX /DWIN32_LEAN_AND_MEAN=1 /D_CRT_SECURE_NO_WARNINGS)
endif()

set(ASSSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_SAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(BUILD_TESTING OFF)
set(RAPIDJSON_BUILD_TESTS OFF)
set(RAPIDJSON_BUILD_EXAMPLES OFF)
set(RAPIDJSON_BUILD_DOC OFF)
set(GLFW_BUILD_DOCS OFF)
set(Boost_NO_BOOST_CMAKE ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(GLEW REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(OpenGL REQUIRED)

add_subdirectory(third_party/assimp)
add_subdirectory(third_party/entt)
add_subdirectory(third_party/rapidjson)
add_subdirectory(third_party/glfw)

source_group("RapidJSON" RapidJSON)
source_group("RapidJSON" assimp)
add_subdirectory(dankerer)

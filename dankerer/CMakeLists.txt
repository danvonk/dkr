add_subdirectory(base)
add_subdirectory(gfx)

add_executable(Main main.cpp)

target_include_directories(Main PUBLIC 
${GLEW_INCLUDE_DIRS}
${Boost_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/dankerer
${CMAKE_SOURCE_DIR}/third_party/glm
${CMAKE_SOURCE_DIR}/third_party/assimp/include
${CMAKE_SOURCE_DIR}/third_party/glfw/include
${CMAKE_SOURCE_DIR}/third_party/entt/src
${OPENGL_INCLUDE_DIR}
)

target_link_libraries(Main LINK_PUBLIC
Base
Graphics
glfw
${GLEW_LIBRARIES}
OpenGL::GL
)
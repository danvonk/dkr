package(default_visibility = ["//dankerer:internal"])

cc_library(
    name = "gfx",
    srcs = [
        "camera.cpp",
        "commandBuffer.cpp",
        "elementBuffer.cpp",
        "framebuffer.cpp",
        "material.cpp",
        "renderer.cpp",
        "shader.cpp",
        "shaderProgram.cpp",
        "staticMesh.cpp",
        "texture.cpp",
        "uniformBuffer.cpp",
        "vertexArrayConfig.cpp",
        "vertexBuffer.cpp",
        "window.cpp",
    ],
    hdrs = [
        "camera.h",
        "commandBuffer.h",
        "common.h",
        "drawCommands.h",
        "elementBuffer.h",
        "framebuffer.h",
        "material.h",
        "renderer.h",
        "shader.h",
        "shaderProgram.h",
        "staticMesh.h",
        "texture.h",
        "uniformBuffer.h",
        "vertexArrayConfig.h",
        "vertexBuffer.h",
        "window.h",
    ],
    deps = [
        "//dankerer/base",
        "@assimp",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/container:flat_hash_set",
    ],
)

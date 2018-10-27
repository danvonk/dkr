# Restricts most packages to use by //xrtl/... only.
# Selective rules we wish to support to external users are set to
# //visibility:public.
package_group(
    name = "internal",
    packages = [
        "//dankerer",
        "//dankerer/base",
        "//dankerer/gfx",
        "//third_party/...",
    ],
)

LINKOPT = [
    "-lGL",
    "-lGLU",
    "-lX11",
    "-lXxf86vm",
    "-lXinerama",
    "-lXcursor",
    "-lpthread",
    "-lXrandr",
    "-lXi",
    "-lstdc++fs",
    "-ldl",
]

cc_binary(
    name = "main",
    srcs = [
        "main.cpp",
    ],
    data = [
        "resources/chalet.jpg",
        "resources/chalet.obj",
        "resources/mat.xml",
        "resources/sh1.frag",
        "resources/sh1.vert",
        "resources/teapot.obj",
        "resources/wall.jpg",
    ],
    linkopts = LINKOPT,
    deps = [
        "//dankerer/gfx",
        "//third_party/glm",
        "@assimp",
        "@com_google_absl//absl/strings",
        "@glew",
        "@glfw",
    ],
)

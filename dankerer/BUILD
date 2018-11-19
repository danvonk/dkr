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
    data = glob(["resources/**"]),
    linkopts = LINKOPT,
    deps = [
        "//dankerer/gfx",
        "//third_party/glm",
        "@assimp",
        "@com_google_absl//absl/container:flat_hash_map",
        "@com_google_absl//absl/strings",
        "@glew",
        "@glfw",
    ],
)

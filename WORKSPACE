local_repository(
  # Name of the Abseil repository. This name is defined within Abseil's
  # WORKSPACE file, in its `workspace()` metadata
  name = "com_google_absl",

  # NOTE: Bazel paths must be absolute paths. E.g., you can't use ~/Source
  path = "/home/dan/dev/abseil-cpp",
)

new_http_archive(
    name = "glfw",
    build_file = "BUILD.glfw",
    sha256 = "e10f0de1384d75e6fc210c53e91843f6110d6c4f3afbfb588130713c2f9d8fe8",
    strip_prefix = "glfw-3.2.1",
    urls = ["https://github.com/glfw/glfw/archive/3.2.1.tar.gz"],
)

new_git_repository(
    name = "glew",
    remote = "https://github.com/Lunarsong/glew.git",
    commit = "a38094b249974f219f9c23f54b5b60a620777a13",
    build_file = "BUILD.glew",
)

new_http_archive(
    name = "assimp",
    build_file = "BUILD.assimp",
    sha256 = "60080d8ab4daaab309f65b3cffd99f19eb1af8d05623fff469b9b652818e286e",
    strip_prefix = "assimp-4.0.1",
    urls = ["https://github.com/assimp/assimp/archive/v4.0.1.tar.gz"],
)

# proto_library, cc_proto_library, and java_proto_library rules implicitly
# depend on @com_google_protobuf for protoc and proto runtimes.
# This statement defines the @com_google_protobuf repo.
http_archive(
    name = "com_google_protobuf",
    sha256 = "cef7f1b5a7c5fba672bec2a319246e8feba471f04dcebfe362d55930ee7c1c30",
    strip_prefix = "protobuf-3.5.0",
    urls = ["https://github.com/google/protobuf/archive/v3.5.0.zip"],
)

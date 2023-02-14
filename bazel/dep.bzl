load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")
def c_kzg_deps(repo=""):
    repo_ref = ""
    if repo:
        repo_ref= "@{}".format(repo)
    maybe(
        http_archive,
        name = "com_github_blst",
        build_file = "{}//bazel:BUILD.blst".format(repo_ref),
        sha256 = "d5c5c00feddff1d28402f936ed19f87e9a7f647d26f216a0f1c515a0b15b6401",
        urls = ["https://github.com/supranational/blst/archive/refs/tags/v0.3.10.tar.gz"],
        strip_prefix = "blst-0.3.10",
    )

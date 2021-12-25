load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":seabed",
    ],
)

cc_library(
    name = "seabed",
    srcs = ["seabed.cc"],
    hdrs = ["seabed.h"],
)

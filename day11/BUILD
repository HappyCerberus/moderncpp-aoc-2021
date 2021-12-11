load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "flashing",
    srcs = ["flashing.cc"],
    hdrs = ["flashing.h"],
)

cc_test(
    name = "flashing_test",
    size = "small",
    srcs = ["flashing_test.cc"],
    deps = [
        ":flashing",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":flashing",
    ],
)

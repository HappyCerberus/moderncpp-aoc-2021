load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "cave",
    srcs = ["cave.cc"],
    hdrs = ["cave.h"],
)

cc_test(
    name = "cave_test",
    size = "small",
    srcs = ["cave_test.cc"],
    deps = [
        ":cave",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":cave",
    ],
)

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "lanternfish",
    srcs = ["lanternfish.cc"],
    hdrs = ["lanternfish.h"],
)

cc_test(
    name = "lanternfish_test",
    size = "small",
    srcs = ["lanternfish_test.cc"],
    deps = [
        ":lanternfish",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":lanternfish",
    ],
)

cc_binary(
    name = "compile-time",
    srcs = ["compile-time.cc"],
)

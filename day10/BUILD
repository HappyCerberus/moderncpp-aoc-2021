load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "brackets",
    srcs = ["brackets.cc"],
    hdrs = ["brackets.h"],
)

cc_test(
    name = "brackets_test",
    size = "small",
    srcs = ["brackets_test.cc"],
    deps = [
        ":brackets",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":brackets",
    ],
)

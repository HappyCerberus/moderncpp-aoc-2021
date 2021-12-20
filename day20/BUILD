load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "filter",
    srcs = ["filter.cc"],
    hdrs = ["filter.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":filter",
    ],
)

cc_test(
    name = "filter_test",
    srcs = ["filter_test.cc"],
    deps = [
        ":filter",
        "@com_google_googletest//:gtest_main",
    ],
)

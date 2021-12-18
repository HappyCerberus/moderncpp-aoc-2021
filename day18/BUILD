load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "snail-number",
    srcs = ["snail-number.cc"],
    hdrs = ["snail-number.h"],
)

cc_test(
    name = "snail-number_test",
    srcs = ["snail-number_test.cc"],
    deps = [
        ":snail-number",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":snail-number",
    ],
)

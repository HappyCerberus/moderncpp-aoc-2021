load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "point",
    srcs = ["point.cc"],
    hdrs = ["point.h"],
)

cc_library(
    name = "range",
    srcs = ["range.cc"],
    hdrs = ["range.h"],
    deps = [
        ":point",
    ],
)

cc_test(
    name = "range_test",
    srcs = ["range_test.cc"],
    deps = [
        ":range",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [":range"],
)

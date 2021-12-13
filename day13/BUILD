load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "fold",
    srcs = ["fold.cc"],
    hdrs = ["fold.h"],
)

cc_test(
    name = "fold_test",
    size = "small",
    srcs = ["fold_test.cc"],
    deps = [
        ":fold",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":fold",
    ],
)

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "crabs",
    srcs = ["crabs.cc"],
    hdrs = ["crabs.h"],
)

cc_test(
    name = "crabs_test",
    size = "small",
    srcs = ["crabs_test.cc"],
    deps = [
        ":crabs",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":crabs",
    ],
)

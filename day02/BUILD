load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "navigation",
    srcs = ["navigation.cc"],
    hdrs = ["navigation.h"],
)

cc_test(
    name = "navigation_test",
    size = "small",
    srcs = ["navigation_test.cc"],
    deps = [
        ":navigation",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "part1-main",
    srcs = ["part1-main.cc"],
    deps = [":navigation"],
)

cc_library(
    name = "with-aim",
    srcs = ["with-aim.cc"],
    hdrs = ["with-aim.h"],
)

cc_test(
    name = "with-aim_test",
    size = "small",
    srcs = ["with-aim_test.cc"],
    deps = [
        ":with-aim",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "part2-main",
    srcs = ["part2-main.cc"],
    deps = [":with-aim"],
)

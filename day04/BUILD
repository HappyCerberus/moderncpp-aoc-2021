load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "bingo",
    srcs = ["bingo.cc"],
    hdrs = ["bingo.h"],
)

cc_test(
    name = "bingo_test",
    size = "small",
    srcs = ["bingo_test.cc"],
    deps = [
        ":bingo",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "part1-main",
    srcs = ["part1-main.cc"],
    deps = [
        ":bingo",
    ],
)

cc_binary(
    name = "part2-main",
    srcs = ["part2-main.cc"],
    deps = [
        ":bingo",
    ],
)

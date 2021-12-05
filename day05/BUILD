load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "lines",
    srcs = ["lines.cc"],
    hdrs = ["lines.h"],
)

cc_test(
    name = "lines_test",
    size = "small",
    srcs = ["lines_test.cc"],
    deps = [
        ":lines",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "part1-main",
    srcs = ["part1-main.cc"],
    deps = [
        ":lines",
    ],
)

cc_library(
    name = "diagonals",
    srcs = ["diagonals.cc"],
    hdrs = ["diagonals.h"],
)

cc_test(
    name = "diagonals_test",
    size = "small",
    srcs = ["diagonals_test.cc"],
    deps = [
        ":diagonals",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "part2-main",
    srcs = ["part2-main.cc"],
    deps = [
        ":diagonals",
    ],
)

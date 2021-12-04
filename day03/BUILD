load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "diagnostic",
    srcs = ["diagnostic.cc"],
    hdrs = ["diagnostic.h"],
)

cc_test(
    name = "diagnostic_test",
    size = "small",
    srcs = ["diagnostic_test.cc"],
    deps = [
        ":diagnostic",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "part1-main",
    srcs = ["part1-main.cc"],
    deps = [
        ":diagnostic",
    ],
)

cc_binary(
    name = "part1-main-preread",
    srcs = ["part1-main-preread.cc"],
    deps = [
        ":diagnostic",
    ],
)

cc_library(
    name = "ratings",
    srcs = ["ratings.cc"],
    hdrs = ["ratings.h"],
)

cc_test(
    name = "ratings_test",
    size = "small",
    srcs = ["ratings_test.cc"],
    deps = [
        ":ratings",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "part2-main",
    srcs = ["part2-main.cc"],
    deps = [
        ":ratings",
    ],
)

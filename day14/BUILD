load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "generator",
    hdrs = ["generator.h"],
)

cc_library(
    name = "polymer",
    srcs = ["polymer.cc"],
    hdrs = ["polymer.h"],
    deps = [
        ":pair",
        ":parsing",
    ],
)

cc_library(
    name = "lazy-brute-force",
    srcs = ["lazy-brute-force.cc"],
    hdrs = ["lazy-brute-force.h"],
    deps = [
        ":generator",
        ":pair",
        ":parsing",
    ],
)

cc_test(
    name = "lazy-brute-force_test",
    size = "small",
    srcs = ["lazy-brute-force_test.cc"],
    deps = [
        ":lazy-brute-force",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "parsing",
    srcs = ["parsing.cc"],
    hdrs = ["parsing.h"],
    deps = [
        ":pair",
    ],
)

cc_library(
    name = "pair",
    hdrs = ["pair.h"],
)

cc_test(
    name = "polymer_test",
    size = "small",
    srcs = ["polymer_test.cc"],
    deps = [
        ":polymer",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":lazy-brute-force",
        ":polymer",
    ],
)

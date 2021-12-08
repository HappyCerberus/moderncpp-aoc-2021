load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "parsing",
    srcs = ["parsing.cc"],
    hdrs = ["parsing.h"],
    deps = [
        ":display",
    ],
)

cc_library(
    name = "display",
    srcs = ["display.cc"],
    hdrs = ["display.h"],
)

cc_library(
    name = "wiring",
    srcs = ["wiring.cc"],
    hdrs = ["wiring.h"],
    deps = [
        ":display",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":parsing",
        ":wiring",
    ],
)

cc_test(
    name = "puzzle_test",
    size = "small",
    srcs = ["puzzle_test.cc"],
    deps = [
        ":display",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "wiring_test",
    size = "small",
    srcs = ["wiring_test.cc"],
    deps = [
        ":parsing",
        ":wiring",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "parsing_test",
    size = "small",
    srcs = ["parsing_test.cc"],
    deps = [
        ":parsing",
        "@com_google_googletest//:gtest_main",
    ],
)

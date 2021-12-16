load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "bitstream",
    srcs = ["bitstream.cc"],
    hdrs = ["bitstream.h"],
    deps = [":generator"],
)

cc_library(
    name = "packet",
    srcs = ["packet.cc"],
    hdrs = ["packet.h"],
    deps = [
        ":bitstream",
    ],
)

cc_library(
    name = "generator",
    hdrs = ["generator.h"],
)

cc_test(
    name = "packet_test",
    srcs = ["packet_test.cc"],
    deps = [
        ":packet",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":bitstream",
        ":packet",
    ],
)

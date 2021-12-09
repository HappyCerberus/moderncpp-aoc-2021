load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "heightmap",
    srcs = ["heightmap.cc"],
    hdrs = ["heightmap.h"],
)

cc_library(
    name = "flood-fill",
    srcs = ["flood-fill.cc"],
    hdrs = ["flood-fill.h"],
    deps = [
        ":heightmap",
    ],
)

cc_test(
    name = "heightmap_test",
    size = "small",
    srcs = ["heightmap_test.cc"],
    deps = [
        ":heightmap",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "flood-fill_test",
    size = "small",
    srcs = ["flood-fill_test.cc"],
    deps = [
        ":flood-fill",
        ":heightmap",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":flood-fill",
        ":heightmap",
    ],
)

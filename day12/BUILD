load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "search-with-memory",
    srcs = ["search-with-memory.cc"],
    hdrs = ["search-with-memory.h"],
)

cc_test(
    name = "search-with-memory_test",
    size = "small",
    srcs = ["search-with-memory_test.cc"],
    deps = [
        ":search-with-memory",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":search-with-memory",
    ],
)

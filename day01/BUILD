load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "trivial",
    srcs = ["trivial.cc"],
    hdrs = ["trivial.h"],
)

cc_library(
    name = "sliding",
    srcs = ["sliding.cc"],
    hdrs = ["sliding.h"],
)

cc_test(
    name = "trivial_test",
    size = "small",
    srcs = ["trivial_test.cc"],
    deps = [
        ":trivial",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "sliding_test",
    size = "small",
    srcs = ["sliding_test.cc"],
    deps = [
        ":sliding",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "sonar-sliding",
    srcs = ["sonar-sliding.cc"],
    deps = [":sliding"],
)

cc_binary(
    name = "sonar-trivial",
    srcs = ["sonar-trivial.cc"],
    deps = [":trivial"],
)

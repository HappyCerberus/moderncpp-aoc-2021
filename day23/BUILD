load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")

cc_library(
    name = "room",
    srcs = ["room.cc"],
    hdrs = ["room.h"],
)

cc_test(
    name = "room_test",
    srcs = ["room_test.cc"],
    deps = [
        ":room",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_library(
    name = "puzzle",
    srcs = ["puzzle.cc"],
    hdrs = ["puzzle.h"],
    deps = [
        ":room",
    ],
)

cc_test(
    name = "puzzle_test",
    srcs = ["puzzle_test.cc"],
    deps = [
        ":puzzle",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":puzzle",
    ],
)

#cc_test(
#    name = "puzzle_test",
#    srcs = ["puzzle_test.cc"],
#    deps = [
#        ":puzzle",
#        "@com_google_googletest//:gtest_main",
#    ],
#)

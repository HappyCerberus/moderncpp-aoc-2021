#include "search-with-memory.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>

using ::testing::UnorderedElementsAre;

TEST(SearchWithMemory, Parsing) {
  std::stringstream input("start-A\nstart-b\nA-c\nA-b\nb-d\nA-end\nb-end");
  Graph g = parse_graph(input);
  EXPECT_EQ(g.size(), 6);
  EXPECT_THAT(g["start"], UnorderedElementsAre("A", "b"));
  EXPECT_EQ(g["end"].size(), 0);
  EXPECT_THAT(g["A"], UnorderedElementsAre("b", "c", "end")); // no start
}

TEST(SearchWithMemory, Simple) {
  {
    std::stringstream input("start-end");
    Graph g = parse_graph(input);
    EXPECT_EQ(count_paths(g), 1);
  }
  {
    std::stringstream input("start-end\nstart-A\nA-end");
    Graph g = parse_graph(input);
    EXPECT_EQ(count_paths(g), 2);
  }
}

TEST(SearchWithMemory, FromAoCInput) {
  std::stringstream input("start-A\nstart-b\nA-c\nA-b\nb-d\nA-end\nb-end");
  Graph g = parse_graph(input);
  EXPECT_EQ(count_paths(g), 10);
  EXPECT_EQ(count_complex_paths(g), 36);
}

TEST(SearchWithMemory, FromAoCLargerInput) {
  std::stringstream input("dc-end\nHN-start\nstart-kj\ndc-start\ndc-HN\nLN-dc\nHN-end\nkj-sa\nkj-HN\nkj-dc");
  Graph g = parse_graph(input);
  EXPECT_EQ(count_paths(g), 19);
  EXPECT_EQ(count_complex_paths(g), 103);
}

TEST(SearchWithMemory, FromAoCLargestInput) {
  std::stringstream input(
      "fs-end\nhe-DX\nfs-he\nstart-DX\npj-DX\nend-zg\nzg-sl\nzg-pj\npj-he\nRW-he\nfs-DX\npj-RW\nzg-RW\nstart-pj\nhe-WI\nzg-he\npj-fs\nstart-RW");
  Graph g = parse_graph(input);
  EXPECT_EQ(count_paths(g), 226);
  EXPECT_EQ(count_complex_paths(g), 3509);
}
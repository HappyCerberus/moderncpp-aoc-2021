#include "puzzle.h"

#include <gtest/gtest.h>

TEST(Puzzle, Content) {
  Puzzle puzzle{.hallway = {'A', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                .rooms = {{'A', {'.', '.'}}, {'B', {'C', '.'}}, {'C', {'.', '.'}}, {'D', {'.', '.'}}}};

  EXPECT_EQ(puzzle.greedy_move_to_room(), 4);
  EXPECT_EQ(puzzle.rooms[0].top(), 'A');
  EXPECT_EQ(puzzle.greedy_room_to_room(), 600);
  EXPECT_EQ(puzzle.rooms[2].top(), 'C');
  EXPECT_EQ(puzzle.rooms[0].top(), 'A');
}

TEST(Puzzle, HallWayMove) {
  {
    Puzzle puzzle{.hallway = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                  .rooms = {{'A', {'.', '.'}}, {'B', {'C', '.'}}, {'C', {'B', '.'}}, {'D', {'.', '.'}}}};
    auto v = puzzle.hallway_move(2, 3);
    EXPECT_TRUE(v.has_value());
    EXPECT_EQ(v.value(), 50);
  }
  {
    Puzzle puzzle{.hallway = {'B', 'C', '.', 'D', '.', '.', '.', '.', '.', '.', '.'},
                  .rooms = {{'A', {'A', '.'}}, {'B', {'B', '.'}}, {'C', {'C', '.'}}, {'D', {'A', 'D'}}}};
    auto v = puzzle.hallway_move(3, 9);
    EXPECT_TRUE(v.has_value());
    EXPECT_EQ(v.value(), 2000);
  }
}

TEST(Puzzle, Puzzle1) {
  Puzzle puzzle{.hallway = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                .rooms = {{'A', {'B', 'B'}}, {'B', {'A', 'A'}}, {'C', {'C', 'C'}}, {'D', {'D', 'D'}}}};
  auto v = find_shortest(puzzle);
  EXPECT_TRUE(v.has_value());
}

TEST(Puzzle, Puzzle2) {
  Puzzle puzzle{.hallway = {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                .rooms = {{'A', {'A', 'B'}}, {'B', {'D', 'C'}}, {'C', {'C', 'B'}}, {'D', {'A', 'D'}}}};
  auto v = find_shortest(puzzle);
  ASSERT_TRUE(v.has_value());
  EXPECT_EQ(v.value(), 12521);
}

TEST(Puzzle, Puzzle3) {
  Puzzle puzzle{.hallway = {'B', 'C', '.', 'D', '.', 'D', '.', '.', '.', '.', '.'},
                .rooms = {{'A', {'A', '.'}}, {'B', {'B', '.'}}, {'C', {'C', '.'}}, {'D', {'A', '.'}}}};
  auto v = puzzle.hallway_move(3, 9);
  ASSERT_TRUE(v.has_value());
  EXPECT_EQ(v.value(), 3);
  EXPECT_EQ(puzzle.greedy_move_to_room(), 5000);
  EXPECT_EQ(puzzle.greedy_move_to_room(), 6000);
  EXPECT_EQ(puzzle.greedy_move_to_room(), 600);
  EXPECT_EQ(puzzle.greedy_move_to_room(), 50);
  EXPECT_EQ(puzzle.greedy_move_to_room(), 8);
  EXPECT_TRUE(puzzle.solved());
}

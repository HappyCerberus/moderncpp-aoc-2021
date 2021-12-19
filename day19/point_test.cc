#include "point.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

using ::testing::UnorderedElementsAre;

TEST(Point, Rotations) {
  std::vector<Point3D> points;
  for (auto &rot : ROTATIONS) {
    Point3D point{1, 2, 3};
    point = point.rotate(rot);
    points.push_back(point);
  }

  EXPECT_THAT(points,
              UnorderedElementsAre(Point3D(1, 2, 3), Point3D(1, 3, -2), Point3D(1, -2, -3), Point3D(1, -3, 2), Point3D(-1, 2, -3), Point3D(-1, -3, -2),
                                   Point3D(-1, -2, 3), Point3D(-1, 3, 2), Point3D(2, 1, -3), Point3D(2, -3, -1), Point3D(2, -1, 3), Point3D(2, 3, 1),
                                   Point3D(-2, 1, 3), Point3D(-2, 3, -1), Point3D(-2, -1, -3), Point3D(-2, -3, 1), Point3D(3, 1, 2), Point3D(3, 2, -1),
                                   Point3D(3, -1, -2), Point3D(3, -2, 1), Point3D(-3, 1, -2), Point3D(-3, -2, -1), Point3D(-3, -1, 2), Point3D(-3, 2, 1)));
}

TEST(Point, Operations) {
  Point3D a{1, 2, 3}, b{4, 5, 6};
  EXPECT_EQ((a - b), Point3D(-3, -3, -3));
  EXPECT_EQ((a + b), Point3D(5, 7, 9));
}

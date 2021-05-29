#include <antgame/WorldObject.h>

#include <gtest/gtest.h>

// Demonstrate some basic assertions.
TEST(WorldObjectTest, CanPrint) {
    Point point(1, 2);

    WorldObject wo(point, "woName");
    EXPECT_STREQ(wo.Print(false).c_str(), "woName: pos:POINT(1 2)\n");
}

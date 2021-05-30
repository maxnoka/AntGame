#include <antgame/WorldObject.h>

#include <easyloggingpp/easylogging++.h>
#include <gtest/gtest.h>

INITIALIZE_EASYLOGGINGPP

// Demonstrate some basic assertions.
TEST(WorldObjectTest, CanPrint) {
    Point point(1, 2);

    WorldObject wo(point, "woName");
    EXPECT_STREQ(wo.Print(false).c_str(), "woName: pos:POINT(1 2)");
}

#include <antgame/WorldObject.h>
#include <antgame/Ant.h>

#include <easyloggingpp/easylogging++.h>
#include <gtest/gtest.h>

INITIALIZE_EASYLOGGINGPP

// Demonstrate some basic assertions.
TEST(WorldObjectTest, CanPrint) {
    Point point(1, 2);

    Ant ant(point, "Ant");
    EXPECT_STREQ(ant.Print(false).c_str(), "Ant: pos:POINT(1 2)");
}

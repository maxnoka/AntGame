#include <antgame/WorldTree.h>
#include <antgame/Ant.h>

#include <easyloggingpp/easylogging++.h>
#include <gtest/gtest.h>

INITIALIZE_EASYLOGGINGPP

TEST(WorldTreeTest, Insert) {
    WorldTree wt;
    auto obj = std::make_shared<Ant>(Point(1, 2), "woName");
    wt.InsertObject(obj);

    size_t numEntries = 0;
    for ( auto it = wt.QAll() ; it != wt.QEnd() ; ++it ) {
        ++numEntries;
    }
    ASSERT_EQ(numEntries, 1);

    auto allEntries = wt.GetAll();
    ASSERT_EQ(allEntries.size(), 1);
    EXPECT_EQ(allEntries.front(), obj);
}

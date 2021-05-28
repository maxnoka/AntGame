#include <antgame/WorldTree.h>

#include <iostream>

int main(int argc, char **argv)
{
    WorldTree wt;
    
    // put some world objects into the world
    for ( unsigned i = 0 ; i < 10 ; ++i ) {
        // create a box
        Point point(i + 0.0f, i + 0.0f);
        auto newObj = std::make_shared<WorldObject>(point, std::to_string(i));
        wt.InsertObject(std::move(newObj));
    }
    
    // do a query
    std::cout << "knn query point:" << std::endl;
    Point point(0, 0);
    std::cout << boost::geometry::wkt<Point>(point) << std::endl;
    
    auto result = wt.GetNearestNeighbours(point, 2);
    std::cout << "knn query result:" << std::endl;
    for (const auto& v : result) {
        v->Print(true);
        wt.RemoveObject(v);
    }
    
    std::cout << "again\n";
    result = wt.GetNearestNeighbours(point, 2);
    std::cout << "knn query result:" << std::endl;
    for (const auto& v : result) {
        v->Print(true);
    }
 
	return 0;
}

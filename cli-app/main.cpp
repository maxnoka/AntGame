#include <antgame/World.h>
#include <antgame/Ant.h>

#include <easyloggingpp/easylogging++.h>

#include <iostream>

INITIALIZE_EASYLOGGINGPP

int main(int argc, char **argv) {
    World world;
    
    // put some world objects into the world
    for ( unsigned i = 0 ; i < 10 ; ++i ) {
        // create a box
        Point point(i + 0.0f, i + 0.0f);
        auto newObj = std::make_shared<Ant>(point, std::to_string(i));
        world.AddObject(std::move(newObj));
    }

    for (size_t i = 0; i < 10000; i++)
    {
        world.Update();
    }

    world.DbgPrint();
	return 0;
}

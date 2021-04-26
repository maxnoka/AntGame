#include "bar.h"

#include <iostream>

Bar::Bar()
{
    std::cout << "contstructor\n";
}

Bar::~Bar()
{
    std::cout << "destructor\n";
}

void Bar::DoStuff()
{
	std::cout << "REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n";
}


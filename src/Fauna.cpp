#include <antgame/Fauna.h>

#include <iostream>

Ant::Ant(std::string Name, Position spawnPoint)
: m_name(Name)
, m_age(0)
, m_position(spawnPoint)
{
}


void Ant::PrintName()
{
	std::cout << m_name << "\n";
}

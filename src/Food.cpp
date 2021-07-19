#include <antgame/Food.h>

#include <antgame/FoodSource.h>

void Food::BecomeEaten() { 
    if (m_foodSource) {
        m_foodSource.value()->ReportEaten();
    }
    RemoveSelfFromWorld(); 
}

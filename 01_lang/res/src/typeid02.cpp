#include <iostream>
#include "car.h"

using namespace nec::car_v1;

void car_game(Car* carptr)
{
    carptr->start();
    carptr->run();
    
    if(typeid(*carptr) == typeid(Mercedes))
    {
        static_cast<Mercedes*>(carptr)->open_sunroof();
        (void) getchar();
    }
    carptr->stop();
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; ++i)
    {
        auto p = create_random_car();
        car_game(p);
        delete p;
    }
    
    try
    {
        car_game(nullptr);
    }
    catch(const std::bad_typeid& e)
    {
        std::cout << "Exception caught:" << e.what() << '\n';
    }
    
}

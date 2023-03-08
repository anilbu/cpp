#include <iostream>
#include <memory>
#include "car.h"
#include "nutility.h"

std::unique_ptr<Car> create_random_car_uptr() {
    Irand rand{ 0, 6 };

    switch (rand()) {
    case 0: return std::make_unique<Bmw>();
    case 1: return std::make_unique<Mercedes>();
    case 2: return std::make_unique<MercedesS500>();
    case 3: return std::make_unique<Fiat>();
    case 4: return std::make_unique<Renault>();
    case 5: return std::make_unique<Dacia>();
    case 6: return std::make_unique<Volvo>();
    default: return nullptr;
    }
}

void car_game_loop(std::unique_ptr<Car> car)
{
    car->start();
    car->run();
    car->stop();
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        for (int i = 0; i < 10; ++i)
        {
            auto car = create_random_car_uptr();
            car_game_loop(move(car));
        }
    }

}

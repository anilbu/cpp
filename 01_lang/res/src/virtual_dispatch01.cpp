#include <iostream>

class Car {
public:
    virtual void start() { std::cout << "car has started\n"; }
    virtual void run() { std::cout << "car is running now!\n"; }
    virtual void stop() { std::cout << "car has just stopped\n"; }
};

class Mercedes: public Car {
public:
    void start() { std::cout << "Audi has started\n"; }
    void run() { std::cout << "Audi is running now!\n"; }
    void stop() { std::cout << "Audi has just stopped\n"; }
};

class Audi: public Car {
public:
    void start() { std::cout << "Audi has started\n"; }
    void run() { std::cout << "Audi is running now!\n"; }
    void stop() { std::cout << "Audi has just stopped\n"; }
};

class Fiat: public Car {
public:
    void start() { std::cout << "Audi has started\n"; }
    void run() { std::cout << "Audi is running now!\n"; }
    void stop() { std::cout << "Audi has just stopped\n"; }
};

void car_game(Car& car)
{
    car.start();
    car.run();
    car.stop();
}

Car* create_random_car()
{
    switch (rand() % 3)
    {
    case 0: std::cout<< "Mercedes uretiliyor...\n"; return new Mercedes;
    case 1: std::cout<< "Audi uretiliyor...\n"; return new Audi;
    case 2: std::cout<< "Fiat uretiliyor...\n"; return new Fiat;
    }
    return nullptr;
}

int main(int argc, char const *argv[])
{
    srand(static_cast<unsigned>(time(0)));
    
    for (size_t i = 0; i < 10; i++)
    {
        Car* carptr = create_random_car();
        car_game(*carptr);
        (void)getchar();
        
        // delete carptr; // ileride deginilecek: virtual dtor
    }
}

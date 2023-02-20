#include <iostream>

class Car {
public:
    // ...
    virtual void start() = 0;
    virtual Car* clone() = 0;
};

class Volvo : public Car {
private:
    // ...
    virtual void start() override {
        std::cout << "Volvo has started\n";
    }
    virtual Volvo* clone() override {
        return new Volvo(*this);    // copy ctor call
    }
};

class BMW : public Car {
private:
    // ...
    virtual void start() override {
        std::cout << "BMW has started\n";
    }
    virtual BMW* clone() override {
        return new BMW(*this);    // copy ctor call
    }
};

void car_game(Car* p) 
{
    // *p nesnesinin dinamik turu ne ise o turden bir nesne olusturmak isteniyor:
    Car* pnew = p->clone();
    p->start();
    delete p;
}

Car* create_random_car()
{
    switch (rand() % 2)
    {
    case 0: std::cout<< "Volvo uretiliyor...\n"; return new Volvo;
    case 1: std::cout<< "BMW uretiliyor...\n"; return new BMW;
    default: return nullptr;
    }
}

int main(int argc, char const *argv[])
{
    srand(static_cast<unsigned>(time(0)));
    
    for (size_t i = 0; i < 10; i++)
    {
        Car* carptr = create_random_car();
        car_game(carptr);
        (void)getchar();
        
        // delete carptr; // ileride deginilecek: virtual dtor
    }
}

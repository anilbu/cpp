#include <iostream>
#include <string>

template <typename T>
class Animal {
public:
    void make_sound()
    {
        auto s = static_cast<T*>(this)->sound();
        std::cout << s << '\n';
    }
};

class Dog: public Animal<Dog>
{
public:
    std::string sound() const
    {
        return "hav hav!!!";
    }
};

class Cat: public Animal<Cat>
{
public:
    std::string sound() const
    {
        return "miyav miyav!!!";
    }
};

class Lamb: public Animal<Lamb>
{
public:
    std::string sound() const
    {
        return "meeeeeeee!!!";
    }
};

template <typename T>
void func(Animal<T>& x)
{
    x.make_sound();
}

int main(int argc, char const *argv[])
{
    using namespace std;

    Dog karabas;
    Cat minnos;
    Lamb kuzucuk;

    karabas.make_sound();
    minnos.make_sound();
    kuzucuk.make_sound();

    func(karabas);
    func(minnos);
    func(kuzucuk);
}

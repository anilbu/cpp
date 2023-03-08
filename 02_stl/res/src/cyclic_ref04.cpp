#include <iostream>
#include <memory>
#include <list>
#include "person.h"



int main(int argc, char const *argv[])
{
    using namespace std;

    {
        list<shared_ptr<Person>> plist;

        for (int i = 0; i < 3; ++i)
        {
            auto sp = make_shared<Person>("person" + std::to_string(i));
            plist.push_back(sp);
        }
        std::cout << "Kaynaklar plist icinde shared_ptr ile tutuldugu icin plist yok edilene kadar release edilmedi\n";
    }
    std::cout << "------------------------\n";
    {
        list<weak_ptr<Person>> plist;

        for (int i = 0; i < 3; ++i)
        {
            auto sp = make_shared<Person>("person" + std::to_string(i));
            plist.push_back(sp);
        }
        std::cout << "Kaynaklar release edildi\n";
    }
    std::cout << "------------------------\n";

}
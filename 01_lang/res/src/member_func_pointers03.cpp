#include <iostream>
#include <functional>
#include "date.h"

class Fighter { 
public:
    int power() const;
    int age() const;
    int no_of_bullets() const;
    int no_of_children() const;
};

void game_xyz(const Fighter& f, int(Fighter::*fptr)() const)
{
     auto val = (f.*fptr)();
}

int main(int argc, char const *argv[])
{
    Fighter f;
    
    game_xyz(f, &Fighter::age);
    game_xyz(f, &Fighter::no_of_bullets);
}

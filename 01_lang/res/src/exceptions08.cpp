#include <iostream>


class Member {
public:
    Member() {
        std::cout << "Member()\n";
    }

    ~Member() {
        std::cout << "~Member()\n";
    }
};

class AnotherMember{
public:
    AnotherMember() { 
        throw std::out_of_range{ "hata...." };
        std::cout << "AnotherMember()\n";
    }
    
    ~AnotherMember() { 
        std::cout << "~AnotherMember()\n";
    }
};

class Nec {
public:
    ~Nec() {
        std::cout << "~Nec()\n";
    }
private:
    Member mx;
    AnotherMember my;
};




int main(int argc, char const *argv[])
{
    try {
        Nec nec;    // ne Member ne de Nec'in dtor'u cagrilmaz
    }
    catch (const std::exception& ex) {
        std::cout << "Exception caught: " << ex.what() << '\n';
    }
}

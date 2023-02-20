#include <iostream>


class Member {
public:
    Member() {
        std::cout << "Member()\n";
        throw std::out_of_range{ "hata...." };
    }

    ~Member() {
        std::cout << "~Member()\n";
    }
};

class Nec {
public:
    ~Nec() {
        std::cout << "~Nec()\n";
    }
private:
    Member mx;
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

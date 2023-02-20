#include <iostream>

class Base {
public:
  Base(int x) {
    std::cout << "Base(int) x = " << x << '\n';
  }
};

class Der: public Base {
public:
  Der(): Base(0)
  {
  }
};



int main(int argc, char const *argv[])
{
  Der Der;
}

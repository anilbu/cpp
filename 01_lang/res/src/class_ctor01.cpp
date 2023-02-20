#include <iostream>
#include <string>

using namespace std;

class Myclass
{
public:
  Myclass(std::string name = "") : _name{name}
  {
    cout << "[" << _name << "] default ctor this = " << this << '\n';
  }

  ~Myclass()
  {
    cout << "[" << _name << "] dtor this = " << this << '\n';
  }

  void func()
  {
    std::cout << "[" << _name << "] Myclass::func()\n";
  }

private:
  std::string _name;
};

// global sinif nesneleri
Myclass g1{"g1"};
Myclass g2{"g2"};
Myclass g3{"g3"};

void foo()
{
  cout << "foo cagrildi\n";

  // static yerel sinif nesneleri
  static Myclass static_m{"static_m"};

  cout << "foo sona eriyor\n";
}

int main(int argc, char const *argv[])
{
  cout << "main basladi\n";

  cout << "&g1 = " << &g1 << '\n';

  foo();
  foo();

  // otomatik omurlu sinif nesneleri
  if (true)
  {
    cout << "scope basladi\n";

    Myclass m{"m"};
    cout << "&m = " << &m << '\n';

    cout << "scope sona eriyor\n";
  }

  for (int i = 0; i < 3; ++i)
  {
    Myclass m_i{"m_" + to_string(i)};
  }

  // dinamik omurlu sinif nesneleri
  Myclass *p;
  
  {
    p = new Myclass{"m_dynamic"};
  }
  
  p->func();
  delete p;

  cout << "main sona eriyor\n";
}

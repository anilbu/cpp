// (1)
class Myclass { 
public: 
    void func(int);
};

void func(int, int);  // Function overloading mi degil mi? Degil, scopelar farkli.

void Myclass::func(int x) { 
    func(10, 20);   // Bu kod derlendiginde once isim arama yapilmasindan dolay 
                    // once class scope'da bulunacak. Ancak gecersiz parametreler ile cagrilmis.
                    
    ::func(10, 20); // gecerli: global func cagrisi
}
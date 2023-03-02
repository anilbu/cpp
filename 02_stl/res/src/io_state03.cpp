#include <iostream>



int main(int argc, char const *argv[])
{
    using namespace std;
    
    int x;
    std::cout << "bir tam sayi girin:";
    
    cin >> x;   // type murat
    cout << "cin nesnesi " << (cin ? "good" : "failed") << " durumda\n";
    
    cin.clear();
    
    string str;
    cin >> str; // onceki islem fail oldugu icin str degismedi
    std::cout << "[" << str << "]\n";
}

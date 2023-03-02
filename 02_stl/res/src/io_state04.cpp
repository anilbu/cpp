#include <iostream>



int main(int argc, char const *argv[])
{
    using namespace std;
    int x;

    while (true) {
        cout << "tam sayi girin: ";
        cin >> x;
        if (cin.good())
            break;
        if (cin.eof()) {
            cout << "giris yapilmadi\n";
            cin.clear();
        }
        else if (cin.bad()) {
            cout << "kritik hata\n";
            throw std::runtime_error{"kritik hata"};
        }
        else {
            string str;
            cin.clear();
            cin >> str;
            cout << "[" << str << "] gecerli bir tam sayi degil\n";
        }
    }
}

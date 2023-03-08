#include <iostream>
#include <memory>
#include <string>

class Cat {
public:
    Cat(const std::string& __name): m_name{ __name } {}
    ~Cat()
    {
        std::cout << "~Cat() name = " << m_name << '\n';
    }

    bool has_friend() const {
        return !mp_friend.expired();
    }

    void print() const {
        std::cout << "benim adim " << m_name << ", ";
        if (auto sp = mp_friend.lock())
        {
            std::cout << "benim bir arkadasim var onun ismi " << sp->m_name << '\n';
        }
        else {
            std::cout << "benim henuz bir arkadasim yok\n";
        }
    }

    void make_friend(std::shared_ptr<Cat> __sp) {
        mp_friend = __sp;
        std::cout << m_name << " ile " << __sp->m_name << " arkadas oldu\n";
    }

private:
    std::string m_name;
    std::weak_ptr<Cat> mp_friend;
};

int main(int argc, char const *argv[])
{
    using namespace std;

    auto sp1 = make_shared<Cat>("pamuk");
    auto sp2 = make_shared<Cat>("komur");

    sp1->print();
    sp2->print();

    sp1->make_friend(sp2);
    sp2->make_friend(sp1);

    sp1->print();
    sp2->print();
}
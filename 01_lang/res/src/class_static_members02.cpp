#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Ninja
{
public:
    Ninja(const std::string name) : m_name{name}
    {
        svec.push_back(this);
    }

    Ninja(const Ninja&) = delete;
    Ninja& operator=(const Ninja&) = delete;

    ~Ninja() 
    {
        // (1) C++20
        // std::erase(this);
        
        // (2) C++17
        // if(auto iter = std::find(svec.begin(), svec.end(), this); iter != svec.end()) 
        //     svec.erase(iter);
        
        // (3)
        svec.erase(std::remove(svec.begin(), svec.end(), this), svec.end());
    }
    
    void call_friends()
    {
        std::cout << "Arkadaslar yetisin, ben Ninja "<< m_name << '\n';
        for (auto n : svec)
        {
            if(n != this)
                std::cout << n->m_name << " ";
        }
        std::cout << "\nDusmanlar saldiriyor!!\n";
    }

private:
    std::string m_name;
    inline static std::vector<Ninja*> svec{};
};

int main(int argc, char const *argv[])
{
    Ninja n1{"mahmut"};
    Ninja n2{"suheyla"};
    Ninja *p1{new Ninja{"aleaddin"}};
    Ninja *p2{new Ninja{"hayrullah"}};

    p1->call_friends();
    
    delete p2;
    
    p1->call_friends();
}

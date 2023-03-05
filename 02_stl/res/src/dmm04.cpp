#include <iostream>
#include <new>
#include <vector>

void custom_new_handler() 
{
    static int cnt{};

    // loglama islerini yapti...
    std::cout << "my_new_handler " << ++cnt << ". kez cagrildi\n";
    
    if(cnt == 5) {
        // 3. ihtimal:
        // baska bir handler set edilerek farkli bir islev calistirilir
        std::set_new_handler(custom_new_handler2);
    }
    
    if(cnt == 10){ 
        // 1. ihtimal:
        // operator new kendisi exception throw eder
        std::set_new_handler(nullptr);
        cnt = 0;
    }
    
    // 2. ihtimal:
    // bad_alloc turunden exception throw edilebilir
}

void custom_new_handler2()
{
    std::cout << "another_handler cagrildi\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    std::set_new_handler(custom_new_handler);
    
    vector<void*> mvec;
    try
    {
        for(;;)
        {
            mvec.push_back(operator new(1024 * 1024));
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

#include <iostream>
#include <vector>

using new_handler = void(*)();

new_handler g_handler;

//  std::get_new_handler()
new_handler Get_new_handler()
{
    return g_handler;
}

//  std::set_new_handler()
new_handler Set_new_handler(new_handler handler)
{
    new_handler old_handler = g_handler;
    g_handler = handler;
    return old_handler;
}

void* operator new(size_t n)
{
  while(true) 
  {
    // Eger bellek tahsisi basarili olursa donguden cikacaktir.
    void* vp = std::malloc(n);
    if(vp)
      return vp;
    
    auto handler = Get_new_handler();
    if(!handler)
      throw std::bad_alloc{};
    
    handler();
  }
}


void custom_new_handler2()
{
    std::cout << "another_handler cagrildi\n";
}


void custom_new_handler() 
{
    static int cnt{};

    // loglama islerini yapti...
    std::cout << "custom_new_handler " << ++cnt << ". kez cagrildi\n";
    
    if(cnt == 5) {
        // 2. ihtimal:
        // std::Set_new_handler(another_handler);
        Set_new_handler(&custom_new_handler2);
    }
    
    if(cnt == 10){ 
        // 1. ihtimal:
        // std::Set_new_handler(nullptr);
        Set_new_handler(nullptr);
        cnt = 0;
    }
    
    // 3. ihtimal:
    // bad_alloc turunden exception throw edildi.
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    Set_new_handler(&custom_new_handler);
    
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

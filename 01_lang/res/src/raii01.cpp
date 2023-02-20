#include <iostream>
#include <memory>

class File
{
public:
    File(const char *p) : mp{p}
    {
        std::cout << mp << " isimli dosya acildi\n";
    }
    
    void write(const char*);
    
    ~File()
    {
        std::cout << mp << " isimli dosya kapatildi\n";
    }

private:
    const char *mp;
};

int main(int argc, char const *argv[])
{
    std::cout << "main basladi\n";
    {
        File f{"deneme.txt"};
        File* p = new File{"dynamic_deneme.txt"}; // deallocate edilmeyecek, cunku delete edilmiyor
        
        std::shared_ptr<File> s_p = std::make_shared<File>("shared_ptr_deneme.txt");
        std::unique_ptr<File> u_p = std::make_unique<File>("unique_ptr_deneme.txt");
    }

    std::cout << "main sonlanmak uzere\n";
}

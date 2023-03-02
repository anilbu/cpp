#include <iostream>

class Formatter
{
public:
    Formatter(std::ostream& os) : _os{os}
    {
        // os.setf();
    }
    
    ~Formatter(){
        // _os.unsetf();
    }
private:
    std::ostream& _os;
};


int main(int argc, char const *argv[])
{
    using namespace std;
    Formatter fmt { cout };
    
    
}

#include <iostream>
#include <vector>
#include <string>


int main(int argc, char const *argv[])
{
    using namespace std;
    string name {"necati ergin"};
    
    vector<string> svec;
    
    svec.push_back(name);             // lval ref calls vector<string>::push_back(const string&)
    svec.push_back(std::move(name));  // rval ref calls vector<string>::push_back(string&&)
    
    // emplace_back'in kendisi bir function template'dir. Bu nedenle tur icin cikarim yapilir.
    svec.emplace_back("test");        // vector<string>::emplace_back<T>(T&&)
}

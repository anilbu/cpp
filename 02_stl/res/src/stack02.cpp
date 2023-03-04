#include <iostream>
#include <stack>
#include <string>
#include "nutility.h"

// Parantezler dogru bir bicimde match oluyor mu?
bool is_matching(const std::string& str)
{
    if(str.empty())
        return true;

    std::stack<char> s{};
    
    for (const auto&c : str)
    {
        if(s.empty()){
            s.push(c);
        }
        else if((s.top() == '(' && c == ')') ||
                (s.top() == '<' && c == '>') ||
                (s.top() == '[' && c == ']') ||
                (s.top() == '{' && c == '}')
        ) {
            s.pop();
        }
        else {
            s.push(c);
        }
    }
    
    return s.empty();
}

int main(int argc, char const *argv[])
{
    using namespace std;

    string str = "(([]<>))";
    std::cout << "is_matching(\""<< str <<"\") = " << is_matching(str) << '\n';
    
    str = "(((<>{}())))";
    std::cout << "is_matching(\""<< str <<"\") = " << is_matching(str) << '\n';
    
    str = "((((<>{}())))";
    std::cout << "is_matching(\""<< str <<"\") = " << is_matching(str) << '\n';
}

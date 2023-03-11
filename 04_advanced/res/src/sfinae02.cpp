#include <type_traits>

template <typename T>
class A : public std::void_t {
    
};

int main(int argc, char const *argv[])
{
    A<int> ax;
}
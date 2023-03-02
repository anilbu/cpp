#include <iostream>

void print_stream_state(const std::istream& is)
{
    std::cout << "failbit:" << (is.rdstate() & ios::failbit ? "set" : "unset") << '\n';
    std::cout << "eofbit :" << (is.rdstate() & ios::eofbit ? "set" : "unset") << '\n';
    std::cout << "badbit :" << (is.rdstate() & ios::badbit ? "set" : "unset") << '\n';
}

int main(int argc, char const *argv[])
{
    using namespace std;

    print_stream_state(std::cin);

    int x;
    cin >> x;

    print_stream_state(std::cin);

}

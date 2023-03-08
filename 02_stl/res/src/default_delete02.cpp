#include <iostream>
#include <memory>
#include <functional>
#include <cstdio>

int main(int argc, char const *argv[])
{
    using namespace std;

    auto fdel = [](FILE* p) {
        std::cout << "closed\n";
        fclose(p);
    };

    unique_ptr<FILE, decltype(fdel)> up{ fopen("/tmp/sample.txt", "w") };
    fprintf(up.get(), "ocak ayinin 22si hava hala cok sicak\n");
}
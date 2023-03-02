#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>



int main(int argc, char const *argv[])
{
    using namespace std;

    {
        list<string> slist_src {"ali", "ayse", "mehmet"};

        std::for_each(slist_src.begin(), slist_src.end(), [](string& s) {
            s += "can";
            std::cout << s << '\n';
        });
    }
    {
        class Nec {
        public:
            void operator()(const string& s) {
                std::cout << (char)toupper(s.front()) << (char)toupper(s.back()) << '\n';
                m_count++;
            }

            int count() const {
                return m_count;
            }
        private:
            int m_count{};
        };


        list<string> slist_src {"ali", "ayse", "mehmet"};

        auto f = std::for_each(slist_src.begin(), slist_src.end(), Nec{});
        cout << f.count() << '\n';
    }

}

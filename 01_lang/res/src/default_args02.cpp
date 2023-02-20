#include <iostream>
#include <ctime>

void process_date(int day = -1, int mon = -1, int year = -1)
{
    if (year == -1) {
        std::time_t timer;
        std::time(&timer);
        std::tm* tp = std::localtime(&timer);
        year = tp->tm_year + 1900;
        if (mon == -1) {
            mon = tp->tm_mon + 1;
            if (day == -1) {
                day = tp->tm_mday;
            }
        }
    }

    std::cout << day << '/' << mon << '/' << year << std::endl;
}

// Benzer sekilde pointerlar icin nullptr kullanimi oldukca yaygindir
void func(int x, int* ptr = nullptr)
{
    if (ptr) {
        *ptr = x * x;
    }
}

int main(int argc, char const *argv[])
{
    process_date(10, 5, 1993);
    process_date(10, 5);
    process_date(10);
    process_date();
}

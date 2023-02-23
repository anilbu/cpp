#include <iostream>

template<typename T>
struct ValCat {
	constexpr static const char *p = "PR Value";
};

template<typename T>
struct ValCat<T&> {
	constexpr static const char *p = "L Value";
};

template<typename T>
struct ValCat<T&&> {
	constexpr static const char *p = "X Value";
};


#define print_val_cat(expr) std::cout << "Value category of expr '" #expr "' is " << ValCat<decltype((expr))>::p << std::endl

int foo1() { return 1; }
int& foo2();

int main()
{
	int x = 10;
	int* p = &x;
    print_val_cat(x);       		// lvalue
    print_val_cat(x + 5);   		// rvalue
	print_val_cat(10);				// prvalue
	print_val_cat(foo1());			// prvlaue
	print_val_cat(*p);				// lvalue
	print_val_cat(std::move(x));	// xvalue
	print_val_cat(foo2());			// lvalue
	
}
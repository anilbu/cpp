#ifndef NUTILITY_H
#define NUTILITY_H

#include <random>
#include <string>
#include <iostream>
#include <set>
#include <forward_list>
#include <utility>

class Irand {
public:
	Irand() = default;
	Irand(int min, int max) : m_dist{ min, max } {}
	int operator()();
private:
	std::uniform_int_distribution<int> m_dist;
};


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

class Drand {
public:
	Drand() = default;
	Drand(double dmin, double dmax) : m_dist{ dmin, dmax } {}
	double operator()();
private:
	std::uniform_real_distribution<double> m_dist;
};


void		randomize();
[[nodiscard]] std::string rname();
[[nodiscard]] std::string rfname();
[[nodiscard]] std::string rtown();
[[nodiscard]] std::string rperson();

[[nodiscard]] 
constexpr bool isprime(int val)
{
	if (val < 2)
		return false;

	if (val % 2 == 0)
		return val == 2;

	if (val % 3 == 0)
		return val == 3;

	if (val % 5 == 0)
		return val == 5;

	for (int k = 7; k * k <= val; k += 2)
		if (val % k == 0)
			return false;

	return true;
}

std::ostream& dline(std::ostream& os);
//--------------------------------------------------
//--------------------------------------------------
constexpr int ndigit(int val)
{
	if (val == 0)
		return 1;

	int digit_count = 0;

	while (val != 0) {
		val /= 10;
		++digit_count;
	}

	return digit_count;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p)
{
	return os << "[" << p.first << ", " << p.second << "]";
}
//--------------------------------------------------
//--------------------------------------------------
template<typename C, typename F>
void rfill(C& c, size_t n, F frand)
{
	while (c.size() < n)
		c.insert(c.end(), frand());
}

//--------------------------------------------------
//--------------------------------------------------

template<typename T, typename F>
void rfill(std::forward_list<T>& c, size_t n, F frand)
{
	while (n--)
		c.insert_after(c.before_begin(), frand());
}


template<typename C>
void print(const C& c, const char* p = " ", std::ostream& os = std::cout)
{
	for (const auto& elem : c)
		os << elem << p;
	os << dline;
}
//--------------------------------------------------
//--------------------------------------------------

template<typename InIter>
void print(InIter beg, InIter end, const char* p = " ", std::ostream& os = std::cout)
{
	while (beg != end) {
		os << *beg++ << p;
	}
	os << dline;
}

//--------------------------------------------------
//--------------------------------------------------

template<typename C, typename F>
void fcs(C& c, size_t n, F func)
{
	std::set<typename C::value_type> s;
	while (s.size() != n)
		s.insert(func());
	c.assign(s.begin(), s.end());
}

//--------------------------------------------------
//--------------------------------------------------

void my_terminate();

//--------------------------------------------------
//--------------------------------------------------

// template <typename T, typename U>
// std::ostream& operator<<(std::ostream& os, const std::pair<T,U>& p)
// {
// 	return os << '[' << p.first << ',' << p.second << ']';
// }

//--------------------------------------------------
//--------------------------------------------------

#endif

#ifndef NUTILITY_H
#define NUTILITY_H

#include <random>
#include <string>
#include <iostream>
#include <set>
#include <forward_list>
#include <utility>
#include <fstream>
#include <filesystem>
#include <functional>

#ifdef __GNUG__
#include <boost/core/demangle.hpp>
#endif

inline std::string _demangle(const char* tname)
{
#ifdef __GNUG__
	return boost::core::demangle(tname);
#else
	return string{tname};
#endif
}

void gen_text_ifnexists(const std::string& filename, std::function<void(std::ostream&)> func, bool force = false);
void gen_bin_ifnexists(const std::string& filename, std::function<void(std::ostream&)> func, bool force = false);

std::ofstream create_text_file(const std::string& filename);
std::ofstream create_binary_file(const std::string& filename);
std::ifstream open_text_file(const std::string& filename);
std::ifstream open_binary_file(const std::string& filename);

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

class Irand {
public:
	Irand() = default;
	Irand(int min, int max) : m_dist{ min, max } {}
	int operator()();
private:
	std::uniform_int_distribution<int> m_dist;
};

//--------------------------------------------------
//--------------------------------------------------

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

template<class Ch, class Tr, class Tuple, std::size_t... Is>
void __print_tuple_impl(std::basic_ostream<Ch,Tr>& os,
                      const Tuple& t,
                      std::index_sequence<Is...>)
{
    using swallow = int[];
    (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
}

template<class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr>& os,
                          const std::tuple<Args...>& t)
{
    os << "(";
    __print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
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

template<typename C>
void printp(const C& c, const char* p = " ", std::ostream& os = std::cout)
{
	for (const auto& elem : c)
		os << *elem << p;
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

class de { 
public:
	constexpr de(long long _val, char _delim = '.') : val { _val }, delim{_delim} {}
	
	friend std::ostream& operator<<(std::ostream& os, de x)
	{
		auto s = std::to_string(x.val);
		if(s[0] == '-') {
			os << '-';
			s.erase(0,1);
		}
		auto len = s.length();
		for (size_t i = 0; i < len; ++i)
		{
			os << s[i];
			auto n = len - 1 - i;
			if(n && (len - 1 - i) % 3 == 0)
				os << x.delim;
		}
		
		return os;
	}
	
private:
	long long val;
	char delim;
};

//--------------------------------------------------
//--------------------------------------------------

#endif

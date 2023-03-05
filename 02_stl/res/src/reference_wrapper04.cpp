#include <vector>
#include <algorithm>
#include <iterator>


struct Biggie
{
	bool operator()(int i) const
	{
		//code
		return true;
	}
	
    char buf[1024] {};
};

const Biggie gbig;

std::vector<int> ivec;

int main()
{
	std::vector<int> destvec;
	std::copy_if(ivec.begin(), ivec.end(), back_inserter(destvec), std::ref(gbig));
}
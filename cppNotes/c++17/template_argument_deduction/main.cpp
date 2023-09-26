#include <iostream>
#include <string>
#include <utility>

template<typename T>
class myCtorTypeDeduction
{
	T val;
	public:
	myCtorTypeDeduction(T t) : val{t} {}
	void printVal() { std::cout << "val: " << val << std::endl; }
};

int main()
{
	auto val = 5;
	//1. 
	myCtorTypeDeduction obj(val); obj.printVal();
	//vs
	myCtorTypeDeduction<int> obj1(10); obj1.printVal();

	//2. 
	auto myPair1 = std::pair<int, int>(14, 15);
	auto myPair2 = std::make_pair<int, std::string>(14, "naseeb");
	//vs
	auto myPair3 = std::pair(14, 15);
	auto myPair4 = std::make_pair(14, "naseeb");
	return 0;
}

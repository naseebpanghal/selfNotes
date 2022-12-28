#include <iostream>

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
	myCtorTypeDeduction obj(val); obj.printVal();
	//vs
	myCtorTypeDeduction<int> obj1(10); obj1.printVal();

	return 0;
}

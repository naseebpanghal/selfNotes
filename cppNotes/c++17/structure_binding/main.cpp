#include <utility>
#include <iostream>

using namespace std;

class base
{
	public:
		int val { 5 };
};
auto func()
{
	base b;
	b.val = 10;
	int temp = 6;
	return make_pair<base, int>(std::move(b), 6);
}

int main()
{
	auto [ myBase, myInt ] = func();
	std::cout << "myBase::val: " << myBase.val << std::endl;
	return 0;
}


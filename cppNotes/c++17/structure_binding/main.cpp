#include <utility>
#include <map>
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
	//structure binding
	auto [ myBase, myInt ] = func();
	std::cout << "myBase::val: " << myBase.val << std::endl;

	std::map<string, int> studentMarks = { {"naseeb", 80}, {"mahi", 95}};
	for(auto [key, value] : studentMarks)
	{
		std::cout << "Name: " << key << " Marks: " << value << std::endl;
	}
	return 0;
}


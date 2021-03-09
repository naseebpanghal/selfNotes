#include <iostream>
#include <forward_list>

int main()
{
  std::forward_list<int> my_f_list;
  my_f_list.push_front(1);
  my_f_list.push_front(2);

  for(auto ref : my_f_list) std::cout << "value: " << ref << std::endl;
	return 0;
}

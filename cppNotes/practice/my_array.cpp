#include <iostream>
#include <array>

int main()
{
  std::array<int, 6> my_array {1, 2, 3, 4, 5, 6};

  //print array
  for(auto &val: my_array) std::cout << "value: " << val << std::endl;

  std::cout << "Value at index 4: " << my_array[4] << std::endl;
	return 0;
}

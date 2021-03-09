#include <iostream>
#include <deque>

int main()
{
  std::deque<int> my_deque {4, 5, 2, 6};

  //insert
  my_deque.push_front(1);
  my_deque.push_back(9);
  //erase
  my_deque.erase(my_deque.begin() + 2);
  //emplace_back
  my_deque.emplace_back(24);
  my_deque.emplace_front(42);
  for(int ref : my_deque) std::cout << ref << std::endl;

  std::cout << "Max size: " << my_deque.size() << std::endl;
  auto value = my_deque.front();
  std::cout << "value popped: " << value << std::endl;
  my_deque.pop_front();
  std::cout << "Max size: " << my_deque.size() << std::endl;
	return 0;
}

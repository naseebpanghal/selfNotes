#include <iostream>

template <typename T>
void my_func(T t)
{
//  std::cout << "value passed is: " << t << std::endl;
}
template <typename T> struct value 
{
  T t;
};

struct another
{
  int j;
  char *k;
  struct value<int> t;
};
int main()
{
  struct value<int> temp{10};
  struct another other{5,"naseeb Panghal",7}; 
  my_func(temp);
  return 0;
}

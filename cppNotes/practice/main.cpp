#include <iostream>

template<typename...> struct Tuple {};
template<typename T1, typename T2> struct Pair {};
template<class ...Args1> struct zip {
    template<class ...Args2> struct with {
        typedef Tuple<Pair<Args1, Args2>...> type;
//        Pair<Args1, Args2>... is the pack expansion
//        Pair<Args1, Args2> is the pattern
    };
};
template <typename T>
void my_func(T t)
{
//  std::cout << "value passed is: " << t << std::endl;
}
int main()
{
  std::integral_constant<int, 5> temp;
  std::integral_constant<int, 10> temp2;
  temp<int, 5>::type var1;
//  std::cout << "value: " << temp::value << endl;

  return 0;
}

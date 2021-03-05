#include <iostream>
#include <memory>

class A{
  public:
    //int a{10};
    A(){std::cout << "A\n";}
    ~A(){std::cout << "~A\n";}
    A(const A&)=delete; //copy cons
    A& operator=(const A&)=delete; // copy ass
    A(A&&){std::cout << "move\n";} // move con
    A& operator=(A&& other){ // move ass
      std::cout << "move ass\n";
      return other;
    }
};

auto func(A a)
{
  //std::cout << a.a << '\n';
  //return std::move(a);    
  return a;
}   
int main()
{   
  A a;
  //std::cout << a.a << '\n';
  a = func(std::move(a));
  //std::cout << a.a << '\n';
}  

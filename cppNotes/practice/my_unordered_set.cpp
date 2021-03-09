#include <iostream>
#include <unordered_set>
#include <algorithm>


int insert_set(std::unordered_set<int> &myset, int &&val)
{
  auto ret = myset.insert(val);
  if(ret.second == true) std::cout << "insert successfull" << std::endl;
  else std::cout << "insert failed" << std::endl;
  return 0;
}
int main()
{
  std::unordered_set<int> myset;
  insert_set(myset, 1);
  insert_set(myset, 3);
  insert_set(myset, 4);
  insert_set(myset, 6);
  insert_set(myset, 5);
  insert_set(myset, 2);

  //for(std::set<int>::iterator it = myset.begin(); it != myset.end(); it++) std::cout << it << std::endl;
  //for(auto it = myset.begin(); it != myset.end(); it++) std::cout << it << std::endl;
  for(auto it: myset) std::cout << it << std::endl;

  for_each(myset.begin(), myset.end(), [](const int val) 
      {
      std::cout << "value: " << val << std::endl;
      }
      );


  auto value = myset.find(7);
  if(value != myset.end()) std::cout << "Value found: " << *value << std::endl;
  else std::cout << "Value not found" << std::endl;

  

  for(auto it: myset) std::cout << it << std::endl;
  return 0;
}

#include <iostream>
#include <map>

int map_insert(std::map<int, int> &mymap, std::pair<int,int> &&my_pair)
{
  auto ret = mymap.insert(my_pair);
  if(ret.second == true) std::cout << "pair is inserted successfully" << std::endl;
  else std::cout << "key already exist" << std::endl;
}
int main()
{
  std::map<int, int> mymap;

  //Insert something into the map
  map_insert(mymap, std::pair<int, int>(1,2));
  map_insert(mymap, std::pair<int, int>(2,4));

  //Lets go to find the value
  auto val = mymap.find(1);
  if(val != mymap.end()) std::cout << "value found: " << val->second << std::endl;
  else std::cout << "value doesn't exist" << std::endl; 

  return 0;

}

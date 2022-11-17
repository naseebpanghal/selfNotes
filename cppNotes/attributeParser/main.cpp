#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

vector<string> tag_stack;
map<string, string> attrs;
void insert_attr(string key, string value)
{
	string full_key;
	for(auto str : tag_stack)
	{
		full_key += str + ".";
	}
	full_key.pop_back();
	full_key += "~" + key;
	attrs[full_key] = value;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int N, Q;
	cin >> N >> Q;
	while(N--)
	{
		char ch; cin >> ch;
		if(cin.peek() == '/') //closing tag
		{
			string temp;
			cin >> temp;
			tag_stack.pop_back();
		}
		else
		{
			string tag; cin >> tag;
			if(tag.back() == '>')
			{
				tag.pop_back();
				tag_stack.push_back(tag);
			}
			else
			{
				tag_stack.push_back(tag);
				for(;;)
				{
					string attr_name, eq, attr_val;
					cin >> attr_name >> eq >> attr_val;
					if(attr_val.back() == '>') //last attr
					{
						attr_val.pop_back();
						attr_val.pop_back();
						attr_val = attr_val.substr(1);
						insert_attr(attr_name, attr_val);
						break;
					}
					else
					{
						attr_val.pop_back();
						attr_val = attr_val.substr(1);
						insert_attr(attr_name, attr_val);
					}
				}
			}
		}
	}

	while(Q--)
	{
		string query;
		cin >> query;
		if(attrs.find(query) != attrs.end())
			cout << attrs[query] << endl;
		else
			cout << "Not Found!" << endl;
	}
	return 0;
}


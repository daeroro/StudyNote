#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	vector< pair<int, string> > v;

	v.push_back(pair<int, string>(90, "Lee"));
	v.push_back(pair<int, string>(92, "Park"));
	v.push_back(pair<int, string>(88, "Koo"));

	sort(v.begin(), v.end());
	
	for(int i=0; i<v.size(); i++)
		cout << v[i].second <<' ' <<endl;

	return 0;
}

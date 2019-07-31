#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(pair< string, pair<int, int> > a,
		pair< string, pair<int, int> > b)
{
	if(a.second.first == b.second.first)
	{
		return a.second.second > b.second.second;
	}
	else
	{
		return a.second.first > b.second.first;
	}
}	

int main(void)
{
	vector< pair< string, pair<int, int> > > v;
 
	v.push_back(pair< string, pair<int, int> >("Lee", make_pair(90, 1992)));
	v.push_back(pair< string, pair<int, int> >("Park", make_pair(92, 1992)));
	v.push_back(pair< string, pair<int, int> >("Song", make_pair(97, 1993)));
	v.push_back(pair< string, pair<int, int> >("Kim", make_pair(92, 1994)));

	sort(v.begin(), v.end(), comp);

	for(int i=0; i<v.size(); i++)
		cout << v[i].first << ' ' << endl;

	return 0;
}

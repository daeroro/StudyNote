#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstring>

using namespace std;

bool comp(pair<string, int> a, pair<string, int> b)
{
	if(a.second == b.second)
		return a.first < b.first;
	else
		return a.second < b.second;
}

int main(void)
{
	int i, num;
	char word[51];
	vector<pair<string, int> > v;
	pair<string, int> tmp;

	scanf("%d", &num);

	for(i=0; i<num; i++)
	{
		scanf("%s", word);
		v.push_back(pair<string, int>(word, strlen(word)));
	}

	sort(v.begin(), v.end(), comp);

	tmp = v[0];
	cout << tmp.first<<endl;

	for(i=1; i<num; i++)
	{   
		if(v[i].first != tmp.first)
			cout << v[i].first << endl;
		tmp = v[i];
	}
	return 0;
}

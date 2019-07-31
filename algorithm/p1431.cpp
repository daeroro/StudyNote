#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>
#include <cstring>

using namespace std;

int num;

bool comp(string a, string b)
{
	int a_sum = 0, b_sum = 0;

	if(a.length() != b.length())
		return a.length() < b.length();
	else
	{
		for(int i = 0; i<a.length(); i++)
		{
			if(a[i] < 58)
				a_sum += a[i] - '0';

			if(b[i] < 58)
				b_sum += b[i] - '0';
		}

		if(a_sum != b_sum)
			return a_sum < b_sum;

		return a<b;
	}

}

int main(void)
{
	int i;

	char serial[51];
	vector<string>v;
	
	scanf("%d", &num);

	for(i=0; i<num; i++)
	{
		scanf("%s", serial);
		v.push_back(serial);
	}
	

	sort(v.begin(), v.end(), comp);

	for(i=0; i<v.size(); i++)
		cout << v[i] <<endl;

	return 0;
}

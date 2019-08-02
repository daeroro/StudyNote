#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>

#define NODE 7
#define NUM	11

using namespace std;

vector <pair<int, pair<int, int> > > v;
vector <int> node[NODE+1];
int arr[NUM+1];

//function declaration
void kruskal(void);

int getParent(int min);
void unionFunc(int a, int b);
bool unionFind(int a, int b);


bool comp(pair<int, pair<int, int> > a, pair<int, pair<int, int> > b)
{
	return a.first < b.first;
}


//main
int main(void)
{
	int i;

	//Union Find array initialization
	for(i=1; i<=NUM; i++)
	{
		arr[i] = i;
	}
	
	//Node informations are inserted to the vector v.

	v.push_back(pair<int, pair<int, int> >(12, make_pair(1, 7)));
	v.push_back(pair<int, pair<int, int> >(13, make_pair(4, 7)));
	v.push_back(pair<int, pair<int, int> >(17, make_pair(1, 5)));
	v.push_back(pair<int, pair<int, int> >(20, make_pair(3, 5)));
	v.push_back(pair<int, pair<int, int> >(24, make_pair(2, 4)));
	v.push_back(pair<int, pair<int, int> >(28, make_pair(1, 4)));
	v.push_back(pair<int, pair<int, int> >(37, make_pair(3, 6)));
	v.push_back(pair<int, pair<int, int> >(45, make_pair(5, 6)));
	v.push_back(pair<int, pair<int, int> >(62, make_pair(2, 5)));
	v.push_back(pair<int, pair<int, int> >(67, make_pair(1, 2)));
	v.push_back(pair<int, pair<int, int> >(73, make_pair(5, 7)));

	//Sorting vector v
	sort(v.begin(), v.end(), comp);
	
	//Printing sorted vector v
	for(i=0; i<NUM; i++)
		printf("%d - %d : %d\n", v[i].second.first, v[i].second.second, v[i].first);
	printf("\n");

	//kruskal
	kruskal();

	return 0;
}

//function
void kruskal(void)
{
	int i, j, a, b;
	int cost = 0;
	
	for(i=0; i<NODE; i++)
	{
		a = v[i].second.first;
		b = v[i].second.second;

		if(!unionFind(a, b))
		{
			node[a].push_back(b);
			node[b].push_back(a);

			unionFunc(a, b);

			for(j=1; j<=NODE; j++)
				printf("%d ", arr[j]);
			printf("\n");

			cost += v[i].first;
			printf("+= %d\n", v[i].first);
		}
	}
	printf("cost = %d\n", cost);

}


int getParent(int min)
{
	int p = min;

	while(arr[p] != p)
	{
		p = arr[p];
	}
	return p;
}

void unionFunc(int a, int b)
{
	int i;
	int min = (arr[a] <= arr[b]) ? arr[a] : arr[b];
	int max = (arr[a] <= arr[b]) ? arr[b] : arr[a];
	
	if(!unionFind(a, b))
	{
		for(i=1; i<=NODE; i++)
		{
			if(arr[i] == max)
			{
				arr[i] = min;
			}
		}	
	}
}

bool unionFind(int a, int b)
{
	if(arr[a] == arr[b])
		return 1;
	else
		return 0;
}


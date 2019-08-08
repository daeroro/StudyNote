#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>

#define NUM 6
#define INF 100000

using namespace std;

int arr1[NUM+1];
int arr2[NUM+1];
vector < pair <int, int> > v[NUM+1];
int vNum = NUM;

int find_min(int start)
{
	int i, idx, tmp;

	for(i=1; i<=NUM; i++)
	{
		if(arr2[i] != 1)
		{
			idx = i;
			break;				
		}
	}
	
	for(i=1; i<=NUM; i++)
	{
		if((arr2[i] != 1) && (arr1[i] < arr1[idx]) && (arr1[i]!= 0))
		{
			idx = i;
		}
	}
	return idx;
}

void dijkstra(int start)
{
	int i, j;
	int nidx, idx, min = 0;

	//initialize
	for(i=1; i<=NUM; i++)
		arr1[i] = INF;

	arr1[start] = 0;

	for(i=0; i < v[start].size(); i++)
	{
		arr1[v[start][i].first] = v[start][i].second;
	}
	arr2[start] = 1;

	//distance update
	for(i=vNum; i>1; i--)
	{
		idx = find_min(start);
		arr2[idx] = 1;
		
		min = arr1[idx];

		for(j=0; j<v[idx].size(); j++)
		{
			nidx = v[idx][j].first;
			min += v[idx][j].second;

			if(min < arr1[nidx])
				arr1[nidx] = min;
			
			min = arr1[idx];
		}
		
		for(j=1; j<=NUM; j++)
			printf("%d ", arr1[j]);
		printf("\n");
	}
}

int main(void)
{
	int i;

	//1-2 : 2
	v[1].push_back(pair<int, int>(2, 2));
	v[2].push_back(pair<int, int>(1, 2));

	//1-3 : 5
	v[1].push_back(pair<int, int>(3, 5));
	v[3].push_back(pair<int, int>(1, 5));

	//1-4 : 1
	v[1].push_back(pair<int, int>(4, 1));
	v[4].push_back(pair<int, int>(1, 1));
	
	//2-4 : 2
	v[2].push_back(pair<int, int>(4, 2));
	v[4].push_back(pair<int, int>(2, 2));

	//2-3 : 3
	v[2].push_back(pair<int, int>(3, 3));
	v[3].push_back(pair<int, int>(2, 3));

	//3-4 : 3
	v[3].push_back(pair<int, int>(4, 3));
	v[4].push_back(pair<int, int>(3, 3));

	//3-5 : 1
	v[3].push_back(pair<int, int>(5, 1));
	v[5].push_back(pair<int, int>(3, 1));

	//3-6 : 5
	v[3].push_back(pair<int, int>(6, 5));
	v[6].push_back(pair<int, int>(3, 5));

	//4-5 : 1
	v[4].push_back(pair<int, int>(5, 1));
	v[5].push_back(pair<int, int>(4, 1));

	//5-6 : 2
	v[5].push_back(pair<int, int>(6, 2));
	v[6].push_back(pair<int, int>(5, 2));

	dijkstra(1);

	for(i=1; i<=NUM; i++)
		printf("%d ", arr1[i]);
	printf("\n");	

	return 0;
}

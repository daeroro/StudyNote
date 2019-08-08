#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include <stdio.h>

#define NUM	6
#define INF 1000000

using namespace std;

vector <pair <int, int> > v[NUM+1];
int d[NUM+1];

void dijkstra2(int start)
{
	int i, idx, min, tmp, itmp;
	priority_queue<pair<int, int> > pq;

	//d[] initialize
	for(i=1; i<=NUM; i++)
		d[i] = INF;

	d[start] = 0;

	for(i=0; i<v[start].size(); i++)
		d[v[start][i].first] = v[start][i].second;

	for(i=1; i<=NUM; i++)
	{
		pq.push(make_pair(-d[i], i));
	}
	
//
	pq.pop();

	while(!pq.empty())
	{
 		idx = pq.top().second;
		tmp = -pq.top().first;
		pq.pop();

	//	printf("idx = %d, min = %d\n", idx, tmp);
		for(i=0; i<v[idx].size(); i++)
		{
			min = tmp + v[idx][i].second;
			itmp = v[idx][i].first;	

	//		printf("min = %d, d[] = %d\n", min, d[itmp]);
			if(min < d[itmp])
			{
				d[itmp] = min;
				pq.push(make_pair(-min, itmp));
				
			}
		}
	}

	for(i=1; i<=NUM; i++)
		printf("%d ", d[i]);
	printf("\n");	
}

int main(void)
{
	//1-2 : 2
	v[1].push_back(make_pair(2, 2));
	v[2].push_back(make_pair(1, 2));

	//1-3 : 5
	v[1].push_back(make_pair(3, 5));
	v[3].push_back(make_pair(1, 5));

	//1-4 : 1
	v[1].push_back(make_pair(4, 1));
	v[4].push_back(make_pair(1, 1));

	//2-3 : 3
	v[2].push_back(make_pair(3, 3));
	v[3].push_back(make_pair(2, 3));

	//2-4 : 2
	v[2].push_back(make_pair(4, 2));
	v[4].push_back(make_pair(2, 2));

	//3-4 : 3
	v[3].push_back(make_pair(4, 3));
	v[4].push_back(make_pair(3, 3));

	//3-5 : 1
	v[3].push_back(make_pair(5, 1));
	v[5].push_back(make_pair(3, 1));

	//3-6 : 5
	v[3].push_back(make_pair(6, 5));
	v[6].push_back(make_pair(3, 5));

	//4-5 : 1
	v[4].push_back(make_pair(5, 1));
	v[5].push_back(make_pair(4, 1));

	//5-6 : 2
	v[5].push_back(make_pair(6, 2));
	v[6].push_back(make_pair(5, 2));

	dijkstra2(1);

	return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include <cstdio>

#define NUM 6

using namespace std;

int idx;

vector<pair<int, int> >v[NUM + 1];
int visit[NUM+1];
int p[NUM];

void networkFlow(int begin, int end)
{
	int i, node, tmp;
	queue<int> q;

	q.push(begin);
	visit[begin] = 1;
	p[idx++] = begin;

	while(!q.empty())
	{
		node = q.front();
		printf("node = %d\n", node);
		q.pop();
		for(i=0; i<v[node].size(); i++)
		{
			tmp = v[node][i].first;
			if(!visit[tmp])
			{
				q.push(tmp);
				visit[tmp] = 1;;
				p[idx++] = tmp;
			}
		}
	}

	for(i=0; i<NUM; i++)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
}

int main(void)
{
	//1->2 : 12
	v[1].push_back(make_pair(2, 12));

	//1->4 : 11
	v[1].push_back(make_pair(4, 11));

	//2->3 : 6
	v[2].push_back(make_pair(3, 6));

	//2->4 : 3
	v[2].push_back(make_pair(4, 3));	

	//2->5 : 5
	v[2].push_back(make_pair(5, 5));

	//2->6 : 9
	v[2].push_back(make_pair(6, 9));

	//3->6 : 8
	v[3].push_back(make_pair(6, 8));

	//4->5 : 9
	v[5].push_back(make_pair(5, 9));

	//5->3 : 3
	v[5].push_back(make_pair(3, 3));

	//5->6 : 4
	v[5].push_back(make_pair(6, 4));

	networkFlow(1, 6);


	return 0;
}

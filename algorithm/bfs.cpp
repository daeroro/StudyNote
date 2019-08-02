#include <iostream>
#include <vector>
#include <queue>

#include <cstdio>

#define TRUE 1

using namespace std;

vector<int> adj[8];
int check[8];

void bfs(int start);

int main(void)
{
	//1-2
	adj[1].push_back(2);
	adj[2].push_back(1);

	//1-3
	adj[1].push_back(3);
	adj[3].push_back(1);

	//2-3
	adj[2].push_back(3);
	adj[3].push_back(2);
	
	//2-4
	adj[2].push_back(4);
	adj[4].push_back(2);

	//2-5
	adj[2].push_back(5);
	adj[5].push_back(2);

	//3-6
	adj[3].push_back(6);
	adj[6].push_back(3);

	//3-7
	adj[3].push_back(7);
	adj[7].push_back(3);
	
	//4-5
	adj[4].push_back(5);
	adj[5].push_back(4);
	
	//6-7
	adj[6].push_back(7);
	adj[7].push_back(6);
	
	bfs(1);

	return 0;
}

void bfs(int start)
{
	queue<int> q;
	int c, i, tmp;

	q.push(start);
	check[start] = TRUE;	

	while(!q.empty())
	{
		c = q.front();
		printf("%d ", c);
		q.pop();

		for(i=0; i<adj[c].size(); i++)
		{
			tmp = adj[c][i];
			if(check[tmp] != TRUE)
			{
				q.push(tmp);
				check[tmp] = TRUE;
			}
		}
	}
	printf("\n");
}

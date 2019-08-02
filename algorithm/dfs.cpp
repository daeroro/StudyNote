#include <iostream>
#include <vector>
#include <stack>

#include <cstdio>

#define TRUE 1

using namespace std;

vector<int> adj[8];
int check[8];

void dfs(int start);

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
	
	dfs(1);

	return 0;
}

void dfs(int start)
{
	stack<int> st;
	int c, i, tmp;

	st.push(start);
	printf("%d ", start);
	check[start] = TRUE;

	while(!st.empty())
	{
		c = st.top();
		for(i=0; i<adj[c].size(); i++)
		{
			tmp = adj[c][i];
			if(check[tmp] != TRUE)
			{
				st.push(tmp);
				printf("%d ", tmp);
				check[tmp] = TRUE;
				break;
			}
			
			if(i == (adj[c].size()-1))
			{
				st.pop();
			}

		}
	}
	printf("\n");
}

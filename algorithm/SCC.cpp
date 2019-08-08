#include <iostream>
#include <vector>
#include <stack>

#include <cstdio>

#define NUM 11

using namespace std;

int sccNum;
int vNum = NUM;

vector <int> v[NUM+1];
int visit[NUM+1];
int parent[NUM+1];

void SCC(void)
{
	int i, sNode, nNode, tNode;
	stack<int> s;

	while(vNum)
	{
		if(s.empty())
		{
			for(i=1; i<NUM; i++)
			{
				if(visit[i] == 0)
				{
					sNode = i;
					s.push(sNode);
					visit[sNode] = 1;
					break;
				}
			}
		}
		
		sNode = s.top();
		printf("sNode = %d\n", sNode);		
		
		for(i=0; i<v[sNode].size(); i++)
		{
			if((visit[v[sNode][i]]==0) || (visit[v[sNode][i]]==1))
			{
				nNode = v[sNode][i];
				printf("nNode = %d\n", nNode);
				break;
			}
		}

		if(i==v[sNode].size())
		{
			printf("%d번째 SCC : %d\n", ++sccNum, sNode);
			--vNum;
			visit[sNode] = 2;
			s.pop();
			continue;
		}

		if(visit[nNode] == 0)
		{
			s.push(nNode);
			visit[nNode] = 1;
			continue;
		}
		else if(visit[nNode] == 1)
		{
			printf("%d번째 SCC : ", ++sccNum);
			tNode = s.top();

			while(tNode!= nNode)
			{
				printf("%d ", tNode);
				--vNum;
				visit[tNode] = 2;
				parent[tNode] = nNode;
				s.pop();
				tNode = s.top();
			}
			printf("%d\n", s.top());
			--vNum;
			visit[s.top()] = 2;
			s.pop();
		}
	}
}

int main(void)
{
	int i;

	//1->2
	v[1].push_back(2);

	//2->3
	v[2].push_back(3);

	//3->1
	v[3].push_back(1);

	//4->2
	v[4].push_back(2);

	//4->5
	v[4].push_back(5);

	//5->7
	v[5].push_back(7);

	//7->6
	v[7].push_back(6);

	//6->5
	v[6].push_back(5);

	//8->5
	v[8].push_back(5);

	//8->9
	v[8].push_back(9);

	//9->10
	v[9].push_back(10);

	//10->11
	v[10].push_back(11);

	//11->3
	v[11].push_back(3);

	//11->8
	v[11].push_back(8);

	//parent[] initialize
	for(i=1; i<=NUM; i++)
		parent[i] = i;

	SCC();

	for(i=1; i<=NUM; i++)
		printf("%d ", parent[i]);
	printf("\n");

	return 0;
}

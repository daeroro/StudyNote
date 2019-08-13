#include <iostream>
#include <vector>
#include <algorithm>

#include <cstdio>

using namespace std;

int N, M, K;
int n[11][11];
int A[11][11];

vector<pair<pair<int, int>,int> >v; 
vector<pair<pair<int, int>,int> >d;

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int>b)
{
	if((a.first.first == b.first.first) && (a.first.second == b.first.second))
		return a.second < b.second;
}

void countTree(void)
{
    
	int i, j, xp, yp, nxp, nyp;
	int xadd[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
	int yadd[8] = {0, 0, -1, 1, -1, 1, 1, -1};

	//spring

	for(i=0; i<(int)v.size(); i++)
	{
		xp = v[i].first.first;
		yp = v[i].first.second;

		if(n[xp][yp] >= v[i].second)
		{
			n[xp][yp] -= v[i].second;
			v[i].second++;
		}
		else
		{

			d.push_back(pair<pair<int,int>,int>(make_pair(xp, yp), v[i].second));
			v.erase(v.begin()+i);
			i--;
		}
	}
	
	//summer
	for(i=0; i<(int)d.size(); i++)
	{
		n[d[i].first.first][d[i].first.second] += (d[i].second/2);
		d.erase(d.begin()+i);
		i--;
	}
	
	//fall
	for(i=0; i<(int)v.size(); i++)
	{
		if(v[i].second % 5 == 0)
		{
			xp = v[i].first.first;
			yp = v[i].first.second;

			for(j=0; j<8; j++)
			{
				nxp = xp + xadd[j];
				nyp = yp + yadd[j];

				if(nxp<1 || nxp>N || nyp<1 || nyp>N)
					continue;
				
				v.push_back(pair<pair<int, int>, int>(make_pair(nxp, nyp),1));

			}
		}	

	}
	sort(v.begin(), v.end());



	//winter
	for(i=1; i<=N; i++)
		for(j=1; j<=N; j++)
			n[i][j] += A[i][j];

}

int main(void)
{
	int i, j, x[100], y[100], tree[100];

	scanf("%d %d %d", &N, &M, &K);
	
	for(i=1; i<=N; i++)
	{
		for(j=1; j<=N; j++)
		{
			scanf("%d", &A[i][j]);
		}
	}

	for(i=0; i<M; i++)
	{
		scanf("%d %d %d", &x[i], &y[i], &tree[i]);

	}

	for(i=0; i<M; i++)
		v.push_back(pair<pair<int, int>, int>(make_pair(x[i], y[i]), tree[i]));

	sort(v.begin(), v.end());

	for(i=1; i<=10; i++)
		for(j=1; j<=10; j++)
			n[i][j] = 5;

	for(i=0; i<K; i++)
		countTree();
	cout<<v.size()<<endl;

	return 0;
}

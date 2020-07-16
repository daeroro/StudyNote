#include <string>
#include <vector>
#include <deque>
#include <cmath>
#include <iostream>

using namespace std;

struct pos{
    int y, x, d, p;
};
int pri[25][25];
deque<struct pos> dq;

// 위, 아래, 왼쪽, 오른쪽
int yadd[4] = {-1, 1, 0, 0};
int xadd[4] = {0, 0, -1, 1};

int solution(vector<vector<int>> board) {
    int answer = 0;
    int N = board.size();
    //cout<<N<<"\n";

    int res = 25*25*500;

    pri[0][0] = -1;
    if(board[0][1] == 0)
    {
        dq.push_back({0, 1, 3, 100});
        pri[0][1] = 100;
    }
    if(board[1][0] == 0)
    {
        dq.push_back({1, 0, 1, 100});
        pri[1][0] = 100;
    }

    struct pos cPos, nPos;
    while(!dq.empty())
    {
        cPos = dq.front();
        dq.pop_front();

        //cout<<"cPo "<<cPos.y<<' '<<cPos.x<<' '<<cPos.d<<' '<<cPos.p<<"\n";

        for(int i=0; i<4; i++)
        {
            nPos.y = cPos.y + yadd[i];
            nPos.x = cPos.x + xadd[i];

            if(nPos.y < 0 || nPos.x < 0 || nPos.y >= N || nPos.x >= N)
                continue;

            if(nPos.y == N-1 && nPos.x == N-1)
            {
                if(cPos.d == i)
                {
                    nPos.d = i;
                    nPos.p = cPos.p + 100;
                }
                else
                {
                    nPos.d = i;
                    nPos.p = cPos.p + 600;
                }

                if(nPos.p < res) res = nPos.p;
                //cout<<"cur : "<<nPos.p<<"\n";
                continue;
            }
            int tNum;
            if(cPos.d == i) tNum = 100;
            else tNum = 600;            
            
            if(board[nPos.y][nPos.x] == 0)
            {
                if(pri[nPos.y][nPos.x] == 0)
                {
                    nPos.d = i;
                    nPos.p = cPos.p + tNum;

                    pri[nPos.y][nPos.x] = nPos.p;

                    dq.push_back(nPos);
                }
                else if(cPos.p + tNum <= pri[nPos.y][nPos.x])
                {
                    nPos.d = i;
                    nPos.p = cPos.p + tNum;

                    pri[nPos.y][nPos.x] = nPos.p;

                    dq.push_back(nPos);
                }
                //cout<<"nPos "<<i<<' '<<nPos.y<<' '<<nPos.x<<' '<<nPos.d<<' '<<nPos.p<<"\n";
            }
        }
    }

    answer = res;

    return answer;
}
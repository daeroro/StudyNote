#include <cstring>

#define w 1
#define y 2
#define r 3
#define o 4
#define g 5
#define b 6

#define U 7
#define D 8
#define F 9
#define B 10
#define L 11
#define R 12

#define cw 13
#define ccw 14

int num;
int test;
int arr[1001][2];

int arrU[10] = {0, w, w, w, w, w, w, w, w, w};
int arrD[10] = {0, y, y, y, y, y, y, y, y, y};
int arrF[10] = {0, r, r, r, r, r, r, r, r, r};
int arrB[10] = {0, o, o, o, o, o, o, o, o, o};
int arrL[10] = {0, g, g, g, g, g, g, g, g, g};
int arrR[10] = {0, b, b, b, b, b, b, b, b, b};

using namespace std;

void rotate(int side, int dir)
{
	int i;
	int tmp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	switch(side)
	{
		case U:
			if(dir == cw)
			{
				for(i=1; i<=3; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrR[i];
					arrR[i] = arrB[i];
					arrB[i] = arrL[i];
					arrL[i] = tmp[i];
				}	
			}
			else if(dir == ccw)
			{
				for(i=1; i<=3; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrL[i];
					arrL[i] = arrB[i];
					arrB[i] = arrR[i];
					arrR[i] = tmp[i];
				}
			}
			break;

		case D:
			if(dir == cw)
			{
				for(i=7; i<=9; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrR[i];
					arrR[i] = arrB[i];
					arrB[i] = arrL[i];
					arrL[i] = tmp[i];
				}
			}
			else if(dir == ccw)
			{
				for(i=7; i<=9; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrL[i];
					arrL[i] = arrB[i];
					arrB[i] = arrR[i];
					arrR[i] = tmp[i];
				}
			}
			break;

		case F:
			if(dir == cw)
			{
				tmp[7] = arrU[7]; tmp[8] = arrU[8]; tmp[9] = arrU[9];
				arrU[7] = arrL[3]; arrU[8] = arrL[6]; arrU[9] = arrL[9];
				arrL[3] = arrD[7]; arrL[6] = arrD[8]; arrL[9] = arrD[9];
				arrD[7] = arrR[7]; arrD[8] = arrR[4]; arrD[9] = arrR[1];
				arrR[7] = tmp[7]; arrR[4] = tmp[8]; arrR[1] = tmp[9];

			}
			else if(dir == ccw)
			{
				tmp[7] = arrU[7]; tmp[8] = arrU[8]; tmp[9] = arrU[9];
				arrU[7] = arrR[1]; arrU[8] = arrR[4]; arrU[9] = arrR[7];
				arrR[1] = arrD[7]; arrR[4] = arrD[8]; arrR[7] = arrD[9];
				arrD[7] = arrL[3]; arrD[8] = arrL[6]; arrD[9] = arrL[9];
				arrL[3] = tmp[7]; arrL[6] = tmp[8]; arrL[9] = tmp[9];

			}
			break;
		
		case B:
			if(dir == cw)
			{
				tmp[1] = arrU[1]; tmp[2] = arrU[2]; tmp[3] = arrU[3];
				arrU[1] = arrR[3]; arrU[2] = arrR[6]; arrU[3] = arrR[9];
				arrR[3] = arrD[3]; arrR[6] = arrD[2]; arrR[9] = arrD[1];
				arrD[3] = arrL[7]; arrD[2] = arrL[4]; arrD[1] = arrL[1];
				arrL[7] = tmp[1]; arrL[4] = tmp[2]; arrL[1] = tmp[3];
			
			}
			else if(dir == ccw)
			{
				tmp[1] = arrU[1]; tmp[2] = arrU[2]; tmp[3] = arrU[3];
				arrU[1] = arrL[7]; arrU[2] = arrL[4]; arrU[3] = arrL[1];
				arrL[7] = arrD[3]; arrL[4] = arrD[2]; arrL[1] = arrD[1];
				arrD[3] = arrR[9]; arrD[2] = arrR[6]; arrD[1] = arrR[3];
				arrR[9] = tmp[3]; arrR[6] = tmp[2]; arrR[3] = tmp[1];
			}
			break;

		case L:
			if(dir == cw)
			{
				tmp[1] = arrU[1]; tmp[4] = arrU[4]; tmp[7] = arrU[7];
				arrU[1] = arrB[7]; arrU[4] = arrB[4]; arrU[7] = arrB[1];
				arrB[7] = arrD[7]; arrB[4] = arrD[4]; arrB[1] = arrD[1];
				arrD[7] = arrF[1]; arrD[4] = arrF[4]; arrD[1] = arrF[7];
				arrF[1] = tmp[1]; arrF[4] = tmp[4]; arrF[7] = tmp[7];

			}
			else if(dir == ccw)
			{
				tmp[1] = arrU[1]; tmp[4] = arrU[4]; tmp[7] = arrU[7];
				arrU[1] = arrF[1]; arrU[4] = arrF[4]; arrU[7] = arrF[7];
				arrF[1] = arrD[7]; arrF[4] = arrD[4]; arrF[7] = arrD[1];
				arrD[7] = arrB[7]; arrD[4] = arrB[4]; arrD[1] = arrB[1];
				arrB[7] = tmp[1]; arrB[4] = tmp[4]; arrB[1] = tmp[7];
			}
			break;

		case R:
			if(dir == cw)
			{
				tmp[3] = arrU[3]; tmp[6] = arrU[6]; tmp[9] = arrU[9];
				arrU[3] = arrF[3]; arrU[6] = arrF[6]; arrU[9] = arrF[9];
				arrF[3] = arrD[9]; arrF[6] = arrD[6]; arrF[9] = arrD[3];
				arrD[9] = arrB[9]; arrD[6] = arrB[6]; arrD[3] = arrB[3];
				arrB[9] = tmp[3]; arrB[6] = tmp[6]; arrB[3] = tmp[9];

			}
			else if(dir == ccw)
			{
				tmp[3] = arrU[3]; tmp[6] = arrU[6]; tmp[9] = arrU[9];
				arrU[3] = arrB[9]; arrU[6] = arrB[6]; arrU[9] = arrB[3];
				arrB[9] = arrD[9]; arrB[6] = arrD[6]; arrB[3] = arrD[3];
				arrD[9] = arrF[3]; arrD[6] = arrF[6]; arrD[3] = arrF[9];
				arrF[3] = tmp[3]; arrF[6] = tmp[6]; arrF[9] = tmp[9];
				
			}
			break;

		memset(tmp, 0, sizeof(int)*10);
	}
}

int main(void)
{
	int i;
	scanf("%d", &test);
	while(test--)
	{
		scanf("%d", &num);

		for(i=1; i<=num; i++)
		{
			scanf("%d", &arr[i][0]);
			scanf("%d", &arr[i][1]);
		}

		for(i=1; i<=num; i++)
		{
			rotate(arr[i][0], arr[i][1]);
		}
	}

	return 0;
}

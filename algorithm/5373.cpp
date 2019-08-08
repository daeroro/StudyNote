#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
	
using namespace std;

#define U 7
#define D 8
#define F 9
#define B 10
#define L 11
#define R 12

#define cw 13
#define ccw 14


char arrU[10];
char arrD[10];
char arrF[10];
char arrB[10];
char arrL[10];
char arrR[10];

void reset(void)
{
	int i;
	
	for(i=1; i<=9; i++)
	{
		arrU[i] = 'w';
		arrD[i] = 'y';
		arrF[i] = 'r';
		arrB[i] = 'o';
		arrL[i] = 'g';
		arrR[i] = 'b';
	}
}

void clockWise(char * arr)
{
	char tmp1, tmp2;

	tmp1 = arr[1];
	arr[1] = arr[7];
	arr[7] = arr[9];
	arr[9] = arr[3];
	arr[3] = tmp1;

	tmp2 = arr[2];
	arr[2] = arr[4];
	arr[4] = arr[8];
	arr[8] = arr[6];
	arr[6] = tmp2;
}

void counterClockWise(char * arr)
{
	char tmp1, tmp2;

	tmp1 = arr[1];
	arr[1] = arr[3];
	arr[3] = arr[9];
	arr[9] = arr[7];
	arr[7] = tmp1;

	tmp2 = arr[2];
	arr[2] = arr[6];
	arr[6] = arr[8];
	arr[8] = arr[4];
	arr[4] = tmp2;
}

void rotate(char side, char dir)
{
	int i;
	int tmp[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int tmp2[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	

	switch(side)
	{
		case 'U':
			if(dir == '+')
			{
				for(i=1; i<=3; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrR[i];
					arrR[i] = arrB[i];
					arrB[i] = arrL[i];
					arrL[i] = tmp[i];
				}
				clockWise(arrU);
	
			}
			else if(dir == '-')
			{
				for(i=1; i<=3; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrL[i];
					arrL[i] = arrB[i];
					arrB[i] = arrR[i];
					arrR[i] = tmp[i];
				}
				counterClockWise(arrU);
			}
			break;

		case 'D':
			if(dir == '+')
			{
				for(i=7; i<=9; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrR[i];
					arrR[i] = arrB[i];
					arrB[i] = arrL[i];
					arrL[i] = tmp[i];
				}
				clockWise(arrD);
			}
			else if(dir == '-')
			{
				for(i=7; i<=9; i++)
				{
					tmp[i] = arrF[i];
					arrF[i] = arrL[i];
					arrL[i] = arrB[i];
					arrB[i] = arrR[i];
					arrR[i] = tmp[i];
				}
				counterClockWise(arrD);
			}
			break;

		case 'F':
			if(dir == '+')
			{
				tmp[7] = arrU[7]; tmp[8] = arrU[8]; tmp[9] = arrU[9];
				arrU[7] = arrL[9]; arrU[8] = arrL[6]; arrU[9] = arrL[3];
				arrL[9] = arrD[9]; arrL[6] = arrD[8]; arrL[3] = arrD[7];
				arrD[9] = arrR[1]; arrD[8] = arrR[4]; arrD[7] = arrR[7];
				arrR[1] = tmp[7]; arrR[4] = tmp[8]; arrR[7] = tmp[9];
				
				clockWise(arrF);

			}
			else if(dir == '-')
			{
				tmp[7] = arrU[7]; tmp[8] = arrU[8]; tmp[9] = arrU[9];
				arrU[7] = arrR[1]; arrU[8] = arrR[4]; arrU[9] = arrR[7];
				arrR[1] = arrD[7]; arrR[4] = arrD[8]; arrR[7] = arrD[9];
				arrD[7] = arrL[3]; arrD[8] = arrL[6]; arrD[9] = arrL[9];
				arrL[3] = tmp[7]; arrL[6] = tmp[8]; arrL[9] = tmp[9];
				
				counterClockWise(arrF);

			}
			break;
		
		case 'B':
			if(dir == '+')
			{
				tmp[1] = arrU[1]; tmp[2] = arrU[2]; tmp[3] = arrU[3];
				arrU[1] = arrR[3]; arrU[2] = arrR[6]; arrU[3] = arrR[9];
				arrR[3] = arrD[3]; arrR[6] = arrD[2]; arrR[9] = arrD[1];
				arrD[3] = arrL[7]; arrD[2] = arrL[4]; arrD[1] = arrL[1];
				arrL[7] = tmp[1]; arrL[4] = tmp[2]; arrL[1] = tmp[3];
			
				clockWise(arrB);
			
			}
			else if(dir == '-')
			{
				tmp[1] = arrU[1]; tmp[2] = arrU[2]; tmp[3] = arrU[3];
				arrU[1] = arrL[7]; arrU[2] = arrL[4]; arrU[3] = arrL[1];
				arrL[7] = arrD[3]; arrL[4] = arrD[2]; arrL[1] = arrD[1];
				arrD[3] = arrR[9]; arrD[2] = arrR[6]; arrD[1] = arrR[3];
				arrR[9] = tmp[3]; arrR[6] = tmp[2]; arrR[3] = tmp[1];

				counterClockWise(arrB);
			}
			break;

		case 'L':
			if(dir == '+')
			{
				tmp[1] = arrU[1]; tmp[4] = arrU[4]; tmp[7] = arrU[7];
				arrU[1] = arrB[7]; arrU[4] = arrB[4]; arrU[7] = arrB[1];
				arrB[7] = arrD[7]; arrB[4] = arrD[4]; arrB[1] = arrD[1];
				arrD[7] = arrF[1]; arrD[4] = arrF[4]; arrD[1] = arrF[7];
				arrF[1] = tmp[1]; arrF[4] = tmp[4]; arrF[7] = tmp[7];

				clockWise(arrL);

			}
			else if(dir == '-')
			{
				tmp[1] = arrU[1]; tmp[4] = arrU[4]; tmp[7] = arrU[7];
				arrU[1] = arrF[1]; arrU[4] = arrF[4]; arrU[7] = arrF[7];
				arrF[1] = arrD[7]; arrF[4] = arrD[4]; arrF[7] = arrD[1];
				arrD[7] = arrB[7]; arrD[4] = arrB[4]; arrD[1] = arrB[1];
				arrB[7] = tmp[1]; arrB[4] = tmp[4]; arrB[1] = tmp[7];

				counterClockWise(arrL);
			}
			break;

		case 'R':
			if(dir == '+')
			{
				tmp[3] = arrU[3]; tmp[6] = arrU[6]; tmp[9] = arrU[9];
				arrU[3] = arrF[3]; arrU[6] = arrF[6]; arrU[9] = arrF[9];
				arrF[3] = arrD[9]; arrF[6] = arrD[6]; arrF[9] = arrD[3];
				arrD[9] = arrB[9]; arrD[6] = arrB[6]; arrD[3] = arrB[3];
				arrB[9] = tmp[3]; arrB[6] = tmp[6]; arrB[3] = tmp[9];

				clockWise(arrR);

			}
			else if(dir == '-')
			{
				tmp[3] = arrU[3]; tmp[6] = arrU[6]; tmp[9] = arrU[9];
				arrU[3] = arrB[9]; arrU[6] = arrB[6]; arrU[9] = arrB[3];
				arrB[9] = arrD[9]; arrB[6] = arrD[6]; arrB[3] = arrD[3];
				arrD[9] = arrF[3]; arrD[6] = arrF[6]; arrD[3] = arrF[9];
				arrF[3] = tmp[3]; arrF[6] = tmp[6]; arrF[9] = tmp[9];

				counterClockWise(arrR);
				
			}
			break;

		memset(tmp, 0, sizeof(int)*10);
	
		
	}
}

void printU(int num)
{
	int i;

	for(i=1; i<=num; i++)
	{
		printf("%c", arrU[i]);
		if(i%3 == 0)
			printf("\n");
	}
}	

int main(void)
{
	int i, j;
	int test, num[101];
	char a[101][1001][3];
	scanf("%d", &test);

	for(i=1; i<=test; i++)
	{
		scanf("%d", &num[i]);

		for(j=1; j<=num[i]; j++)
		{	
			scanf("%s", a[i][j]);
		}

	}
	for(i=1; i<=test; i++)
	{
		reset();
		for(j=1;j<=num[i]; j++)
		{
			rotate(a[i][j][0], a[i][j][1]);
		}
		printU(9);
	}

	return 0;
}

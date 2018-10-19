#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <map>

struct CUBE_STATE
{
	int number[6];

	bool operator<(const CUBE_STATE& rhs)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (number[i] < rhs.number[i])
			{
				return true;
			}
			else if (number[i] > rhs.number[i])
			{
				return false;
			}
		}

		return false;
	}

	bool isCompelete()
	{
		for (int i = 0; i < 6; ++i)
		{
			if (number[i] % 1111 != 0)
				return false;
		}

		return true;
	}

	void log()
	{
		printf("[%d,%d,%d,%d,%d,%d]\n", number[0], number[1], number[2], number[3], number[4], number[5]);
	}
};

typedef std::map<CUBE_STATE, int> mapCubeState;

int sblankState[24] =
{
	0,0,0,0,
	1,1,1,1,
	2,2,2,2,
	3,3,3,3,
	4,4,4,4,
	5,5,5,5,
};

struct BLANK_STATE
{
	int blankState[24];

	int* operator[](int i)
	{
		return &blankState[i * 4];
	}
	
	void  init()
	{
		memcpy(blankState, sblankState, sizeof(sblankState));
	}

};

BLANK_STATE BlankState;
//六种颜色的编码值分别为 [0, 1, 2, 3, 4, 5]
//4个格子的放缩值为 [1, 10 , 100, 1000]

CUBE_STATE cal_cube_state()
{
	CUBE_STATE cubeState;
	for (int i = 0; i < 6; ++i)
	{
		int* panel = BlankState[i];
		cubeState.number[i] = panel[0] * 1 + panel[1] * 10 + panel[2] * 100 + panel[3] * 1000;
	}
}

void up_left()
{
	BLANK_STATE temp = BlankState;
	
	BlankState[0][0] = temp[3][0];
	BlankState[0][1] = temp[3][1];

	BlankState[1][0] = temp[0][0];
	BlankState[1][1] = temp[0][1];

	BlankState[2][0] = temp[1][0];
	BlankState[2][1] = temp[1][1];

	BlankState[3][0] = temp[2][0];
	BlankState[3][1] = temp[2][1];


	BlankState[4][0] = temp[4][1];
	BlankState[4][1] = temp[4][3];
	BlankState[4][3] = temp[4][2];
	BlankState[4][2] = temp[4][0];
}

void up_right()
{
	BLANK_STATE temp = BlankState;

	BlankState[0][0] = temp[1][0];
	BlankState[0][1] = temp[1][1];

	BlankState[1][0] = temp[2][0];
	BlankState[1][1] = temp[2][1];
	
	BlankState[2][0] = temp[3][0];
	BlankState[2][1] = temp[3][1];
		
	BlankState[3][0] = temp[0][0];
	BlankState[3][1] = temp[0][1];


	BlankState[4][0] = temp[4][2];
	BlankState[4][2] = temp[4][3];
	BlankState[4][3] = temp[4][1];
	BlankState[4][1] = temp[4][0];
}

void b_left()
{
	BLANK_STATE temp = BlankState;

	BlankState[0][0] = temp[3][0];
	BlankState[0][1] = temp[3][1];

	BlankState[1][0] = temp[0][0];
	BlankState[1][1] = temp[0][1];

	BlankState[2][0] = temp[1][0];
	BlankState[2][1] = temp[1][1];

	BlankState[3][0] = temp[2][0];
	BlankState[3][1] = temp[2][1];


	BlankState[4][0] = temp[4][1];
	BlankState[4][1] = temp[4][3];
	BlankState[4][3] = temp[4][2];
	BlankState[4][2] = temp[4][0];
}

void b_right()
{
	BLANK_STATE temp = BlankState;

	BlankState[0][0] = temp[1][0];
	BlankState[0][1] = temp[1][1];

	BlankState[1][0] = temp[2][0];
	BlankState[1][1] = temp[2][1];

	BlankState[2][0] = temp[3][0];
	BlankState[2][1] = temp[3][1];

	BlankState[3][0] = temp[0][0];
	BlankState[3][1] = temp[0][1];


	BlankState[4][0] = temp[4][2];
	BlankState[4][2] = temp[4][3];
	BlankState[4][3] = temp[4][1];
	BlankState[4][1] = temp[4][0];
}


int main()
{

	return 0;
}


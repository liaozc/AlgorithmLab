// DP.cpp : 动态规划
//

/*
	题目: http://blog.csdn.net/chudongfang2015/article/details/76796631

	解题思路:
		对于第i层，只需记录在从左右楼梯上来时，关闭前面 i-1 层的最小时间 fi(leftMin) 和 fi(rightMin);
		那么 fi+1(leftMin) = min(max_right_i+1 * 2 + 1，fi(rightMin) + m + 2);  对于 fi(rightMin) 同理。

*/

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

#define min(a,b)  a < b ? a : b;

int map[20][22];

void change_to_flag(int n,char chs[],int m)
{
	for (int j = 0; j < m; ++j)
		map[n][j] = chs[j] - '0';
}

int findMinTime(int n, int m)
{
	int fMinLeft = 0, fMinRight = m - 1;
	int fMinius = 0;
	for (int i = n - 1; i >= 0; -- i) {
		int l = m; 
		int r = 0;
		bool findL = false;
		bool findR = false;
		for (int j = 1; j <= m - 2; ++j) {
			if (map[i][j] == 1 && j < l) {
				l = j; findL = true;
			}
			if (map[i][m - 1 - j] == 1 && m - 1 - j > r) {
				r = m - 1 - j;
				findR = true;
			}
			if (findL && findR) break;
		}
		if (l > r) continue;
		
		fMinius = min(fMinLeft + r, fMinRight + m - 1 - l);
		int fTempMinLeft = min(fMinLeft + 2 * r + 1, fMinRight + m);
		fMinRight = min(fMinRight + 2 * (m - 1 - l) + 1, fMinLeft + m);
		fMinLeft = fTempMinLeft;
	}
	return fMinius;
}

int main()
{
	while (true) {
		memset(map,0,sizeof(int) * 20 * 22);
		int n; int m;
		scanf_s("%d%d",&n,&m);
		if (n == 0 || m == 0) break;
		char chs[30];
		for (int i = 0; i < n; ++i) {
			scanf_s("%s",chs,30);
			change_to_flag(i, chs, m + 2);
		}
		int fmin = findMinTime(n,m + 2);
		printf("%d\n", fmin);
	}
    return 0;
}


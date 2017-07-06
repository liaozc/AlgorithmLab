//N Queens : Defines the entry point for the console application.
//


/*	question:

	1.输出各个N Queens 的各个解
*/

/* 思路：

	经典的回溯解法

*/

#include "stdafx.h"
#include <string>
#include <vector>
#include <cstdlib>


void GetString(std::vector<int>& q, std::vector<std::string>& strAry)
{
	int N = q.size();
	std::string str;
	for (int i = 0; i < N; ++i) 
	{
		std::string row = std::string(N, '.');
		row.replace(q[i], 1, "Q");
		str = str + row + "\n";
	}
	str = str + "\n";
	strAry.push_back(str);
}

bool CheckPos(int r, std::vector<int>& q,int p)
{
	for (int i = 0; i < r; ++i) {
		if (p - q[i] == 0 || abs(p - q[i]) == r - i)
			return false;
	}
	return true;
}

void SolveNQueens(std::vector<std::string>& strAry, int r, int N, std::vector<int>& q)
{
	if (r == N) {
		GetString(q, strAry);
		return;
	}
	for (int i = 0; i < N; ++i) {
		q[r] = i;
		if (CheckPos(r, q, i))
		{
			SolveNQueens(strAry, r + 1, N, q);
		}
	}

}

void SolveNQueens(std::vector<std::string>& strAry, int N)
{
	std::vector<int> q(N,-1);
	SolveNQueens(strAry,0,N,q);
}

int main()
{
	std::vector<std::string> strAry;
	SolveNQueens(strAry, 5);
	printf("all solution : %d \n\n", strAry.size());
	for (int i = 0; i < strAry.size(); ++i) {
		printf(strAry[i].c_str());
	}
    return 0;
}


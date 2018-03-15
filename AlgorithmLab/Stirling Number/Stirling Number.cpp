// Stirling Number.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

/*
	将 N 个数构成 K 个非空环的个数，
	例如 3 分成 2 个非空环的个数 1->2/3 ,1->2/2 , 2->3/1 共三种，
	令S(N,K)表示该个数，称S(N,K)为stirling数。

	又可以细分成两类，一种是环的顺序是可辨别的，即和排列相关，一种是环的顺序只和元素集合相关。 分称为第一种 stirling 和 第二种striling 数。

	第一种的推导形式：
	S(N,K) = S(N-1,K -1) + S(N - 1,K) * (N - 1)
	第二种推导形式：
	S(N,K) = S(N-1，K-1) + S(N-1,K) * K

	S(N,0) = 0
	S(N,N) = 1
	S(0,K) = 0
	S(N,K) = 0 K>N
*/

/*
	应用1 ：
		每个房间有一把钥匙，但顺序可能掉乱，如Room1可能放着Key2，全部门锁着，不打破Room1的门，最多打破K扇门，能够打开Room1的概率。（钥匙分布等概率）
	求解：N的房间的钥匙形成K个环，这样在K次之内能打开，当然，除了这些Key1在Room1的环。求出1，2，..K个环所构成的个数，并减去其中Key1在Room1的个数，除上全部的分布情况。
		 SUM<i:1..K>(S(N,i))/P(N), P(N)为N的排列

*/

typedef long long ll;

ll fac[21] = { 1 };
ll table[21][21];
void init_fac()
{
	for (int i = 1; i < 21; ++i)
		fac[i] = fac[i - 1] * i;
	memset(table, 0, 441 * sizeof(ll));
	for (int i = 1; i <= 21; ++i) {
		for (int j = i; j < 21; ++j) {
			if (j == i) table[i][j] = 1;
			if (j > i) table[i][j] = table[i - 1][j - 1] + table[i][j - 1] * (j - 1);
		}
	}
}

ll get_stirling_number_1(ll n,ll k)
{	
	return table[k][n];
}


int main()
{
	init_fac();
	//应用1
	while (true) {
		int n = 0, k = 0;
		scanf_s("%d%d", &n, &k);
		if (n == 0 || k == 0) break;
		ll all_accessable = 0;
		for (int i = 1; i <= k; i++)
			all_accessable += get_stirling_number_1(n, i) - get_stirling_number_1(n - 1, i - 1);
		float prob = (float)all_accessable / float(fac[n]);
		printf("prob:%.4f \n", prob);
	}
    return 0;
}

/*
	思维不周密，逻辑不严谨，这样的数学技能、编码能力，竟然还能混到现在。
*/
// DP Floyd.cpp : Defines the entry point for the console application.
//

/*
	状压DP:状态压缩动态规划
	将状态压缩，通常采用&操作符进行DP. 状压DP主要是用于暴力回溯时的节省时间的策略，一般会将 O(N!)的时间复杂度减低到O(N^k * 2^N)的情况

	问题描述：
	有一个送外卖的，他手上有n份订单，他要把n份东西，分别送达n个不同的客户的手上。n个不同的客户分别在1~n个编号的城市中。送外卖的从0号城市出发，
	然后n个城市都要走一次（一个城市可以走多次），最后还要回到0点（他的单位），请问最短时间是多少。现在已知任意两个城市的直接通路的时间。

	解题思路：
	建构DP[N][1<<N],
	令DP[i][j]是当前在 i 城市，处于 j 状态时走过的距离。易知，DP[0][0] = 0; 状态 j 为所有走过的城市的编码。这里的每个城市的状态位是代表这个城市
	在行程中的最后一次出现的情况，非最后一次的情况只是其他节点的路过点，不计入状态。所以从一个状态转移到另一个状态，必须不能有相同的城市状态位，
	这也说明了，转移后的状态比转移前的状态值要大。

	对于和 i 相连的所有节点，刷新其状态。
	如果每个节点的每个状态都被贡献了有效值，那么就能够得到所有DP的情况。
	那么是
	for(int i = 0; i < N; ++ i) 
		for(int s = 0; s < (1<<N); ++s )
	还是 
	for(int s = 0; s < (1<<N); ++s )
		for(int i = 0; i < N; ++ i)
	注意到第一情况下,由于是对某个节点的所有状态的遍历，会出现有的状态并未被正式赋值前就被访问了。
	例如 0->1->2->0, 会有状态 s = 001 和 010 和 011 在访问时是 INF 值，这是错误的。 而第二种情况下，
	以状态为序，由于每一种状态 s 只会影响其他节点的状态 s',其中s’ > s, 所以能影响s'状态的取值的
	所有s状态都是被遍历过的。所以使用第二种方式。

	
*/
#if 1
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

#define min(a,b) a < b ? a : b;
const int N = 20;
int map[N][N];
const int INF = 0x0FFFFFFF;

int dp[N][1 << N];

void clear()
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			map[i][j] = INF;

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < (1 << N); ++j)
			dp[i][j] = INF;

}

void floyd(int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; k++) {
				if (map[j][k] > map[j][i] + map[i][k]) map[j][k] = map[j][i] + map[i][k];
			}
		}
	}
}

void print_m(int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}


int main()
{
	clear();
	int n = 1;
	scanf_s("%d",&n);
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			scanf_s("%d", &map[i][j]);
	floyd(n);
	print_m(n);
	dp[0][0] = 0;

	for (int s = 0; s < (1 << n); ++s) {
		for (int i = 0; i < n; ++i) {
			if (dp[i][s] == INF) continue;
			for (int j = 0; j < n; ++j) {
				if (s & (1 << j)) continue;
				int nextState = s | (1 << j);
				dp[j][nextState] = min(dp[j][nextState], dp[i][s] + map[i][j]);
			}
		}
	}

	printf("%d\n", dp[0][(1<<n)- 1]);

    return 0;
}
#else

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<iomanip>


#define INF 0x3f3f3f3f
using namespace std;
typedef  long long ll;
const int MOD = 100000007;
const int N = 16;

int dp[N][1 << N];

int n;
int mm[N + 2][N + 2];

void floyd()
{
	for (int k = 0; k < n; k++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < n; i++)
			{
				mm[i][j] = min(mm[i][j], mm[i][k] + mm[k][j]);
			}
		}

	}
}

void print_m(int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d ", mm[i][j]);
		}
		printf("\n");
	}
}



int main() {
	ios_base::sync_with_stdio(false);
	//    freopen("data.txt","r",stdin);

	while (cin >> n)
	{
		memset(dp, INF, sizeof(dp));
		n++;
		for (int i = 0; i<n; i++)
		{
			for (int j = 0; j<n; j++)
			{
				cin >> mm[i][j];
			}
		}

		floyd();
		print_m(n);
		dp[0][0] = 0;
		for (int stat = 0; stat < (1 << n); stat++)
		{
			for (int i = 0; i < n; i++)
			{
				if (dp[i][stat] == INF) continue;
				for (int j = 0; j<n; j++)
				{
					if (stat&(1 << j))
						continue;

					int nex = stat | (1 << j);

					dp[j][nex] = min(dp[j][nex], dp[i][stat] + mm[i][j]);

				}
			}
		}

		cout << dp[0][(1 << n) - 1] << endl;

	}
	return 0;
}
#endif
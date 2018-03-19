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
	令DP[i][j]是当前在 i 城市，处于 j 状态时走过的距离。易知，DP[0][0] = 0;
	对于和 i 相连的所有节点，刷新其状态。
	如果每个节点的每个状态都被贡献了有效值，那么就能够得到所有DP的情况。
	那么是
	for(int i = 0; i < N; ++ i) 
		for(int s = 0; s < (1<<N); ++s )
	还是 
	for(int s = 0; s < (1<<N); ++s )
		for(int i = 0; i < N; ++ i)
	注意到第一情况下,由于是对某个节点的所有状态的遍历，会出现有的状态并未被正式赋值前就被访问了。
	例如 0->1->2->0, 会有状态 s = 01 和 10 和 11 在访问时是 INF 值，这是错误的。 而第二种情况下，
	以状态为序，由于每一种状态 s 只会影响其他节点的 s’ ，s‘ > s, 所以，不存在当前的状态改变之前访
	问过的状态，导致以前的访问是无效值的问题。所以采用第二种方式。
	
*/

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

const int N = 20;
int map[N][N];
const int INF = 0x8FFFFFFF;

void clear_map()
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			map[i][j] = INF;

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


int main()
{
	clear_map();
	int n = 1;
	scanf_s("%d",&n);
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			scanf_s("%d", &map[i][j]);
	floyd(n);



    return 0;
}


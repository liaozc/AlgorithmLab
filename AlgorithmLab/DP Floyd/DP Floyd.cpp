// DP Floyd.cpp : Defines the entry point for the console application.
//

/*
	״ѹDP:״̬ѹ����̬�滮
	��״̬ѹ����ͨ������&����������DP. ״ѹDP��Ҫ�����ڱ�������ʱ�Ľ�ʡʱ��Ĳ��ԣ�һ��Ὣ O(N!)��ʱ�临�Ӷȼ��͵�O(N^k * 2^N)�����

	����������
	��һ���������ģ���������n�ݶ�������Ҫ��n�ݶ������ֱ��ʹ�n����ͬ�Ŀͻ������ϡ�n����ͬ�Ŀͻ��ֱ���1~n����ŵĳ����С��������Ĵ�0�ų��г�����
	Ȼ��n�����ж�Ҫ��һ�Σ�һ�����п����߶�Σ������Ҫ�ص�0�㣨���ĵ�λ�����������ʱ���Ƕ��١�������֪�����������е�ֱ��ͨ·��ʱ�䡣

	����˼·��
	����DP[N][1<<N],
	��DP[i][j]�ǵ�ǰ�� i ���У����� j ״̬ʱ�߹��ľ��롣��֪��DP[0][0] = 0; ״̬ j Ϊ�����߹��ĳ��еı��롣�����ÿ�����е�״̬λ�Ǵ����������
	���г��е����һ�γ��ֵ�����������һ�ε����ֻ�������ڵ��·���㣬������״̬�����Դ�һ��״̬ת�Ƶ���һ��״̬�����벻������ͬ�ĳ���״̬λ��
	��Ҳ˵���ˣ�ת�ƺ��״̬��ת��ǰ��״ֵ̬Ҫ��

	���ں� i ���������нڵ㣬ˢ����״̬��
	���ÿ���ڵ��ÿ��״̬������������Чֵ����ô���ܹ��õ�����DP�������
	��ô��
	for(int i = 0; i < N; ++ i) 
		for(int s = 0; s < (1<<N); ++s )
	���� 
	for(int s = 0; s < (1<<N); ++s )
		for(int i = 0; i < N; ++ i)
	ע�⵽��һ�����,�����Ƕ�ĳ���ڵ������״̬�ı�����������е�״̬��δ����ʽ��ֵǰ�ͱ������ˡ�
	���� 0->1->2->0, ����״̬ s = 001 �� 010 �� 011 �ڷ���ʱ�� INF ֵ�����Ǵ���ġ� ���ڶ�������£�
	��״̬Ϊ������ÿһ��״̬ s ֻ��Ӱ�������ڵ��״̬ s',����s�� > s, ������Ӱ��s'״̬��ȡֵ��
	����s״̬���Ǳ��������ġ�����ʹ�õڶ��ַ�ʽ��

	
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
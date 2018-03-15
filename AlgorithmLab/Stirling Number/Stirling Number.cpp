// Stirling Number.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

/*
	�� N �������� K ���ǿջ��ĸ�����
	���� 3 �ֳ� 2 ���ǿջ��ĸ��� 1->2/3 ,1->2/2 , 2->3/1 �����֣�
	��S(N,K)��ʾ�ø�������S(N,K)Ϊstirling����

	�ֿ���ϸ�ֳ����࣬һ���ǻ���˳���ǿɱ��ģ�����������أ�һ���ǻ���˳��ֻ��Ԫ�ؼ�����ء� �ֳ�Ϊ��һ�� stirling �� �ڶ���striling ����

	��һ�ֵ��Ƶ���ʽ��
	S(N,K) = S(N-1,K -1) + S(N - 1,K) * (N - 1)
	�ڶ����Ƶ���ʽ��
	S(N,K) = S(N-1��K-1) + S(N-1,K) * K

	S(N,0) = 0
	S(N,N) = 1
	S(0,K) = 0
	S(N,K) = 0 K>N
*/

/*
	Ӧ��1 ��
		ÿ��������һ��Կ�ף���˳����ܵ��ң���Room1���ܷ���Key2��ȫ�������ţ�������Room1���ţ�������K���ţ��ܹ���Room1�ĸ��ʡ���Կ�׷ֲ��ȸ��ʣ�
	��⣺N�ķ����Կ���γ�K������������K��֮���ܴ򿪣���Ȼ��������ЩKey1��Room1�Ļ������1��2��..K���������ɵĸ���������ȥ����Key1��Room1�ĸ���������ȫ���ķֲ������
		 SUM<i:1..K>(S(N,i))/P(N), P(N)ΪN������

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
	//Ӧ��1
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
	˼ά�����ܣ��߼����Ͻ�����������ѧ���ܡ�������������Ȼ���ܻ쵽���ڡ�
*/
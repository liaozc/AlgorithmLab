// So Easy.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <time.h>

/*
	�����ݺ;�������ݵ�Ӧ��

	�������ǽ���M��N���ݵĲ���ʱ�併�͵ķ�������������󷨣�M��N���ݣ�ʱ�临�Ӷ�ΪO(N).�ö��۵ķ������Լ��͵�O(logN)
	M^N = M * M * M ... * M,
	N = 2^a1 + 2^a2 + .. + 2^an,
	��NΪ�����Ƹ�ʽ�����磬N(2) = 11011,������Kλ��������M^1��M^2,....,M^K,һ��O(logN)����ÿ��Ϊ1��bitλ��������ʱ�����С�
	

	�����ݵĴ���������£���������������
*/

int quick_power(int M,int N)
{
	int temp = 1;
	while (N) {
		if (N & 1) temp *= M;
		M *= M;
		N >>= 1;
	}
	return temp;
}

/*
	��������ݵ�˼ά��࣬���ǽ����Եļӷ���������Ϊ���Եĳ˷������������ü�����м�������Ϳ�����һ�����
	����쳲���ϵ�У�F(1) = F(2) = 1, F(N) = F(N-1) + F(N-2),N > 2; ��F(N),һ���������ÿ��n<N��Ҫ˳����������ʱ��ΪO(N).
	�罫F(N)��F(N-1)��ɾ����� M[N] = {F(N),F(N-1)}T, ��M[N + 1] = A*M[N],����A = {{1,1},{1,0}},
	��F(N) = M[N].a00; M[N] = A^(N-1) * M[1].��ʱ������ܽ�A^(N-1)�ļ��������٣����ܰ��㷨�ĸ��Ӷȼ��͡����ھ���˷��Ŀɽ���ԣ�
	֪��Ӧ���ڿ����ݵķ���ͬ�������ڴˡ�

	��������ݵĴ���������£����������
*/

template<typename Matrix>
Matrix quick_power(Matrix M, int N)
{
	Matrix ret;
	while (N) {
		if (N & 1) ret = ret * M;
		M = M * M;
		N >>= 1;
	}
	return ret;
}

class Matrix_Fibonacci
{
public:
	int a00, a01, a10, a11;
	Matrix_Fibonacci() 
	{
		a00 = 1;
		a01 = 0;
		a10 = 0;
		a11 = 1;
	}
	Matrix_Fibonacci& operator*(const Matrix_Fibonacci& _Other)
	{
		Matrix_Fibonacci temp;
		temp.a00 = a00 * _Other.a00 + a01 * _Other.a10;
		temp.a01 = a00 * _Other.a01 + a01 * _Other.a11;
		temp.a10 = a10 * _Other.a00 + a11 * _Other.a10;
		temp.a11 = a10 * _Other.a01 + a11 * _Other.a11;
		a00 = temp.a00;
		a01 = temp.a01;
		a10 = temp.a10;
		a11 = temp.a11;
		return *this;
	}
};

int test_fibonacci(int n) 
{
	if (n == 1 || n == 2) return 1;
	return test_fibonacci(n - 1) + test_fibonacci(n - 2);
}


/*
	��[(A + sqrt(B))^N]%M,A B,N M ��Ϊ��������  (A -1)^2 < B < A^2.[]Ϊ����ȡ������ 0< A,M < 2^15, 0< B,N < 2^31.
	
	����Ŀ֪����A��B��N��M����Ϊint.

	1.����ȡ����Ľ����
	�� (A + sqrt(B))^N = XN + YN*sqrt(B),��XNΪ���������֣�YNΪ������������ϵ����֪��YNΪ����ϵ���ֲ��У�sqrt(B)��ָ��Ϊ��������������ȡsqrt(B)���������.
	�� (A - sqrt(B))^N = XN' + YN'*sqrt(B),�ɶ���ֲ�֪����XN = XN',YN = -YN'. ���� (A + sqrt(B))^N + (A - sqrt(B))^N = 2*XN.
	����Ϊ (A - 1)^2< B < A^2,����  A-1 <sqrt(B) < A, 0 < A - Sqrt(B) < 1, ���� 0 < (A - sqrt(B))^N < 1; ���ԣ� (A + sqrt(B))^N = 2*XN - (A - sqrt(B))^N,
	��[(A + sqrt(B))^N] = 2*XN.

	2.��XN.
	��Ϊ (A + sqrt(B))^N = XN + YN*sqrt(B)��(A + sqrt(B))^(N+1) = (XN + YN*sqrt(B))(A + sqrt(B)) = XN* A + B* YN + (XN + A*YN)*sqrt(B);�� XN+1 = XN*A + B*YN, YN+1 = XN + A*YN,
	���Դ�[X1,Y1]([1,1]) ��ʼ���˷���ֱ��[XN,YN],ʱ�临�Ӷ�ΪO(N),Ҳ���Թ����������ÿ����ݵ��㷨�����͵�O(logN)�ĸ��Ӷȡ�

	A��ֱ����˵ķ���.
*/

long long so_easy_direct(long long A, long long B, long long N, long long M)
{
	long long x = A%M, y = 1;
	for(long long i = 1; i < N; ++ i){
		long long tx = (x * A + B * y)%M;
		long long ty = (x + A * y)%M;
		x = tx;
		y = ty;
	}
	return (x * 2)%M;
}

/*	
	B:����������ٳ˷�
	
	TRS = |A,B|  �� M[N+1] = TRS * M[N], ���� M[N] = [XN,YN]T
		  |1,A|,                                    
	֪�� M[N] = TRS^N-1 * M[1] ,N > 1
*/

template<typename Matrix>
Matrix quick_power_mod(Matrix M, long long N, long long Mod)
{
	Matrix ret;
	while (N) {
		if (N & 1) ret = (ret * M)%Mod;
		M = M * M;
		M = M%Mod;
		N >>= 1;
	}
	return ret;
}

class Matrix_So_Easy
{
public:
	long long a00, a01, a10, a11;
	Matrix_So_Easy()
	{
		a00 = 1;
		a01 = 0;
		a10 = 0;
		a11 = 1;
	}
	Matrix_So_Easy& operator*(const Matrix_So_Easy& _Other)
	{
		Matrix_So_Easy temp;
		temp.a00 = a00 * _Other.a00 + a01 * _Other.a10;
		temp.a01 = a00 * _Other.a01 + a01 * _Other.a11;
		temp.a10 = a10 * _Other.a00 + a11 * _Other.a10;
		temp.a11 = a10 * _Other.a01 + a11 * _Other.a11;
		a00 = temp.a00;
		a01 = temp.a01;
		a10 = temp.a10;
		a11 = temp.a11;
		return *this;
	}

	Matrix_So_Easy& operator%(long long Mod)
	{
		a00 %= Mod;
		a01 %= Mod;
		a10 %= Mod;
		a11 %= Mod;
		return *this;
	}

};

void solve_so_easy_direct(long long A, long long B, long long N, long long M)
{
	printf("so_easy_direct (%I64d,%I64d,%I64d,%I64d): %I64d\n", A,B,N,M,so_easy_direct(A,B,N,M));
}

void solve_so_easy_quick(long long A, long long B, long long N, long long M)
{
	Matrix_So_Easy m;
	m.a00 = A, m.a01 = B;
	m.a10 = 1, m.a11 = A;
	m = quick_power_mod<Matrix_So_Easy>(m, N - 1, M);
	long long nMod = 2 * (m.a00 * A + m.a01) % M;
	printf("so_easy_quick (%I64d,%I64d,%I64d,%I64d): %I64d\n", A, B, N, M, nMod);
}


#if 0

#include <iostream>  
#include <cstdio>  
#include <algorithm>  
#include <vector>  
#include <cstring>  
#include <queue>  
#include <map>  
#include <math.h>  
using namespace std;
typedef __int64 LL;
const LL MAXN = 333;
LL a, b, n, m, x, y;
struct rec
{
	LL a11, a12, a21, a22;
	rec() {}
	rec(LL a1, LL a2, LL a3, LL a4) { a11 = a1; a12 = a2; a21 = a3; a22 = a4; }
	rec operator*(rec p)
	{
		return rec(a11*p.a11 + a12*p.a21, a11*p.a12 + a12*p.a22, a21*p.a11 + a22*p.a21, a21*p.a12 + a22*p.a22);
	}
	rec operator%(LL p)
	{
		return rec(a11%p, a12%p, a21%p, a22%p);
	}
}r, ans;

void fast(LL n, LL m)
{
	while (n)
	{
		if (n & 1)
		{
			ans = ans*r;
		}
		r = r*r;
		r = r%m;
		ans = ans%m;
		n /= 2;
	}
}

int main()
{
//	while (scanf_s("%I64d%I64d%I64d%lld", &a, &b, &n, &m) != -1){
	srand(time(0));
	const unsigned int A_M_RANGE = 1 << 15;
	const unsigned int B_N_RANGE = 1 << 31;
	for (int i = 0; i < 100; ++i) {
		LL a = 2 + rand() % (A_M_RANGE - 2);
		LL m = rand() % A_M_RANGE;
		LL b = (a - 1)*(a - 1) + 1 + (rand() % (a * 2 - 2));
		LL n = rand() % B_N_RANGE;
		r.a11 = a, r.a12 = b, r.a21 = 1, r.a22 = a;
		ans.a11 = 1, ans.a12 = 0, ans.a21 = 0, ans.a22 = 1;
		fast(n, m);
		x = ans.a11 * 2;
		x = (x%m + m) % m;
		printf("%I64d\n", x);

		solve_so_easy_direct((unsigned)a, (unsigned)b, (unsigned)n, (unsigned)m);
		solve_so_easy_quick((unsigned)a, (unsigned)b, (unsigned)n, (unsigned)m);

	}
	return 0;
}

#else

int main()
{
	{
		//���Կ�����
		printf("2^15 = %d\n", quick_power(2, 15));
		printf("3^10 = %d\n", quick_power(3, 10));
	}
	{
		//����쳲���ϵ��
		Matrix_Fibonacci m;
		m.a00 = 1; m.a01 = 1;
		m.a10 = 1; m.a11 = 0;
		printf("the 10 fibona num is %d  ", quick_power<Matrix_Fibonacci>(m, 10).a01);
		printf("test fibonacci :%d \n", test_fibonacci(10));
	}
	{
		srand(time(0));
		const unsigned int A_M_RANGE = 1 << 15;
		const unsigned int B_N_RANGE = 1 << 31;
		for (int i = 0; i < 100; ++i) {
			unsigned int A = 2 + rand() % (A_M_RANGE - 2);
			unsigned int M = rand() % A_M_RANGE;
			unsigned int B = (A - 1)*(A - 1) + 1 + (rand() % (A * 2 - 2));
			unsigned int N = rand() % B_N_RANGE;
			//����ֱ�ӽ��so_easy����
			solve_so_easy_direct(A, B, N, M);
			solve_so_easy_quick(A, B, N, M);
		}
		
	}

}

#endif

/*
	ע����ֵ���
*/
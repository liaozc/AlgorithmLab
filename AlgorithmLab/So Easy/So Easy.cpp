// So Easy.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <time.h>

/*
	快速幂和矩阵快速幂的应用

	快速幂是将求M的N次幂的操作时间降低的方法，如果正常求法，M的N次幂，时间复杂度为O(N).用对折的方法可以减低到O(logN)
	M^N = M * M * M ... * M,
	N = 2^a1 + 2^a2 + .. + 2^an,
	解N为二进制格式，假如，N(2) = 11011,假设有K位，依次求M^1，M^2,....,M^K,一共O(logN)个，每个为1的bit位被乘入临时变量中。
	

	快速幂的代码求解如下：不考虑溢出的情况
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
	矩阵快速幂的思维差不多，就是将线性的加法操作，改为线性的乘法操作，再利用计算的中间变量（和快速幂一般道理）
	如求斐波那系列，F(1) = F(2) = 1, F(N) = F(N-1) + F(N-2),N > 2; 求F(N),一般的做法是每个n<N都要顺序求出，这个时间为O(N).
	如将F(N)和F(N-1)组成矩阵，则 M[N] = {F(N),F(N-1)}T, 则M[N + 1] = A*M[N],其中A = {{1,1},{1,0}},
	故F(N) = M[N].a00; M[N] = A^(N-1) * M[1].这时，如果能将A^(N-1)的计算量减少，就能把算法的复杂度减低。由于矩阵乘法的可结合性，
	知道应用于快速幂的方法同样适用于此。

	矩阵快速幂的代码求解如下：不考虑溢出
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
	求[(A + sqrt(B))^N]%M,A B,N M 均为整数，且  (A -1)^2 < B < A^2.[]为向上取整符号 0< A,M < 2^15, 0< B,N < 2^31.
	
	由题目知道，A，B，N，M均可为int.

	1.先求取整后的结果：
	令 (A + sqrt(B))^N = XN + YN*sqrt(B),即XN为其整数部分，YN为其无理数部分系数，知道YN为二次系数分布中，sqrt(B)的指数为奇数的所有项提取sqrt(B)后的整数和.
	令 (A - sqrt(B))^N = XN' + YN'*sqrt(B),由二项分布知道，XN = XN',YN = -YN'. 所以 (A + sqrt(B))^N + (A - sqrt(B))^N = 2*XN.
	而因为 (A - 1)^2< B < A^2,所以  A-1 <sqrt(B) < A, 0 < A - Sqrt(B) < 1, 所以 0 < (A - sqrt(B))^N < 1; 所以， (A + sqrt(B))^N = 2*XN - (A - sqrt(B))^N,
	故[(A + sqrt(B))^N] = 2*XN.

	2.求XN.
	因为 (A + sqrt(B))^N = XN + YN*sqrt(B)，(A + sqrt(B))^(N+1) = (XN + YN*sqrt(B))(A + sqrt(B)) = XN* A + B* YN + (XN + A*YN)*sqrt(B);即 XN+1 = XN*A + B*YN, YN+1 = XN + A*YN,
	可以从[X1,Y1]([1,1]) 开始做乘法，直到[XN,YN],时间复杂度为O(N),也可以构建矩阵，利用快速幂的算法，降低到O(logN)的复杂度。

	A：直接相乘的方法.
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
	B:构建矩阵快速乘法
	
	TRS = |A,B|  则 M[N+1] = TRS * M[N], 其中 M[N] = [XN,YN]T
		  |1,A|,                                    
	知道 M[N] = TRS^N-1 * M[1] ,N > 1
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
		//测试快速幂
		printf("2^15 = %d\n", quick_power(2, 15));
		printf("3^10 = %d\n", quick_power(3, 10));
	}
	{
		//测试斐波那系列
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
			//测试直接解决so_easy问题
			solve_so_easy_direct(A, B, N, M);
			solve_so_easy_quick(A, B, N, M);
		}
		
	}

}

#endif

/*
	注意数值溢出
*/
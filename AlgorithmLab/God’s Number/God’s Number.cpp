// God’s Number.cpp : Defines the entry point for the console application.
//

/*
	求(2^(2^(2..)))数对整数P的取值

	证明： 设f(l,2) 是2的l级数，例如，当l = 1 时，f(l,2) = f(1,2) = 2,l = 2 时，f(l,2) = f(2,2) = 2^2 = 4... 以此类推，证明，当 f(l,2) > P时，f(l,2)% P = f(l+1,2)%P.
	
	引理：f(l+1,2)可以整除 f(l,2),且是f(l,2)的整数幂次方。
	证： 当 l=1 时，f(2,2) = f(1,2) * f(1,2) = 4 = 2^2.题设成立。设当 l = L时也有同样的结论，即f(L+1,2) = f(L,2) ^ M,M为整且易知大于1。令 f(L,2)^(M - 1) = M',
	当 l = L + 1时，f(L+ 2,2) = 2^f(L+1,2) = 2^(M'*f(L,2)) =(2^f(L,2))^M' = f(L+1,2)^M', 即f(L+2，2)能被f(L+ 1,2)整除，且是f(L+1,2)的幂次方。引理得证。

	现证明定理：
	设f(l,2) > P, 且f(l,2) % P = K, 则 f(l + 1,2) = 2^f(l,2) = f(l,2)^M,M为整数，（据引理），即f(l+1,2) = (SP + K)^M,故可得 f(l+1,2)%P = K; <F**K,最后一步是错的...>
	证毕。

	编程：只需找出比P大的数，然后输出即可
*/

/* 错漏百出 数学的严谨何在？？

#include <cstdio>
#include <cstdlib>
#include <time.h>

long long  fast_mod(long long s, long long d)
{
	if (d <= 0) return -1;
	while (s >= d) {
		long long ts = s - d;
		s = ts;
	};
	return s;
}

long long get_enogh_god_number()
{
	long long s = 1;
	int  lastLen = 1;
	int Max = int(1E8);
	while (s < Max) {
		long long ts = 1;
		int i = 0;
		for (; i < s; ++i) {
			ts *= 2;
			if (ts > Max && i%lastLen == 0 ) break;
		}
		lastLen = i;
		s = ts;
	}
	return s;
}

int main()
{
	srand(time(0));
	int count = 0;
	long long  god_number = get_enogh_god_number();
	while (count < 10) {
		int P = 1 + rand() % (int)1E8;
		printf("<%d,%d>\n",P,god_number%P);
		count++;
	};

    return 0;
}

*/

/*标准解法
	用欧拉降幂公式，A^B%C = A^(B%φ(C) + φ(C))%C，φ(x)是欧拉函数，表示这小于整数x的和x互质的整数的个数。
	φ(x) = x*(1- 1/p1)(1- 1/p2)...(1 - 1/pn). 其中 p1..pn 是x的互质因子.

	知道 φ(x)的性质，当x是质数时，φ(x) = x - 1. φ(x) < x;

	令 f(l) = 2^(2^(2..)),其中l 是2的个数，知道 f(l + 1) = 2^f(l);

	f(l)%C = 2^f(l-1)%C = 2^(f(l-1)%φ(C) + φ(C))%C,对于定数C，φ(C)已知且φ(C) < C,则经过一定步骤K,（K<C），得到C1，C2，C3，..CK,
	其中Ci+1 = φ(Ci)。C1 = C,CK = 1,f(l-K)%φ(Ck) = 0,

*/

#include <cstdio>
#include <cstdlib>
#include <time.h>

typedef long long LLong;

LLong Pin(LLong lC)
{
	LLong lTempC = lC;
	LLong lRet = lC;
	for (int i = 2; i*i < lTempC; ++i) {
		if (lTempC%i == 0) {//ltC能被i整除
			lRet = lRet / i * (i - 1);			//先除后乘是为了避免越界
			while (lTempC%i == 0)				//去除相同的因子
				lTempC /= i;
		}
	}
	if (lTempC != 1) lRet = lRet/ lTempC * (lTempC - 1);
	return lRet;
}

LLong QuickPower(LLong A,LLong B,LLong C)
{ 
	LLong lTempA = A;
	LLong lRet = 1;
	while (B) {
		if (B & 1) lRet = (lRet * lTempA) % C;
		lTempA = lTempA * lTempA % C;
		B >>= 1;
	}
	return lRet;
}

LLong Solve(LLong N)
{
	if (N == 1) return 0;
	LLong lPinN = Pin(N);
	return QuickPower(2,Solve(lPinN) + lPinN,N);
}

int main()
{
	int C = 0;
	scanf_s("%d", &C);
	printf("solve:%d \n", (int)Solve(C));

	int A = 0,  B = 0;
	scanf_s("%d %d %d",&A,&B,&C);
	int pinC = Pin(C);
	B = B%pinC;
	printf("A^B%%C: %d\n", QuickPower(A, B, C));
}
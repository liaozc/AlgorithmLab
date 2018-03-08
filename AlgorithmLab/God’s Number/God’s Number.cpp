// God’s Number.cpp : Defines the entry point for the console application.
//

/*
	求(2^(2^(2..)))数对整数P的取值

	证明： 设f(l,2) 是2的l级数，例如，当l = 1 时，f(l,2) = f(1,2) = 2,l = 2 时，f(l,2) = f(2,2) = 2^2 = 4... 以此类推，证明，当 f(l,2) > P时，f(l,2)% P = f(l+1,2)%P.
	
	引理：f(l+1,2)可以整除 f(l,2),且是f(l,2)的整数幂次方。
	证： 当 l=1 时，f(2,2) = f(1,2) * f(1,2) = 4 = 2^2.题设成立。设当 l = L时也有同样的结论，即f(L+1,2) = f(L,2) ^ M,M为整且易知大于1。令 f(L,2)^(M - 1) = M',
	当 l = L + 1时，f(L+ 2,2) = 2^f(L+1,2) = 2^(M'*f(L,2)) =(2^f(L,2))^M' = f(L+1,2)^M', 即f(L+2，2)能被f(L+ 1,2)整除，且是f(L+1,2)的幂次方。引理得证。

	现证明定理：
	设f(l,2) > P, 且f(l,2) % P = K, 则 f(l + 1,2) = 2^f(l,2) = f(l,2)^M,M为整数，（据引理），即f(l+1,2) = (SP + K)^M,故可得 f(l+1,2)%P = K;
	证毕。

	编程：只需找出比P大的数，然后输出即可
*/

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


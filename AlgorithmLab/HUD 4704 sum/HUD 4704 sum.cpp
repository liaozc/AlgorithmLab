// HUD 4704 sum.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

/*
	欧拉定理 / 费马小定理  / 隔板法 / 快速幂求余 / 大数求余  

	欧拉定理证明：
	a^φ(p) % p = 1, a 和 p 互质. 费马小定理 a^(p - 1) % p = 1, a 和 p互质且 p为质数。
	证明:
			    令 X1，X2，....,Xφ(p) 为所有小于P的P的互质数（构成完全剩余系），M1 = a * X1，M2 = a* X2,... Mφ(p) = a * Xφ(p).
				则 Mi，Mj 模 P 不相等。(i != j) <1> 且 Mi%P 和 P互质 <2>
		
		证明1>: 不失一般性，设Mi为较大数，如果Mi和Mj模P相等，则 Mi - Mj 可以被P整除，即a(Xi - Xj) % P = 0, 因为a 和 P互质，则(Xi - Xj)%P = 0.
				因为 Xi - Xj < P,所以(Xi - Xj)%P != 0. 故 Mi 和Mj 模P 不相等。

		证明2>: 设 Mi%P 和 P 有公因子 r，且 r != 1, 则 Mi%P = rX，设 P = rY, Mi = Ki * P + rY, 则 Mi 和 P 有公约数r，而 Mi 和 P互质为已知条件，所以假设
				不成立。

				由<1>,<2>知道，M1，M2，...，Mφ(p) 模 P 结果构成构成完成剩余系。即
				M1 * M2 ... * Mφ(p) % P = X1 * X2 ... * Xφ(p) % P. 即
				a ^ φ(p) * (M1 * M2 ... * Mφ(p)) = X1 * X2 ... * Xφ(p) % P, 因为 X1 * X2 ... * Xφ(p) 和 P 互质，所以 a ^ φ(p) % P = 1.
				证毕。
				(实在是天才的想法，致敬欧拉)
	费马小定理：
	P是素数是 φ(p) = p - 1. 代入欧拉定理，得证.

	应用：
		<x1,x2,...,xk> 是 正整数 N 的一个切分，即 x1 + ... + xk = N,且 xi > 0. 令S(k) 为其切分个数。求 S(1) + .. + S(N) % 1e9 + 7
		
		1> S(k) ：隔板法
		1 / 1 / ..... / 1 .. / 1 
		如上，将 N 切分为 N 份，k 分割实际是在 N-1 个间隔中找出 k - 1 个
		故 S(k) = C(k-1 ,N -1).
		所以 S(1) + ... + S(N) = C(0,N -1) + ... + C(N - 1,N - 1) = 2 ^ (N - 1)
		
		令 NM = (N - 1)% φ(1e9 + 7 - 1), 则 变为求 2^(NM) % (1e9 + 7) 利用快速幂求余法即可

*/

typedef long long ll;

ll P = ll(1e9 + 7);

ll fast_mod(ll a, ll b, ll c)
{
	ll ret = 1;
	while (b) {
		if (b & 1) ret = (ret * a) % c;
		a = a * a % c;
		b >>= 1;
	}

	return ret;
}

ll large_number_mod(char str[], ll c)
{
	int len = strlen(str);
	ll ret = 0;
	for (int i = 0; i < len; ++i) {
		ret = (ret * 10 + str[i] - '0') % c;
	}
	return ret;
}

int main()
{
	while (true) {
		char ch[100050];
		scanf_s("%s", ch, 100000);
		if (strcmp(ch, "exit") == 0) break;
		ll mod = large_number_mod(ch, P - 1);
		mod = fast_mod(2, mod, P);
		printf("mod 1e9 + 7 = %I64d \n", mod);
	}
    return 0;
}


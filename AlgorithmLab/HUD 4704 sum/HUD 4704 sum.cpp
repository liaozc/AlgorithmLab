// HUD 4704 sum.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

/*
	ŷ������ / ����С����  / ���巨 / ���������� / ��������  

	ŷ������֤����
	a^��(p) % p = 1, a �� p ����. ����С���� a^(p - 1) % p = 1, a �� p������ pΪ������
	֤��:
			    �� X1��X2��....,X��(p) Ϊ����С��P��P�Ļ�������������ȫʣ��ϵ����M1 = a * X1��M2 = a* X2,... M��(p) = a * X��(p).
				�� Mi��Mj ģ P ����ȡ�(i != j) <1> �� Mi%P �� P���� <2>
		
		֤��1>: ��ʧһ���ԣ���MiΪ�ϴ��������Mi��MjģP��ȣ��� Mi - Mj ���Ա�P��������a(Xi - Xj) % P = 0, ��Ϊa �� P���ʣ���(Xi - Xj)%P = 0.
				��Ϊ Xi - Xj < P,����(Xi - Xj)%P != 0. �� Mi ��Mj ģP ����ȡ�

		֤��2>: �� Mi%P �� P �й����� r���� r != 1, �� Mi%P = rX���� P = rY, Mi = Ki * P + rY, �� Mi �� P �й�Լ��r���� Mi �� P����Ϊ��֪���������Լ���
				��������

				��<1>,<2>֪����M1��M2��...��M��(p) ģ P ������ɹ������ʣ��ϵ����
				M1 * M2 ... * M��(p) % P = X1 * X2 ... * X��(p) % P. ��
				a ^ ��(p) * (M1 * M2 ... * M��(p)) = X1 * X2 ... * X��(p) % P, ��Ϊ X1 * X2 ... * X��(p) �� P ���ʣ����� a ^ ��(p) % P = 1.
				֤�ϡ�
				(ʵ������ŵ��뷨���¾�ŷ��)
	����С����
	P�������� ��(p) = p - 1. ����ŷ��������֤.

	Ӧ�ã�
		<x1,x2,...,xk> �� ������ N ��һ���з֣��� x1 + ... + xk = N,�� xi > 0. ��S(k) Ϊ���зָ������� S(1) + .. + S(N) % 1e9 + 7
		
		1> S(k) �����巨
		1 / 1 / ..... / 1 .. / 1 
		���ϣ��� N �з�Ϊ N �ݣ�k �ָ�ʵ������ N-1 ��������ҳ� k - 1 ��
		�� S(k) = C(k-1 ,N -1).
		���� S(1) + ... + S(N) = C(0,N -1) + ... + C(N - 1,N - 1) = 2 ^ (N - 1)
		
		�� NM = (N - 1)% ��(1e9 + 7 - 1), �� ��Ϊ�� 2^(NM) % (1e9 + 7) ���ÿ��������෨����

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


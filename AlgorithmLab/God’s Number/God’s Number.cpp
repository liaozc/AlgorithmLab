// God��s Number.cpp : Defines the entry point for the console application.
//

/*
	��(2^(2^(2..)))��������P��ȡֵ

	֤���� ��f(l,2) ��2��l���������磬��l = 1 ʱ��f(l,2) = f(1,2) = 2,l = 2 ʱ��f(l,2) = f(2,2) = 2^2 = 4... �Դ����ƣ�֤������ f(l,2) > Pʱ��f(l,2)% P = f(l+1,2)%P.
	
	����f(l+1,2)�������� f(l,2),����f(l,2)�������ݴη���
	֤�� �� l=1 ʱ��f(2,2) = f(1,2) * f(1,2) = 4 = 2^2.����������赱 l = LʱҲ��ͬ���Ľ��ۣ���f(L+1,2) = f(L,2) ^ M,MΪ������֪����1���� f(L,2)^(M - 1) = M',
	�� l = L + 1ʱ��f(L+ 2,2) = 2^f(L+1,2) = 2^(M'*f(L,2)) =(2^f(L,2))^M' = f(L+1,2)^M', ��f(L+2��2)�ܱ�f(L+ 1,2)����������f(L+1,2)���ݴη��������֤��

	��֤������
	��f(l,2) > P, ��f(l,2) % P = K, �� f(l + 1,2) = 2^f(l,2) = f(l,2)^M,MΪ������������������f(l+1,2) = (SP + K)^M,�ʿɵ� f(l+1,2)%P = K;
	֤�ϡ�

	��̣�ֻ���ҳ���P�������Ȼ���������
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


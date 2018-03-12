// God��s Number.cpp : Defines the entry point for the console application.
//

/*
	��(2^(2^(2..)))��������P��ȡֵ

	֤���� ��f(l,2) ��2��l���������磬��l = 1 ʱ��f(l,2) = f(1,2) = 2,l = 2 ʱ��f(l,2) = f(2,2) = 2^2 = 4... �Դ����ƣ�֤������ f(l,2) > Pʱ��f(l,2)% P = f(l+1,2)%P.
	
	����f(l+1,2)�������� f(l,2),����f(l,2)�������ݴη���
	֤�� �� l=1 ʱ��f(2,2) = f(1,2) * f(1,2) = 4 = 2^2.����������赱 l = LʱҲ��ͬ���Ľ��ۣ���f(L+1,2) = f(L,2) ^ M,MΪ������֪����1���� f(L,2)^(M - 1) = M',
	�� l = L + 1ʱ��f(L+ 2,2) = 2^f(L+1,2) = 2^(M'*f(L,2)) =(2^f(L,2))^M' = f(L+1,2)^M', ��f(L+2��2)�ܱ�f(L+ 1,2)����������f(L+1,2)���ݴη��������֤��

	��֤������
	��f(l,2) > P, ��f(l,2) % P = K, �� f(l + 1,2) = 2^f(l,2) = f(l,2)^M,MΪ������������������f(l+1,2) = (SP + K)^M,�ʿɵ� f(l+1,2)%P = K; <F**K,���һ���Ǵ��...>
	֤�ϡ�

	��̣�ֻ���ҳ���P�������Ȼ���������
*/

/* ��©�ٳ� ��ѧ���Ͻ����ڣ���

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

/*��׼�ⷨ
	��ŷ�����ݹ�ʽ��A^B%C = A^(B%��(C) + ��(C))%C����(x)��ŷ����������ʾ��С������x�ĺ�x���ʵ������ĸ�����
	��(x) = x*(1- 1/p1)(1- 1/p2)...(1 - 1/pn). ���� p1..pn ��x�Ļ�������.

	֪�� ��(x)�����ʣ���x������ʱ����(x) = x - 1. ��(x) < x;

	�� f(l) = 2^(2^(2..)),����l ��2�ĸ�����֪�� f(l + 1) = 2^f(l);

	f(l)%C = 2^f(l-1)%C = 2^(f(l-1)%��(C) + ��(C))%C,���ڶ���C����(C)��֪�Ҧ�(C) < C,�򾭹�һ������K,��K<C�����õ�C1��C2��C3��..CK,
	����Ci+1 = ��(Ci)��C1 = C,CK = 1,f(l-K)%��(Ck) = 0,

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
		if (lTempC%i == 0) {//ltC�ܱ�i����
			lRet = lRet / i * (i - 1);			//�ȳ������Ϊ�˱���Խ��
			while (lTempC%i == 0)				//ȥ����ͬ������
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
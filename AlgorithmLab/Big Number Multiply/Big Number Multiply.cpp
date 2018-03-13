// Big Number Multiply.cpp : Defines the entry point for the console application.
//

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <string>

#define max(a,b) a > b ? a : b;
char Result[220];
char A[100];
char B[100];

void ChangeToNumber(char ch[],char str[],int _count)
{
	for (int i = 0; i < _count; ++i) {
		ch[i] = str[i] - '0';
	}
}

void PrintNumber(char ch[], int _count)
{
	char str[200];
	for (int i = 0; i < _count; ++i) {
		str[i] = ch[i] + '0';
	}
	str[_count] = '\0';
	printf("%s\n", str);
}

int AddNumber(int pos, int val, char Ret[])
{
	while (true) {
		Ret[pos] = Ret[pos] + val;
		int u = Ret[pos] % 10;
		int de = Ret[pos] / 10;
		Ret[pos] = u;
		if (de == 0) break;
		pos++;
		val = de;
	}
	return pos;
}

int MultiplyNumber(char A[],int _countA, char B[],int _countB, char Ret[],int _countR)
{
	int ret = 0;
	memset(Ret,0,sizeof(char) * _countR);
	for (int i = 0; i < _countB; ++i) {
		for (int j = 0; j < _countA; ++j) {
			int a = A[j];
			int b = B[i];
			int r = a * b;
			int temp = AddNumber(_countB + _countA - i - j - 2, r, Ret);
			ret = max(ret,temp);
		}
	}
	for (int i = 0; i < ret - i; ++i) {
		char temp = Ret[i];
		Ret[i] = Ret[ret - i];
		Ret[ret - i] = temp;
	}
	return ret + 1;
}

int main()
{
	char str[100];
	while(true){
		scanf_s("%s", str, 100);
		if (strcmp("exit", str) == 0) break;
		int countA = strlen(str);
		ChangeToNumber(A, str, countA);
		scanf_s("%s", str, 100);
		int countB = strlen(str);
		ChangeToNumber(B, str, countB);
		int CountR = MultiplyNumber(A, countA, B, countB, Result, 200);
		PrintNumber(Result, CountR);
	};
	
    return 0;
}


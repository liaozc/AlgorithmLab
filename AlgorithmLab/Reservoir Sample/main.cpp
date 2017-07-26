// Reservoir Sample.cpp : Defines the entry point for the console application.
//


/*	question:

input an unknown size array��seleted N element from it. 

*/

/* ˼·��
	ǰN��������������ÿһ��������֮ǰ�ĵ�ǰ���������е�ÿһ���� 1/K �ĸ����滻��K�ǵ�ǰ��Ԫ�ص��������

	��ѧ��������ͳ��ѧ��������
*/

#include "stdafx.h"
#include <cstdlib>
#include <time.h>

int* pInputs = nullptr;

int GenerateInputs() 
{
	srand(time(0));
	int L = rand()%100;
	while(L < 10){
		L = rand()%100;
	}
	pInputs = new int[L];
	for(int i = 0; i < L; ++ i){
		pInputs[i] = rand()%100;
	}
	return L;
}

int main()
{
	int L = GenerateInputs();
	int keepAry[10];
	for(int i = 0; i < L; ++ i){
		if(i < 10) keepAry[i] = pInputs[i];
		else{
			srand(time(0));
			for(int j = 0; j < 10; ++ j){
				int r = rand()%(i+1);
				if(r == 1){ keepAry[j] = pInputs[i];break;}
			}
		}
	}
	for (int i = 0; i < L; ++i) {
		printf("%d ", pInputs[i]);
	}
	printf("\n");
	delete[] pInputs;
	for(int i = 0; i < 10; ++ i){
		printf("%d ",keepAry[i]);
	}
	printf("\n");
    return 0;
}


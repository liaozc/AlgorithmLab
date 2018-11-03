#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "xtree.h"

int main()
{
	RBTree r;
	
	for (int i = 1; i < 7; ++i)
	{
		r.Insert(i);
	}

	printf("[height] £º %d\n", r.Height());

	int val = -9965;
	RBTreeNode* node = r.find(val);
	if (node && node->Key == val)
		printf("founded \n");

	r.Remove(1);

    return 0;
}


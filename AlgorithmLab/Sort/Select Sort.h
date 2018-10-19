#pragma once

void select_sort(int inputArr[], int num)
{
	for (int i = 0; i < num; ++i)
	{
		int index = i;
		for (int j = i + 1; j < num; ++j)
		{
			if (inputArr[j] < inputArr[i])
				index = j;
		}

		int temp = inputArr[i];
		inputArr[i] = inputArr[index];
		inputArr[index] = temp;
	}

}

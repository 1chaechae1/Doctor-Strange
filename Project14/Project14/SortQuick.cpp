/*#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void* arg1, const void* arg2)
{
	if (*(double*)arg1 > *(double*)arg2) return 1;
	else if (*(double*)arg1 < *(double*)arg2) return -1;
	else return 0;
}
int main()
{
	int i;
	double list[9] = { 2.1, 0.9, 1.6, 3.8, 1.2, 4.4, 6.2, 9.1, 7.7 };
	qsort((void*)list, 9, sizeof(double), compare);
	for (i = 0; i < 9; i++)
		printf("%4.1f ", list[i]);
}*/
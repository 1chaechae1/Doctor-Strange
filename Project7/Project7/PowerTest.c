#include <stdio.h>

double power(double x, int n)
{
	if (n == 0) return 1;
	else if ((n % 2) == 0)						// n이 짝수인 경우
		return power(x * x, n / 2);
	else
		return x * power(x * x, (n - 1) / 2);	// n이 홀수인 경우
}

double slow_power(double x, int n)
{
	int i;
	double result = 1.0;
	for (i = 0; i < n; i++)
		result = result * x;
	return result;
}

#include <stdlib.h>
#include <time.h>
void main()
{
	int i;
	clock_t t1, t2;
	double d1, d2;
	printf("Fast Power... ");
	t1 = clock();
	for (i = 0; i < 10000000; i++)
		power(2, 500);
	t2 = clock();
	printf("%lf[sec]\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
	printf("\nSlow Power... ");
	t1 = clock();
	for (i = 0; i < 10000000; i++)
		slow_power(2, 500);
	t2 = clock();
	printf("%lf[sec]\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
}
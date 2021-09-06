#include <stdio.h>

int factorial(int n)
{
	printf("factorial(%d)\n", n);	// 순환호출 순서 확인을 위한 출력문
	if (n == 1) return 1;
	else return (n * factorial(n - 1));
}

int factorial_iter(int n)
{
	int k, result = 1;
	for (k = n; k > 0; k--)
		result = result * k;
	return result;
}

void main() { factorial(3); }

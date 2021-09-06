#include <stdio.h>

int fib(int n)
{
	printf("%d\n", n);
	if (n == 0) return 0;
	if (n == 1) return 1;
	return (fib(n - 1) + fib(n - 2));
}
int fib_iter(int n)
{
	
	int i, tmp, current, last;
	if (n < 2) return n;
	else {
		last = 0;
		current = 1;
		for (i = 2; i <= n; i++) {
			printf("%d\n", current);
			tmp = current;
			current += last;
			last = tmp;
		}
		return current;
	}
}
#include <stdlib.h>
#include <time.h>
void main()
{
	int a;
	int b;
	a = fib(5);

	printf("\n");
	b = fib_iter(5);

	printf("\na: %d\nb: %d\n", a, b);

}
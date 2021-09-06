#include <stdio.h>

void copy_array(int a[], int b[], int len)
{
	int i;
	for (i = 0; i < len; i++)
		b[i] = a[i];
}
void copy_variable(int a, int b)
{
	b = a;
}
void main()
{
	int A[5] = { 10, 20, 30 };
	int B[5], i, x = 2018, y = 0;

	copy_variable(x, y); // 함수를 이용한 변수 복사(실패)
	copy_array(A, B, 5); // 함수를 이용한 배열 복사(성공)

	printf("변수 복사 결과: x=%d, y=%d\n", x, y);
	printf("배열 복사 결과: \n");
	for (i = 0; i < 5; i++) {
		printf("A[%d] = %d\t", i, A[i]);
		printf("B[%d] = %d\n", i, B[i]);
	}
}
/*#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_NODE 200

//void error(char str[]) { ... }	// 프로그램 3.1의 함수와 동일
void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}	
typedef int HNode;
#define Key(n) (n)	
HNode heap[MAX_HEAP_NODE];
int heap_size;	

#define Parent(i) (heap[i/2])	// i의 부모 노드
#define Left(i) (heap[i*2])		// i의 왼쪽 자식 노드
#define Right(i) (heap[i*2+1])	// i의 오른쪽 자식 노드

void init_heap() { heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap() { return (heap_size == MAX_HEAP_NODE - 1); }
HNode find_heap() { return heap[1]; }

void insert_heap(HNode n)
{
	int i;
	if (is_full_heap()) return;
	i = ++(heap_size);
	while (i != 1 && Key(n) > Key(Parent(i))) {
		heap[i] = Parent(i);
		i /= 2;
	}
	heap[i] = n;
}

HNode delete_heap()
{
	HNode hroot, last;
	int parent = 1, child = 2;
	if (is_empty_heap() != 0)
		error("힙 트리 공백 에러");
	
	hroot = heap[1];
	last = heap[heap_size--];
	while (child <= heap_size) {
		if (child < heap_size && Key(Left(parent)) < Key(Right(parent)))
			child++;
		if (Key(last) >= Key(heap[child]))
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = last;
	return hroot;
}

void print_array(int a[], int n, char* msg)
{
	int i;
	printf("%10s: ", msg);
	for (i = 0; i < n; i++)
		printf("%3d", a[i]);
	printf("\n");
}

void main()
{
	int i, data[10];
	
	for (i = 0; i < 10; i++)
		data[i] = rand() % 100;
	
	print_array(data, 10, "정렬 전");
	init_heap();
	
	for (i = 0; i < 10; i++)
		insert_heap(data[i]);			// 배열 항목들을 힙에 넣음
	for (i = 9; i >= 0; i--)
		data[i] = Key(delete_heap());	// 힙에서 꺼내 배열에 다시 저장
	print_array(data, 10, "정렬 후");
}*/
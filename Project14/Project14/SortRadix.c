/*#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE	100

typedef int Element;
typedef struct CircularQueue {
	Element data[MAX_QUEUE_SIZE];	// 요소의 배열
	int	front;			// 전단
	int	rear;			// 후단
} Queue;

// 프로그램 4.1의 error()함수와 동일
void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};
// 큐의 주요 연산: 공통

// 큐의 주요 연산: 공통
void init_queue(Queue* q) { q->front = q->rear = 0; ; }
int is_empty(Queue* q) { return q->front == q->rear; }
int is_full(Queue* q) { return q->front == (q->rear + 1) % MAX_QUEUE_SIZE; }
int size(Queue* q) { return(q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Queue* q, Element val)
{
	if (is_full(q))
		error("  큐 포화 에러");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = val;
}
Element dequeue(Queue* q)
{
	if (is_empty(q))
		error("  큐 공백 에러");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
Element peek(Queue* q)
{
	if (is_empty(q))
		error("  큐 공백 에러");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

// 큐 테스트를 위한 코드: 요소 종류마다 수정
void print_queue(Queue* q, char msg[]) {
	int i, maxi = q->rear;
	if (q->front >= q->rear) maxi += MAX_QUEUE_SIZE;
	printf("%s[%2d]= ", msg, size(q));
	for (i = q->front + 1; i <= maxi; i++)
		printf("%2d ", q->data[i % MAX_QUEUE_SIZE]);
	printf("\n");
}

void printStep(int arr[], int n, int val)
{
	int i;
	printf("  Step %2d = ", val);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}
void printArray(int arr[], int n, char* str)
{
	int i;
	printf("%s = ", str);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}


#define BUCKETS 10
#define DIGITS  4
void radix_sort(int list[], int n)
{
	Queue queues[BUCKETS];
	int factor = 1, i, b, d;

	for (i = 0; i < BUCKETS; i++)
		init_queue(&queues[i]);

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++)			// 자릿수에 따라 큐에 삽입
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b < BUCKETS; b++)		// 버킷에서 꺼내어 list로 합친다.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;					// 그 다음 자리수로 간다.
		printStep(list, n, d + 1);			// 중간 과정 출력용 문장
	}
}

void main()
{
	//int 	list[9] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
	int 	list[9] = { 25, 33, 68, 14, 9, 51, 36, 72, 27 };
	printArray(list, 9, "Original ");	// 정렬 전 배열 출력 

	radix_sort(list, 9); 	// 내림차순 선택정렬 알고리즘
	printArray(list, 9, "RadixSort");	// 정렬 후 배열 출력 
}*/
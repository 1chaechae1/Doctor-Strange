#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int Element;
typedef struct CircularQueue {
	Element data[MAX_QUEUE_SIZE];	// 요소의 배열
	int front;						// 전단
	int rear;						// 후단
} Queue;

// 프로그램 4.1의 error()함수와 동일
void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};
// 큐의 주요 연산: 공통

									// 큐의 주요 연산 : 공통
void init_queue(Queue* q) { q->front = q->rear = 0; ; }
int is_empty(Queue* q) { return q->front == q->rear; }
int is_full(Queue* q) { return q->front == (q->rear + 1) % MAX_QUEUE_SIZE; }
int size(Queue* q) {
	return(q->rear - q->front + MAX_QUEUE_SIZE) %
		MAX_QUEUE_SIZE;
}

void enqueue(Queue* q, Element val)
{
	if (is_full(q))
		error(" 큐 포화 에러");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = val;
}
Element dequeue(Queue* q)
{
	if (is_empty(q))
		error(" 큐 공백 에러");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
Element peek(Queue* q)
{
	if (is_empty(q))
		error(" 큐 공백 에러");
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

void main()
{
	int i;
	Queue q;
	init_queue(&q);
	for (i = 1; i < 10; i++)
		enqueue(&q, i);
	print_queue(&q, "선형큐 enqueue 9회");
	printf("\tdequeue() --> %d\n", dequeue(&q));
	printf("\tdequeue() --> %d\n", dequeue(&q));
	printf("\tdequeue() --> %d\n", dequeue(&q));
	print_queue(&q, "선형큐 dequeue 3회");
}
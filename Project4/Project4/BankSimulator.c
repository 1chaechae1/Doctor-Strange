#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct BankCustomer {
	int id;
	int tArrival;
	int tService;
} Customer;
typedef Customer Element;

// 프로그램 4.1의 6~37행 추가
Element data[MAX_QUEUE_SIZE];	// 요소의 배열
int front;						// 전단
int rear;						// 후단
								// 프로그램 3.1의 error()함수와 동일
void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};
// 큐의 주요 연산: 공통
void init_queue() { front = rear = 0; ; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
int size() { return(rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE; }

void enqueue(Element val)
{
	if (is_full())
		error(" 큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}
Element dequeue()
{
	if (is_empty())
		error(" 큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}
Element peek()
{
	if (is_empty())
		error(" 큐 공백 에러");
	return data[(front + 1) % MAX_QUEUE_SIZE];
}

int nSimulation;			// 시뮬레이션 시간
double probArrival;			// 단위시간에 도착하는 평균 고객 수
int tMaxService;			// 한 고객에 대한 최대 서비스 시간
int totalWaitTime;			// 전체 대기 시간
int nCustomers;				// 전체 고객의 수
int nServedCustomers;		// 서비스를 받은 전체 고객 수

double rand0to1() { return rand() / (double)RAND_MAX; }

void insert_customer(int arrivalTime)
{
	Customer a;
	a.id = ++nCustomers;
	a.tArrival = arrivalTime;
	a.tService = (int)(tMaxService * rand0to1()) + 1;
	printf(" 고객 %d 방문 (서비스 시간:%d분)\n", a.id, a.tService);
	enqueue(a);
}
void read_sim_params()
{
	printf("시뮬레이션 할 최대 시간 (예:10) = ");
	scanf("%d", &nSimulation);
	printf("단위시간에 도착하는 고객 수 (예:0.5) = ");
	scanf("%lf", &probArrival);
	printf("한 고객에 대한 최대 서비스 시간 (예:5) = ");
	scanf("%d", &tMaxService);
	printf("====================================================\n");
}
void run_simulation()
{
	Customer a;
	int clock = 0;
	int serviceTime = -1;
	
	init_queue();
	nCustomers = totalWaitTime = nServedCustomers = 0;
	while (clock < nSimulation) {
		clock++;
		printf("현재시각=%d\n", clock);

		if (rand0to1() > probArrival)
			insert_customer(clock);
		if (serviceTime > 0) serviceTime--;
		else {
			if (is_empty()) continue;
			a = dequeue();
			nServedCustomers++;
			totalWaitTime += clock - a.tArrival;
			printf(" 고객 %d 서비스 시작 (대기시간:%d분)\n",
				a.id, clock - a.tArrival);
			serviceTime = a.tService - 1;
		}
	}
}

void print_result()
{

printf("=================================================\n");
	printf(" 서비스 받은 고객수 = %d\n", nServedCustomers);
	printf(" 전체 대기 시간 = %d분\n", totalWaitTime);
	printf(" 서비스고객 평균대기시간 = %-5.2f분\n",
		(double)totalWaitTime / nServedCustomers);
	printf(" 현재 대기 고객 수 = %d\n", nCustomers - nServedCustomers);

}
#include <time.h>
void main()
{
	srand((unsigned int)time(NULL));
	read_sim_params();
	run_simulation();
	print_result();
}
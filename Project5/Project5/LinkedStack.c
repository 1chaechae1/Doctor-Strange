#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct LinkedNode {
	Element data;							// 데이터 영역
	struct LinkedNode* link;				// 다음 노드를 가리키는 포인터 변수
} Node;
Node* top = NULL;					// 연결 리스트의 헤드 포인터

void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};

int is_empty() { return top == NULL; }
void init_stack() { top = NULL; }

Element peek()
{
	if (is_empty())
		error("스택 공백 에러");
	return top->data;
}

void destroy_stack()
{
	while (is_empty() == 0)
		pop();
}

int size()
{
	Node* p;
	int count = 0;
	for (p = top; p != NULL; p = p->link) count++;
	return count;
}

void push(Element e)
{
	Node* p = (Node*)malloc(sizeof(Node));	// 노드 동적 할당
	p->data = e;							// 데이터 필드 초기화
	p->link = top;		// 그림 5.12의 (1)
	top = p;			// 그림 5.12의 (2)
}

Element pop()
{
	Node* p;
	Element e;
	if (is_empty())
		error("스택 공백 에러");

	p = top;				// 그림 5.13의 (1)
	top = p->link;			// 그림 5.13의 (2)
	e = p->data;			// 항목 데이터를 복사해 둠.
	free(p);				// 노드 동적 해제.
	return e;		// 복사한 항목 데이터를 반환.
}

void print_stack(char* msg)
{
	Node* p;
	printf("%s[%2d]= ", msg, size());
	for (p = top; p != NULL; p = p->link)
		printf("%2d ", p->data);
	printf("\n");
}

void main()
{
	int i;

	init_stack();
	for (i = 1; i < 10; i++)
		push(i);
	print_stack("연결된스택 push 9회");
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	printf("\tpop() --> %d\n", pop());
	print_stack("연결된스택 pop 3회");
	destroy_stack();
	print_stack("연결된스택 destroy ");
}
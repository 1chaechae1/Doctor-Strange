#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct LinkedNode {
	Element data;				// ������ ����
	struct LinkedNode* link;	// ���� ��带 ����Ű�� ������ ����
} Node;
Node* front = NULL;
Node* rear = NULL;

// ���α׷� 5.1�� error()�Լ��� ����
void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};

int is_empty() { return front == NULL; }
void init_queue() { front = rear = NULL; }
int size()
{
	Node* p;
	int count = 0;
	for (p = front; p != NULL; p = p->link) count++;
	return count;
}

void enqueue(Element e)
{
	Node* p = (Node*)malloc(sizeof(Node));	// ��� ���� �Ҵ�
	p->data = e;						// ������ �ʵ� �ʱ�ȭ
	p->link = NULL;						// ��ũ �ʵ� �ʱ�ȭ
	
	if (is_empty()) front = rear = p;		// �׸� 5.16�� (a)
	else {
		rear->link = p;						// �׸� 5.16 (b)�� (1)
		rear = p;						// �׸� 5.16 (b)�� (2)
	}
}

Element dequeue()
{
	Node* p;
	Element e;

	if (is_empty())
		error(" ť ���� ����");

	p = front;				// �׸� 5.17 (a)�� (b)�� (1)
	front = front->link;	// �׸� 5.17 (a)�� (b)�� (2)
	if (front == NULL) rear = NULL;		// �׸� 5.17 (b)�� (2)
	e = p->data;						// p�� �׸� ����
	free(p);							// p�� ���� ����
	return e;					// ����� �׸��� ��ȯ
}

Element peek()
{
	if (is_empty())
		error(" ť ���� ����");
	return front->data;
}
void destroy_queue()
{
	while (is_empty() == 0)
		dequeue();
}

void print_queue(char* msg)
{
	Node* p;
	printf("%s[%2d]= ", msg, size());
	for (p = front; p != NULL; p = p->link)
		printf("%2d ", p->data);
	printf("\n");
}

void main()
{
	int i;
	init_queue();
	for (i = 1; i < 10; i++)
		enqueue(i);
	print_queue("�����ť enqueue 9ȸ");
	printf("\tdequeue() --> %d\n", dequeue());
	printf("\tdequeue() --> %d\n", dequeue());
	printf("\tdequeue() --> %d\n", dequeue());
	print_queue("�����ť dequeue 3ȸ");
	destroy_queue();
	print_queue("�����ť destroy ");
}
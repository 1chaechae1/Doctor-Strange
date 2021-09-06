#include <stdio.h>
#include <stdlib.h>

typedef int TElement;

typedef struct BinTrNode {
	TElement data;
	struct BinTrNode* left;
	struct BinTrNode* right;
} TNode;
TNode* root;

void init_tree() { root = NULL; }
int is_empty_tree() { return root == NULL; }
TNode* get_root() { return root; }

TNode* create_tree(TElement val, TNode* l, TNode* r)
{
	TNode* n = (TNode*)malloc(sizeof(TNode));
	n->data = val;
	n->left = l;
	n->right = r;
	return n;
}

//================================================================
void preorder(TNode * n)
{
	if (n != NULL) {
		printf("[%c] ", n->data);
		preorder(n->left);
		preorder(n->right);
	}
}
void inorder(TNode* n)
{
	if (n != NULL) {
		inorder(n->left);
		printf("[%c] ", n->data);
		inorder(n->right);
	}
}
void postorder(TNode* n)
{
	if (n != NULL) {
		postorder(n->left);
		postorder(n->right);
		printf("[%c] ", n->data);
	}
}

//================================================================
#define MAX_QUEUE_SIZE 100
typedef TNode* Element;

// 프로그램 4.1의 6~37행 추가
Element data[MAX_QUEUE_SIZE];	// 요소의 배열
int front;						// 전단
int rear;						// 후단

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}
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

void levelorder(TNode* root)
{
	TNode* n;
	if (root == NULL) return;
	init_queue();
	enqueue(root);
	while (!is_empty()) {
		n = dequeue();
		if (n != NULL) {
			printf("[%c] ", n->data);
			//print_elem(n);
			enqueue(n->left);
			enqueue(n->right);
		}
	}
}

int count_node(TNode* n)
{
	if (n == NULL) return 0;
	return 1 + count_node(n->left) + count_node(n->right);
}

int count_leaf(TNode* n)
{
	if (n == NULL) return 0;
	if (n->left == NULL && n->right == NULL) return 1;
	else return count_leaf(n->left) + count_leaf(n->right);
}

int calc_height(TNode* n)
{
	int hLeft, hRight;
	if (n == NULL) return 0;
	hLeft = calc_height(n->left);
	hRight = calc_height(n->right);
	return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
}

int evaluate(TNode* n)
{
	int op1, op2;
	if (n == NULL) return 0;
	if (n->left == NULL && n->right == NULL) return n->data;
	else {
		op1 = evaluate(n->left);
		op2 = evaluate(n->right);
		switch (n->data) {
		case '+': return op1 + op2;
		case '-': return op1 - op2;
		case '*': return op1 * op2;
		case '/': return op1 / op2;
		}
		return 0;
	}
}

int calc_size(TNode* n)
{
	if (n == NULL) return 0;
	return n->data + calc_size(n->left) + calc_size(n->right);
}
void main()
{
	TNode* m2, * m3, * m4, * m5;
	m4 = create_tree(200, NULL, NULL);
	m5 = create_tree(500, NULL, NULL);
	m3 = create_tree(100, m4, m5);
	m2 = create_tree(50, NULL, NULL);
	root = create_tree(0, m2, m3);
	printf(" 폴더 용량 = %d KB\n", calc_size(root));
}
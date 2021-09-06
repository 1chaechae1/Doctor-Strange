#include <stdio.h>
#include <stdlib.h>

//================================================================
#define TreeData int
#define printTData(e) printf("[%2d] ", e)

typedef struct BinTrNode {
	TreeData data;				// 데이터 영역
	struct BinTrNode* left;		// 왼쪽 자식
	struct BinTrNode* right;	// 오른쪽 자식
} TNode;

int is_leaf(TNode* n)
{
	return (n->left == NULL && n->right == NULL);
}
TNode* new_node(TreeData val, TNode* l, TNode* r)
{
	TNode* n = (TNode*)malloc(sizeof(TNode));
	n->data = val;
	n->left = l;
	n->right = r;
	return n;
}

int count_node(TNode* n)
{
	if (n == NULL) return 0;
	return 1 + count_node(n->left) + count_node(n->right);
}
int count_leaf(TNode* n)
{
	if (n == NULL) return 0;
	if (is_leaf(n)) return 1;
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

//================================================================
#define MAX_QUEUE_SIZE 100
#define Element TNode*
#define print_elem(e) printf("[%2d] ", e->data)

Element data[MAX_QUEUE_SIZE];	 // 요소의 배열
int front;
int rear;
void error(char* str)
{
	fprintf(stderr, "%s\n", str);
	exit(1);
};
void init_queue() { front = rear = 0; ; }
int is_empty() { return front == rear;; }
int is_full() { return (rear + 1) % MAX_QUEUE_SIZE == front; }
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

void levelorder(TNode *root)
{
	TNode* n;

	if (root == NULL) return;
	init_queue();
	enqueue(root);
	while (!is_empty()) {
		n = dequeue();
		if (n != NULL) {
			print_elem(n);
			enqueue(n->left);
			enqueue(n->right);
		}
	}
}

//================================================================
int calc_height_diff(TNode * n)
{
	int hLeft, hRight;
	if (n == NULL) return 0;
	hLeft = calc_height(n->left);
	hRight = calc_height(n->right);
	return hLeft - hRight;
}

TNode* rotateLL(TNode* A)
{
	TNode* B = A->left;
	A->left = B->right;
	B->right = A;
	return B;
}
TNode* rotateRR(TNode* A) {
	TNode* B = A->right;
	A->right = B->left;
	B->left = A;
	return B;
}
TNode* rotateRL(TNode* A) {
	TNode* B = A->right;
	A->right = rotateLL(B);
	return rotateRR(A);
}
TNode* rotateLR(TNode* A) {
	TNode* B = A->left;
	A->left = rotateRR(B);
	return rotateLL(A);
}

TNode *reBalance(TNode *parent)
{
	int hDiff = calc_height_diff(parent);
	if (hDiff > 1) {
		if (calc_height_diff(parent->left) > 0)
			parent = rotateLL(parent);
		else
			parent = rotateLR(parent);
	}
	else if (hDiff < -1) {
		if (calc_height_diff(parent->right) < 0)
			parent = rotateRR(parent);
		else
			parent = rotateRL(parent);
	}
	return parent;
}

TNode* insert_node_AVL(TNode* parent, int key)
{
	if (key < parent->data) {
		if (parent->left != NULL)
			parent->left = insert_node_AVL(parent->left, key);
		else
			parent->left = new_node(key, NULL, NULL);

		return reBalance(parent);
	}
	else if (key > parent->data) {
		if (parent->right != NULL)
			parent->right = insert_node_AVL(parent->right, key);
		else
			parent->right = new_node(key, NULL, NULL);
		return reBalance(parent);
	}
	else {
		printf("중복된 키 에러\n");
		return NULL;
	}
}

//================================================================
void main()
{
	TNode* root;
	root = new_node(7, NULL, NULL); printf("\nAVL(7): ");
	levelorder(root);
	root = insert_node_AVL(root, 8); printf("\nAVL(8): "); levelorder(root);
	root = insert_node_AVL(root, 9); printf("\nAVL(9): "); levelorder(root);
	root = insert_node_AVL(root, 2); printf("\nAVL(2): "); levelorder(root);
	root = insert_node_AVL(root, 1); printf("\nAVL(1): "); levelorder(root);
	root = insert_node_AVL(root, 5); printf("\nAVL(5): "); levelorder(root);
	root = insert_node_AVL(root, 3); printf("\nAVL(3): "); levelorder(root);
	root = insert_node_AVL(root, 6); printf("\nAVL(6): "); levelorder(root);
	root = insert_node_AVL(root, 4); printf("\nAVL(5): "); levelorder(root);
	
	printf("\n 노드의 개수 = %d\n", count_node(root));
	printf(" 단말의 개수 = %d\n", count_leaf(root));
	printf(" 트리의 높이 = %d\n", calc_height(root));
}
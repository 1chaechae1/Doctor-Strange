#include <stdio.h> 
#include <stdlib.h> 
#define MAX_VTXS	256

void error(char str[])			// 오류 메시지 출력후 종료 함수: 공통
{
	printf("%s\n", str);
	exit(1);
}

typedef struct GraphNode {
	int id;					// 정점의 id 
	struct GraphNode* link;	// 다음 노드의 포인터 
} GNode;

typedef char VtxData;			// 그래프 정점에 저장할 데이터의 자료형 
GNode* adj[MAX_VTXS];		// 각 정점의 인접 리스트 
int		vsize;				// 정점의 개수 
VtxData vdata[MAX_VTXS];		// 정점에 저장할 데이터 배열 

int is_empty_graph() { return (vsize == 0); }
int is_full_graph() { return (vsize >= MAX_VTXS); }

void init_graph()
{
	int i;
	vsize = 0;
	for (i = 0; i < MAX_VTXS; i++)
		adj[i] = NULL;
}
void reset_graph()
{
	int i;
	GNode* n;
	for (i = 0; i < vsize; i++) {
		while (adj[i] != NULL) {
			n = adj[i];
			adj[i] = n->link;
			free(n);
		}
	}
	vsize = 0;
}
void insert_vertex(VtxData name)
{
	if (is_full_graph())
		error("Error: 그래프 정점의 개수 초과\n");
	else
		vdata[vsize++] = name;
}
void insert_edge(int u, int v)
{
	GNode* n = (GNode*)malloc(sizeof(GNode));
	n->link = adj[u];
	n->id = v;
	adj[u] = n;
}

void print_graph(char* msg)
{
	int i;
	GNode* v;
	printf("%s%d\n", msg, vsize);
	for (i = 0; i < vsize; i++) {
		printf("%c  ", vdata[i]);

		for (v = adj[i]; v != NULL; v = v->link)
			printf("   %c", vdata[v->id]);
		printf("\n");
	}
}

void load_graph(char* filename)
{
	int i, j, val, n;
	char	str[80];
	FILE* fp = fopen(filename, "r");
	if (fp != NULL) {
		init_graph();
		fscanf(fp, "%d", &n);
		for (i = 0; i < n; i++) {
			fscanf(fp, "%s", str);
			insert_vertex(str[0]);
			for (j = 0; j < n; j++) {
				fscanf(fp, "%d", &val);
				if (val != 0)
					insert_edge(i, j);
			}
		}
		fclose(fp);
	}
}



//---------------------------------------------------------------------------
// 스택
#define MAX_STACK_SIZE	100
#define Element	int
#define print_elem(e)	printf("%2d ", e)

Element	data[MAX_STACK_SIZE];	// 요소의 배열
int	top;						// 요소의 개수

void init_stack() { top = -1; }
int is_empty() {
	return top == -1;
}
int is_full() {
	return top == MAX_STACK_SIZE - 1;
}
void push(Element e)
{
	if (is_full())
		error("스택 포화 에러");
	data[++top] = e;
}
Element pop()
{
	if (is_empty())
		error("스택 공백 에러");
	return data[top--];
}
Element peek()
{
	if (is_empty())
		error("스택 공백 에러");
	return data[top];
}

//===========================================================================
// 그래프 위상정렬
//===========================================================================
void topological_sort()
{
	GNode* p;
	int i, u, w, inDeg[MAX_VTXS];

	for (i = 0; i < vsize; i++) inDeg[i] = 0;
	for (i = 0; i < vsize; i++) {			// 모든 정점의 진입 차수를 계산 
		p = adj[i];
		while (p != NULL) {
			inDeg[p->id]++;
			p = p->link;
		}
	}
	init_stack();
	for (i = 0; i < vsize; i++)			// 진입 차수가 0인 정점을 스택에 삽입 
		if (inDeg[i] == 0) push(i);

	while (!is_empty()) {				// 위상 순서를 생성 
		w = pop();
		printf(" %c ", vdata[w]);
		for (p = adj[w]; p != NULL; p = p->link) {
			u = p->id;
			inDeg[u]--;					//진입 차수를 감소 
			if (inDeg[u] == 0) push(u);
		}
	}
	printf("\n");
}

void main()
{
	int i;

	init_graph();
	for (i = 0; i < 6; i++)
		insert_vertex('A' + i);
	insert_edge(0, 2); 	insert_edge(0, 3); 	insert_edge(1, 3);
	insert_edge(1, 4);	insert_edge(2, 3); 	insert_edge(2, 5);
	insert_edge(3, 5); 	insert_edge(4, 5);

	printf("Topological Sort:\n");
	topological_sort();
}
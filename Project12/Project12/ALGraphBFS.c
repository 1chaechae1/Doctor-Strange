/*#include <stdio.h> 
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



int	visited[MAX_VTXS];
void reset_visited()
{
	int i;
	for (i = 0; i < vsize; i++)
		visited[i] = 0;
}


//---------------------------------------------------------------------------
// 원형큐
#define MAX_QUEUE_SIZE	100
#define Element	int
#define print_elem(e)	printf("[%d] ", e)

Element	data[MAX_QUEUE_SIZE];	// 요소의 배열
int	front;
int	rear;

void init_queue() { front = rear = 0; ; }
int is_empty() { return front == rear;; }
int is_full() { return (rear + 1) % MAX_QUEUE_SIZE == front; }
void enqueue(Element val)
{
	if (is_full())
		error("  큐 포화 에러");
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	data[rear] = val;
}
Element dequeue()
{
	if (is_empty())
		error("  큐 공백 에러");
	front = (front + 1) % MAX_QUEUE_SIZE;
	return data[front];
}

void BFS(int v)
{
	GNode* w;
	visited[v] = 1;

	printf("%c ", vdata[v]);
	init_queue();
	enqueue(v);
	while (!is_empty()) {
		v = dequeue();
		for (w = adj[v]; w != NULL; w = w->link) {
			if (!visited[w->id]) {
				visited[w->id] = 1;
				printf("%c ", vdata[w->id]);
				enqueue(w->id);
			}
		}
	}
}

void main()
{
	load_graph("graph.txt");
	reset_visited();
	printf("BFS ==> ");
	BFS(0);
	printf("\n");
}*/
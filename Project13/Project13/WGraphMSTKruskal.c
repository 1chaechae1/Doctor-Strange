/*#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS	256

void error(char str[])			// 오류 메시지 출력후 종료 함수: 공통
{
	printf("%s\n", str);
	exit(1);
}

typedef char VtxData;			// 그래프 정점에 저장할 데이터의 자료형 
int adj[MAX_VTXS][MAX_VTXS];	// 인접 행렬 
int vsize;						// 전체 정점의 개수 
VtxData vdata[MAX_VTXS];		// 정점에 저장할 데이터 배열 

int is_empty_graph() { return (vsize == 0); }
int is_full_graph() { return (vsize >= MAX_VTXS); }
void init_graph()
{
	int i, j;
	vsize = 0;
	for (i = 0; i < MAX_VTXS; i++)
		for (j = 0; j < MAX_VTXS; j++)
			adj[i][j] = 0;
}
void insert_vertex(VtxData name)
{
	if (is_full_graph())
		error("Error: 그래프 정점의 개수 초과\n");
	else
		vdata[vsize++] = name;
}
void insert_edge(int u, int v, int val)
{
	adj[u][v] = val;
}
void insert_edge2(int u, int v, int val)
{
	adj[u][v] = adj[v][u] = val;
}

//---------------------------------------------------------------------------

void print_graph(char* msg)
{
	int i, j;
	printf("%s", msg);
	printf("%d\n", vsize);
	for (i = 0; i < vsize; i++) {
		printf("%c  ", vdata[i]);
		for (j = 0; j < vsize; j++)
			printf(" %3d", adj[i][j]);
		printf("\n");
	}
}

//===========================================================================
// 가중치 그래프 파일 입력 / 화면 출력
//===========================================================================
#define INF 9999

void load_wgraph(char* filename)
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
				if (i != j && val == 0)
					adj[i][j] = INF;
				else adj[i][j] = val;
			}
		}
		fclose(fp);
	}
}
void print_wgraph(char* msg)
{
	int i, j, val;
	printf("%s%d\n", msg, vsize);
	for (i = 0; i < vsize; i++) {
		printf("%c  ", vdata[i]);
		for (j = 0; j < vsize; j++) {
			val = adj[i][j];
			if (i == j) printf("  0 ");
			else if (val >= INF) printf("  - ");
			else printf("%3d ", val);
		}
		printf("\n");
	}
}

int		parent[MAX_VTXS];		// 각 노드의 부모노드 인덱스	
int		set_size;				// 전체 집합의 개수	

void init_set(int nSets)
{
	int i;
	set_size = nSets;
	for (i = 0; i < nSets; i++)
		parent[i] = -1;			// 맨 처음에는 모든 정점이 각각 고유의 집합	
}
int find_set(int id)
{
	while (parent[id] >= 0) id = parent[id];
	return id;
}
void union_set(int s1, int s2)
{
	parent[s1] = s2;
	set_size--;
}

// 최소힙 관련 코드 
#define MAX_HEAP_NODE	200
typedef struct HeapNode {				// 힙에 저장할 항목의 자료형 
	int		key;
	int		v1;
	int		v2;
} HNode;
#define Key(n) (n.key)					// 힙 노드 n의 키값

HNode heap[MAX_HEAP_NODE];
int heap_size;

#define Parent(i) (heap[i/2])			// i의 부모 노드 
#define Left(i) (heap[i*2])				// i의 왼쪽 자식 노드 
#define Right(i) (heap[i*2+1])			// i의 오른쪽 자식 노드 

void init_heap() { heap_size = 0; }
int is_empty_heap() { return heap_size == 0; }
int is_full_heap() { return (heap_size == MAX_HEAP_NODE - 1); }
HNode find_heap() { return heap[1]; }


void insert_heap(HNode n)
{
	int i;
	if (is_full_heap()) return;
	i = ++(heap_size);
	while (i != 1 && Key(n) < Key(Parent(i))) {
		heap[i] = Parent(i);
		i /= 2;
	}
	heap[i] = n;
}

HNode delete_heap()
{
	HNode hroot, last;
	int parent = 1, child = 2;

	if (is_empty_heap())
		error("힙 트리 공백 에러");

	hroot = heap[1];
	last = heap[heap_size--];
	while (child <= heap_size) {
		if (child<heap_size && Key(Left(parent))>Key(Right(parent)))
			child++;
		if (Key(last) <= Key(heap[child]))
			break;
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = last;
	return hroot;
}

// kruskal의 최소 비용 신장 트리 프로그램 
void Kruskal()
{
	int i, j, edgeAccepted = 0, uset, vset;
	HNode e;

	init_heap();
	init_set(vsize);

	for (i = 0; i < vsize - 1; i++)
		for (j = i + 1; j < vsize; j++)
			if (adj[i][j] < INF) {
				e.key = adj[i][j];		// 힙 노드를 만들어 힙에 삽입 
				e.v1 = i;
				e.v2 = j;
				insert_heap(e);
			}

	while (edgeAccepted < vsize - 1) {
		e = delete_heap();
		uset = find_set(e.v1);
		vset = find_set(e.v2);

		if (uset != vset) {
			printf("간선 추가 : %c - %c (비용:%d)\n",
				vdata[e.v1], vdata[e.v2], e.key);
			union_set(uset, vset);
			edgeAccepted++;
		}
	}
}
void main()
{
	load_wgraph("graph.txt");
	printf("MST By Kruskal's Algorithm\n");
	Kruskal();
}*/
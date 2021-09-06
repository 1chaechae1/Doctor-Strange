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
int vsize;					// 전체 정점의 개수 
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
					insert_edge(i, j, val);
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


int	label[MAX_VTXS];
void labelDFS(int v, int color)
{
	int w;
	visited[v] = 1;
	label[v] = color;
	printf("%c ", vdata[v]);

	for (w = 0; w < vsize; w++)
		if (adj[v][w] != 0 && visited[w] == 0)
			labelDFS(w, color);
}
void find_connected_component()
{
	int i, count = 0;

	reset_visited();
	for (i = 0; i < vsize; i++) {
		if (visited[i] == 0)
			labelDFS(i, ++count);
	}
	printf("\n그래프 연결성분 개수 = %d\n", count);
	for (i = 0; i < vsize; i++)
		printf("%c=%d ", vdata[i], label[i]);
	printf("\n");
}

void main()
{
	int i;

	init_graph();
	for (i = 0; i < 5; i++)
		insert_vertex('A' + i);
	insert_edge2(1, 0, 1);
	insert_edge2(2, 0, 1);
	insert_edge2(3, 4, 1);

	print_graph("그래프(연결성분테스트)\n");
	find_connected_component();
}*/
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
void main()
{
	load_wgraph("wgraph.txt");
	print_wgraph("가중치그래프(wgraph.txt)\n");
}*/
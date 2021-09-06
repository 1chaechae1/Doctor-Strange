/*#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS	256

void error(char str[])			// ���� �޽��� ����� ���� �Լ�: ����
{
	printf("%s\n", str);
	exit(1);
}

typedef char VtxData;			// �׷��� ������ ������ �������� �ڷ��� 
int adj[MAX_VTXS][MAX_VTXS];	// ���� ��� 
int vsize;					// ��ü ������ ���� 
VtxData vdata[MAX_VTXS];		// ������ ������ ������ �迭 

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
		error("Error: �׷��� ������ ���� �ʰ�\n");
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
// ����ġ �׷��� ���� �Է� / ȭ�� ���
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

//===========================================================================
// ���� ���� ó��
//===========================================================================
int selected[MAX_VTXS];
int dist[MAX_VTXS];
int getMinVertex()
{
	int v, minv = 0, mindist = INF;
	for (v = 0; v < vsize; v++)
		if (!selected[v] && dist[v] < mindist) {
			mindist = dist[v];
			minv = v;
		}
	return minv;
}

// Prim�� �ּ� ��� ���� Ʈ�� ���α׷�
void Prim()
{
	int i, u, v;

	for (i = 0; i < vsize; i++) {
		dist[i] = INF;
		selected[i] = 0;
	}
	dist[0] = 0;

	for (i = 0; i < vsize; i++) {
		u = getMinVertex();
		selected[u] = 1;
		if (dist[u] == INF) return;
		printf("%c ", vdata[u]);

		for (v = 0; v < vsize; v++)
			if (adj[u][v] != INF)
				if (!selected[v] && adj[u][v] < dist[v])
					dist[v] = adj[u][v];
	}
	printf("\n");
}
void main()
{
	load_wgraph("graph.txt");
	printf("MST By Prim's Algorithm\n");
	Prim();
}*/
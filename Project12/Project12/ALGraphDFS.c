/*#include <stdio.h> 
#include <stdlib.h> 
#define MAX_VTXS	256

void error(char str[])			// ���� �޽��� ����� ���� �Լ�: ����
{
	printf("%s\n", str);
	exit(1);
}

typedef struct GraphNode {
	int id;					// ������ id 
	struct GraphNode* link;	// ���� ����� ������ 
} GNode;

typedef char VtxData;			// �׷��� ������ ������ �������� �ڷ��� 
GNode* adj[MAX_VTXS];		// �� ������ ���� ����Ʈ 
int		vsize;				// ������ ���� 
VtxData vdata[MAX_VTXS];		// ������ ������ ������ �迭 

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
		error("Error: �׷��� ������ ���� �ʰ�\n");
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

void DFS(int v) {
	GNode* p;
	visited[v] = 1;
	printf("%c ", vdata[v]);
	for (p = adj[v]; p != NULL; p = p->link)
		if (visited[p->id] == 0)
			DFS(p->id);
}

void main()
{
	load_graph("graph.txt");
	reset_visited();
	printf("DFS ==> ");
	DFS(0);
	printf("\n");
}*/
#include <stdio.h>
#define SWAP(x,y,t)	((t)=(x),(x)=(y),(y)=(t))

void printArray(int arr[], int n, char* str)
{
	int i;
	printf("%s = ", str);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}
void printStep(int arr[], int n, int val)
{
	int i;
	printf("  Step %2d = ", val);
	for (i = 0; i < n; i++) printf("%3d", arr[i]);
	printf("\n");
}

// ���� ���� �Լ� 
void selection_sort(int list[], int n)
{
	int i, j, least, tmp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)				// �ּҰ� Ž�� 
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], tmp);	// �迭 �׸� ��ȯ 
		printStep(list, n, i + 1);			// �߰� ���� ��¿� ���� 
	}
}

void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];			// ���ڵ��� ������ �̵�
		list[j + 1] = key;
		printStep(list, n, i);			// �߰� ���� ��¿� ����
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, bChanged, tmp;
	for (i = n - 1; i > 0; i--) {
		bChanged = 0;
		for (j = 0; j < i; j++)
			if (list[j] > list[j + 1]) {
				SWAP(list[j], list[j + 1], tmp);
				bChanged = 1;				// ��ȯ �߻�
			}
		if (!bChanged) break;				// ��ȯ�� ������ ����
		printStep(list, n, n - i);			// �߰� ���� ��¿� ����
	}
}


int ascend(int x, int y) { return y - x; }	// �������� ���Լ�
int descend(int x, int y) { return x - y; }	// �������� ���Լ�

// �Լ� �����͸� �Ű������� �޴� �������� �Լ�
void insertion_sort_fn(int list[], int n, int(*f)(int, int))
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && f(list[j], key) < 0; j--)
			list[j + 1] = list[j];			// ���ڵ��� ������ �̵�
		list[j + 1] = key;
		printStep(list, n, i);			// �߰� ���� ��¿� ����
	}
}


// gap ��ŭ ������ ��ҵ��� ���� ����. ������ ������ first���� last 
static void sortGapInsertion(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
// �� ���� �˰����� �̿��� int �迭�� ������������ �����ϴ� �Լ� 
void shell_sort(int list[], int n)
{
	int i, gap, count = 0;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;		// gap�� ¦���̸� 1�� ���� 
		for (i = 0; i < gap; i++)			// �κ� ����Ʈ�� ������ gap 
			sortGapInsertion(list, i, n - 1, gap);
		printStep(list, n, ++count);		// �߰� ���� ��¿� ���� 
	}
}


#define MAX_SIZE	1024
static void merge(int list[], int left, int mid, int right)
{
	int i, j, k = left, l;			// k�� ���ĵ� ����Ʈ�� ���� �ε���
	static int sorted[MAX_SIZE];		// ���յ� ����Ʈ ������ ���� �ӽù迭
										// ���� ���ĵ� list�� ����
	for (i = left, j = mid + 1; i <= mid && j <= right; )
		sorted[k++] = (list[i] <= list[j]) ? list[i++] : list[j++];
	// ���ʿ� ���� �ִ� ���ڵ��� �ϰ� ����
	if (i > mid)
		for (l = j; l <= right; l++, k++)
			sorted[k] = list[l];
	else
		for (l = i; l <= mid; l++, k++)
			sorted[k] = list[l];
	// �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �ٽ� ����
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
// ���� ���� �˰����� �̿��� int �迭�� ������������ �����ϴ� �Լ�
void merge_sort(int list[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;		// ����Ʈ�� �յ� ����
		merge_sort(list, left, mid);		// �κ� ����Ʈ ����
		merge_sort(list, mid + 1, right);	// �κ� ����Ʈ ����
		merge(list, left, mid, right);	// ����
	}
}

int partition(int list[], int left, int right)
{
	int tmp;
	int low = left + 1;
	int high = right;
	int pivot = list[left]; 		// �ǹ� ���� 
	while (low < high) {			// low�� high�� �������� �ʴ� �� �ݺ� 
		for (; low <= right && list[low] < pivot; low++);
		for (; high >= left && list[high] > pivot; high--);
		if (low < high)				// ���õ� �� ���ڵ� ��ȯ 
			SWAP(list[low], list[high], tmp);
	}
	SWAP(list[left], list[high], tmp);	// high�� �ǹ� �׸� ��ȯ 
	return high;
}

// �� ���� �˰����� �̿��� �迭�� left ~ right �׸���� ������������ �����ϴ� �Լ�
void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) {						// ���� ������ 2�� �̻��� ���
		q = partition(list, left, right);	// �¿�� ���� 
		quick_sort(list, left, q - 1);		// ���� �κи���Ʈ�� �� ����
		quick_sort(list, q + 1, right);	// ������ �κи���Ʈ�� �� ����
	}
}

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void* arg1, const void* arg2)
{
	if (*(double*)arg1 > *(double*)arg2) return 1;
	else if (*(double*)arg1 < *(double*)arg2) return -1;
	else return 0;
}

void main()
{
	int 	list[9] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
	printArray(list, 9, "Original ");	// ���� �� �迭 ��� 

	//selection_sort(list, 9); 			// ���� ���� ���� 
	//printArray(list, 9, "Selection");	// ���� �� �迭 ��� 

	//insertion_sort(list, 9); 			// ���� ���� ���� 
	//printArray(list, 9, "Insertion");	// ���� �� �迭 ��� 

	//bubble_sort(list, 9); 			// ���� ���� ���� 
	//printArray(list, 9, "Bubble   ");	// ���� �� �迭 ��� 

	//insertion_sort_fn(list, 9, descend); 	// �������� �������� �˰���
	//printArray(list, 9, "Insert-De");	// ���� �� �迭 ��� 


	//shell_sort(list, 9); 	// �������� �������� �˰���
	//printArray(list, 9, "ShellSort");	// ���� �� �迭 ��� 

	//merge_sort(list, 0, 8); 	// �������� �������� �˰���
	//printArray(list, 9, "MergeSort");	// ���� �� �迭 ��� 

	quick_sort(list, 0, 8); 	// �������� �������� �˰���
	printArray(list, 9, "QuickSort");	// ���� �� �迭 ��� 
}
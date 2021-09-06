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

// 선택 정렬 함수 
void selection_sort(int list[], int n)
{
	int i, j, least, tmp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++)				// 최소값 탐색 
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], tmp);	// 배열 항목 교환 
		printStep(list, n, i + 1);			// 중간 과정 출력용 문장 
	}
}

void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j];			// 레코드의 오른쪽 이동
		list[j + 1] = key;
		printStep(list, n, i);			// 중간 과정 출력용 문장
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
				bChanged = 1;				// 교환 발생
			}
		if (!bChanged) break;				// 교환이 없으면 종료
		printStep(list, n, n - i);			// 중간 과정 출력용 문장
	}
}


int ascend(int x, int y) { return y - x; }	// 오름차순 비교함수
int descend(int x, int y) { return x - y; }	// 내림차순 비교함수

// 함수 포인터를 매개변수로 받는 삽입정렬 함수
void insertion_sort_fn(int list[], int n, int(*f)(int, int))
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && f(list[j], key) < 0; j--)
			list[j + 1] = list[j];			// 레코드의 오른쪽 이동
		list[j + 1] = key;
		printStep(list, n, i);			// 중간 과정 출력용 문장
	}
}


// gap 만큼 떨어진 요소들을 삽입 정렬. 정렬의 범위는 first에서 last 
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
// 셸 정렬 알고리즘을 이용해 int 배열을 오름차순으로 정렬하는 함수 
void shell_sort(int list[], int n)
{
	int i, gap, count = 0;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;		// gap이 짝수이면 1을 더함 
		for (i = 0; i < gap; i++)			// 부분 리스트의 개수는 gap 
			sortGapInsertion(list, i, n - 1, gap);
		printStep(list, n, ++count);		// 중간 과정 출력용 문장 
	}
}


#define MAX_SIZE	1024
static void merge(int list[], int left, int mid, int right)
{
	int i, j, k = left, l;			// k는 정렬될 리스트에 대한 인덱스
	static int sorted[MAX_SIZE];		// 병합된 리스트 저장을 위한 임시배열
										// 분할 정렬된 list의 병합
	for (i = left, j = mid + 1; i <= mid && j <= right; )
		sorted[k++] = (list[i] <= list[j]) ? list[i++] : list[j++];
	// 한쪽에 남아 있는 레코드의 일괄 복사
	if (i > mid)
		for (l = j; l <= right; l++, k++)
			sorted[k] = list[l];
	else
		for (l = i; l <= mid; l++, k++)
			sorted[k] = list[l];
	// 배열 sorted[]의 리스트를 배열 list[]로 다시 복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
// 병합 정렬 알고리즘을 이용해 int 배열을 오름차순으로 정렬하는 함수
void merge_sort(int list[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;		// 리스트의 균등 분할
		merge_sort(list, left, mid);		// 부분 리스트 정렬
		merge_sort(list, mid + 1, right);	// 부분 리스트 정렬
		merge(list, left, mid, right);	// 병합
	}
}

int partition(int list[], int left, int right)
{
	int tmp;
	int low = left + 1;
	int high = right;
	int pivot = list[left]; 		// 피벗 설정 
	while (low < high) {			// low와 high가 역전되지 않는 한 반복 
		for (; low <= right && list[low] < pivot; low++);
		for (; high >= left && list[high] > pivot; high--);
		if (low < high)				// 선택된 두 레코드 교환 
			SWAP(list[low], list[high], tmp);
	}
	SWAP(list[left], list[high], tmp);	// high와 피벗 항목 교환 
	return high;
}

// 퀵 정렬 알고리즘을 이용해 배열의 left ~ right 항목들을 오름차순으로 정렬하는 함수
void quick_sort(int list[], int left, int right)
{
	int q;
	if (left < right) {						// 정렬 범위가 2개 이상인 경우
		q = partition(list, left, right);	// 좌우로 분할 
		quick_sort(list, left, q - 1);		// 왼쪽 부분리스트를 퀵 정렬
		quick_sort(list, q + 1, right);	// 오른쪽 부분리스트를 퀵 정렬
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
	printArray(list, 9, "Original ");	// 정렬 전 배열 출력 

	//selection_sort(list, 9); 			// 선택 정렬 실행 
	//printArray(list, 9, "Selection");	// 정렬 후 배열 출력 

	//insertion_sort(list, 9); 			// 선택 정렬 실행 
	//printArray(list, 9, "Insertion");	// 정렬 후 배열 출력 

	//bubble_sort(list, 9); 			// 선택 정렬 실행 
	//printArray(list, 9, "Bubble   ");	// 정렬 후 배열 출력 

	//insertion_sort_fn(list, 9, descend); 	// 내림차순 선택정렬 알고리즘
	//printArray(list, 9, "Insert-De");	// 정렬 후 배열 출력 


	//shell_sort(list, 9); 	// 내림차순 선택정렬 알고리즘
	//printArray(list, 9, "ShellSort");	// 정렬 후 배열 출력 

	//merge_sort(list, 0, 8); 	// 내림차순 선택정렬 알고리즘
	//printArray(list, 9, "MergeSort");	// 정렬 후 배열 출력 

	quick_sort(list, 0, 8); 	// 내림차순 선택정렬 알고리즘
	printArray(list, 9, "QuickSort");	// 정렬 후 배열 출력 
}
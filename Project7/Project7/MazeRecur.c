#include <stdio.h>
#define MAZE_SIZE 6
char map[MAZE_SIZE][MAZE_SIZE] = {
{ '1', '1', '1', '1', '1', '1' },
{ 'e', '0', '1', '0', '0', '1' },
{ '1', '0', '0', '0', '1', '1' },
{ '1', '0', '1', '0', '1', '1' },
{ '1', '0', '1', '0', '0', 'x' },
{ '1', '1', '1', '1', '1', '1' },
};
int xExit = 5, yExit = 4, done = 0;
int is_valid(int x, int y) {
	if (x < 0 || y < 0 || x >= MAZE_SIZE || y >= MAZE_SIZE) return 0;
	else return map[y][x] == '0' || map[y][x] == 'x';
}
void search_recur(int x, int y)
{
	if (done) return;
	printf("(%d,%d) ", x, y);
	if (x == xExit && y == yExit) {
		done = 1;
		return;
	}
	map[y][x] = '5';
	if (is_valid(x - 1, y)) search_recur(x - 1, y);
	if (is_valid(x + 1, y)) search_recur(x + 1, y);
	if (is_valid(x, y - 1)) search_recur(x, y - 1);
	if (is_valid(x, y + 1)) search_recur(x, y + 1);
}
// 순환적인 미로 탐색 주 함수
void main()
{
	search_recur(0, 1);
	if (done) printf("\n ==> 출구가 탐지되었습니다.\n");
	else printf("\n ==> 출구를 찾지 못했습니다.\n");
}
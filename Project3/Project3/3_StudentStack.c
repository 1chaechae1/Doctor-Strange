#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100			// 스택 요소 저장을 위한 배열의 크기
typedef struct Student {			// 스택에 저장할 요소의 자료형
	int id;							// 학번
	char name[32];					// 이름
	char dept[32];					// 소속 학과
} Student;							// 스택 요소 저장을 위한 배열의 크기
typedef Student Element;			// 스택 요소의 자료형 정의
Element data[MAX_STACK_SIZE];		// 실제 스택 요소의 배열
int top;							// 실제 스택의 top
									// 다음 함수들은 프로그램3.1에서와 동일함.

void error(char str[])
{
	printf("%s\n", str);
	exit(1);
}

// 스택의 주요 연산 : 공통
void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX_STACK_SIZE - 1; }
int size() { return top + 1; }

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

void print_stack(char msg[])
{
	int i;
	printf("%s[%2d]= ", msg, size());
	for (i = 0; i < size(); i++)
		printf("\n\t%-15d %-10s %-20s",
			data[i].id, data[i].name, data[i].dept);
	printf("\n");
}

Student get_student(int id, char name[], char dept[])
{
	Student s;
	s.id = id;
	strcpy(s.name, name);			// 문자열 복사. s.name = name은 오류
	strcpy(s.dept, dept);			// 문자열 복사. s.dept = dept는 오류
	return s;
}

void main()
{
	init_stack();
	push(get_student(2018130007, "홍길동", "컴퓨터공학과"));
	push(get_student(2018130100, "이순신", "기계공학과"));
	push(get_student(2018130135, "김연아", "체육과"));
	push(get_student(2018130135, "황희", "법학과"));
	print_stack("친구 4명 삽입 후");
	pop();
	print_stack("친구 1명 삭제 후");
}

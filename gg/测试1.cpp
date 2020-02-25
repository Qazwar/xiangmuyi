#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	//两个变量
	int a, b;

	//输入
	scanf("%d %d", &a, &b);

	if (b < 3)
		a++;
	else if (b < 2)
		a = a + 2;
	else
		a += 3;

	return 0;
}
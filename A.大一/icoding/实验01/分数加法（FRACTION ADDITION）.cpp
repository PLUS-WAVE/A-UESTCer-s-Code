//修改如下程序，使用户可以同时输入两个分数，中间用加号隔开：
//
//Enter two fractions separated by a plus sign : 5 / 6 + 3 / 4
//The sum is 38 / 24

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>;

int main() {
	int son1, mom1, son2, mom2;
	printf("Enter two fractions separated by a plus sign: ");
	scanf("%d/%d+%d/%d", &son1, &mom1, &son2, &mom2);
	int result_son, result_mom;
	result_son = son1 * mom2 + son2 * mom1;
	result_mom = mom1 * mom2;
	printf("The sum is %d/%d", result_son, result_mom);
	return 0;
}
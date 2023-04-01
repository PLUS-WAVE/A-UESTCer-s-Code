//编写⼀个程序，要求用户输出⼀个美元数量，然后显示出如何用最少20美元、10美元、5美元和1美元来付款。
//
//Enter a dollar amount : 93
//$20 bills : 4
//$10 bills : 1
//$5 bills : 0
//$1 bills : 3

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>;

int main() {
	int amount, bills20, bills10, bills5, bills1;
	printf("Enter a dollar amount: ");
	scanf("%d", &amount);
	bills20 = amount / 20;
	bills10 = amount % 20 / 10;
	bills5 = (amount - bills20 * 20 - bills10 * 10) / 5;
	bills1 = (amount - bills20 * 20 - bills10 * 10 - bills5 * 5) / 1;
	printf("$20 bills: %d\n$10 bills: %d\n$5 bills: %d\n$1 bills: %d\n", bills20, bills10, bills5, bills1);

	return 0;
}
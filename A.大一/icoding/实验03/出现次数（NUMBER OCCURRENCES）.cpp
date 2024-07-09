//修改如下程序，使其打印⼀份列表，显示出每个数字在数中出现的次数。
//
//输出范例：
//
//Enter a number : 41271092
//
//Digit :			0	1	2	3	4	5	6	7	8	9
//Occurrences :	1	2	2	0	1	0	0	1	0	1


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int main() {
	int digit, digit_count[10] = { 0 };
	long num;
	printf("Enter a number: ");
	scanf("%ld", &num);
	if (num == 0) {
		digit_count[0] = 1;
	}
	while (num != 0) {
		digit = num % 10;
		digit_count[digit]++;
		num = num / 10;
	}
	printf("\nDigit:      ");
	for (int i = 0; i < 10; i++) {
		printf("%d", i);
	}
	printf("\nOccurrences:");
	for (int i = 0; i < 10; i++) {
		printf("%d", digit_count[i]);
	}
	return 0;
}
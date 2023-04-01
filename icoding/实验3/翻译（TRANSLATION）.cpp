//编写程序可以把字母格式的电话号码翻译成数值格式：
//
//Enter phone number : CALLATT
//
//2255288
//
//如果没有电话在身边, 参考这里给出的字母在键盘上的对应关系：（2 = ABC，3 = DEF，4 = GHI，5 = JKL，6 = MNO，7 = PQRS，8 = TUV，9 = WXYZ）原始电话号码中的非字母字符（例如数字或标点符号）保持不变：
//
//Enter phone number : 1 - 800 - COL - LECT1 - 800 - 265 - 5328
//
//可以假设任何用户输入的字母都是大写字母。
//
//输出范例：
//
//Enter phone number : 1 - DCKS - A2D - OLED
//
//1 - 3257 - 223 - 6533


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

int main() {
	char num[50];
	printf("Enter phone number: ");
	scanf("%s", num);
	for (int i = 0; i < 50; i++) {
		if (num[i] == '-') {
		}
		else
		{
			if (num[i] >= 65 && num[i] <= 67) {
				num[i] = '2';
			}
			else if (num[i] >= 68 && num[i] <= 70) {
				num[i] = '3';
			}
			else if (num[i] >= 71 && num[i] <= 73) {
				num[i] = '4';
			}
			else if (num[i] >= 74 && num[i] <= 76) {
				num[i] = '5';
			}
			else if (num[i] >= 77 && num[i] <= 79) {
				num[i] = '6';
			}
			else if (num[i] >= 80 && num[i] <= 83) {
				num[i] = '7';
			}
			else if (num[i] >= 84 && num[i] <= 86) {
				num[i] = '8';
			}
			else if (num[i] >= 87 && num[i] <= 90) {
				num[i] = '9';
			}
		}

	}

	printf("%s", num);


	return 0;
}
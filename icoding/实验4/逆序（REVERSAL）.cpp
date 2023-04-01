//编写程序读一条消息，然后逆序打印出这条消息。
//
//输出范例：
//
//
//Enter a message : Don't get mad, get even.
//Reversal is : .neve teg, dam teg t'noD
//
//
//Enter a message : Hello, world!
//Reversal is : !dlrow, olleH
//
//
//提示：一次读取消息中的一个字符（用getchar函数），并且把这些字符存储在数组中，当数组写满或者读到字符 '\n' 时停止读入。


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>;

int main() {
	printf("Enter a message: ");
	char s[100] = { 0 };
	for (int i = 0; i < 100; i++) {
		s[i] = getchar();
		if (s[i] == '\n') {
			s[i] = 0;
			break;
		}
	}
	//printf("%s", s);
	int count = 0;
	while (s[count] != 0)
	{
		count++;
	}
	char Re[100] = { 0 };
	for (int i = 0; i < 100; i++) {
		Re[i] = s[count - 1];
		count--;
		if (count == 0) {
			break;
		}
	}
	printf("%s", Re);
	return 0;
}
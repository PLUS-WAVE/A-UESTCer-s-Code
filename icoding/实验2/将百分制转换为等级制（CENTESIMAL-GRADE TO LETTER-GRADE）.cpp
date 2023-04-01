//利用switch语句编写一个程序，把用数字表示的成绩转化为字母表示的等级。
//
//使用下面的等级评定规则：A为90~100，B为80~89，C为70~79，D为60~69，F为0~59。如果成绩大于100或小于0显示出错信息。
//
//输出范例：
//Enter numerical grade : 84
//Letter grade : B
//
//Enter numerical grade : -1
//Error, grade must be between 0 and 100.
//
//提示：把成绩拆分成 2 个数字，然后使用 switch 语句判定十位上的数字。

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>


int main() {
	int grade;
	printf("Enter numerical grade: ");
	scanf("%d", &grade);
	if (grade <= 100) {
		if (grade >= 0) {
			if (grade <= 59) {
				printf("Letter grade: F");
			}
			else if (grade <= 69) {
				printf("Letter grade: D");
			}
			else if (grade <= 79) {
				printf("Letter grade: C");
			}
			else if (grade <= 89) {
				printf("Letter grade: B");
			}
			else {
				printf("Letter grade: A");
			}
		}
		else {
			printf("Error, grade must be between 0 and 100.");
		}
	}
	else
	{
		printf("Error, grade must be between 0 and 100.");
	}
	return 0;
}
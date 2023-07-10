//编写一个程序，以月 / 日 / 年（即 mm / dd / yy）的格式接受用户录入的日期信息，并以年月日（即yyyymmdd）的格式将其显示出来。
//
//Enter a date(mm / dd / yyyy) : 2 / 17 / 2011
//You entered the date 20110217

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>;

int main() {
	int mm, dd, yyyy;
	printf("Enter a date (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &mm, &dd, &yyyy);
	int date = yyyy * 10000 + mm * 100 + dd;
	printf("%d", date);
	return 0;
}
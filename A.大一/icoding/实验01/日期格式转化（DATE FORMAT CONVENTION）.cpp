//��дһ���������� / �� / �꣨�� mm / dd / yy���ĸ�ʽ�����û�¼���������Ϣ�����������գ���yyyymmdd���ĸ�ʽ������ʾ������
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
//��дһ������Ҫ���û����� 24 Сʱ�Ƶ�ʱ�䣬����ת��Ϊ 12 Сʱ�Ƶĸ�ʽ��
//
//Enter a 24 - hour time : 21 : 11
//Equivalent 12 - hour time : 9 : 11 PM
//
//Enter a 24 - hour time : 0 : 01
//Equivalent 12 - hour time : 12 : 01 AM
//
//ע�⣬��Ҫ��12 : 00��ʾΪ0 : 00��

#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>;

int main() {
	int h24, m24;
	printf("Enter a 24-hour time: ");
	scanf("%d:%d", &h24, &m24);
	if (h24 < 12) {
		if (h24 >= 1)
			printf("Equivalent 12-hour time: %d:%.2d AM", h24, m24);
		else
		{
			printf("Equivalent 12-hour time: 12:%.2d AM", m24);
		}
	}
	else if (h24 == 12) {
		printf("Equivalent 12-hour time: 12:%.2d PM", m24);
	}
	else {
		int h12 = h24 - 12;
		printf("Equivalent 12-hour time: %d:%.2d PM", h12, m24);
	}
	return 0;
}
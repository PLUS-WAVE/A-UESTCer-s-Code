//����switch����дһ�����򣬰������ֱ�ʾ�ĳɼ�ת��Ϊ��ĸ��ʾ�ĵȼ���
//
//ʹ������ĵȼ���������AΪ90~100��BΪ80~89��CΪ70~79��DΪ60~69��FΪ0~59������ɼ�����100��С��0��ʾ������Ϣ��
//
//���������
//Enter numerical grade : 84
//Letter grade : B
//
//Enter numerical grade : -1
//Error, grade must be between 0 and 100.
//
//��ʾ���ѳɼ���ֳ� 2 �����֣�Ȼ��ʹ�� switch ����ж�ʮλ�ϵ����֡�

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
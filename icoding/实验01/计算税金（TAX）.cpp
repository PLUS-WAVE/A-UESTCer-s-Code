//��дһ������Ҫ���û�����һ����Ԫ������Ȼ����ʾ������ 5 % ˰�ʺ����Ӧ��
//
//Enter an amount : 100.00
//with tax added : $105.00
//
//����Ľ��Ϊ���� 0 ����λ����������


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>;

int main() {
	float amount, taxadd;
	printf("Enter an amount: ");
	scanf("%f", &amount);
	taxadd = amount * (1 + 0.05);
	printf("with tax added: $%5.2f", taxadd);
	return 0;
}
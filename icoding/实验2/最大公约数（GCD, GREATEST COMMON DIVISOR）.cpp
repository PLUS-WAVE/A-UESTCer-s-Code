//��д����Ҫ���û���������������Ȼ��������������������Լ����GCD, Greatest Common Divisor����
//
//���������
//
//
//Enter two integers : 12 28
//Greatest common divisor : 4
//
//
//Enter two integers��1 9
//Greatest common divisor��1
//
//
//��ʾ�������Լ���ľ����㷨 Euclid �㷨���£�
//�ֱ��ñ��� m �� n �洢������������� n Ϊ 0����ôֹͣ������m �е�ֵ�� GCD ��������� m ���� n ���������� n ���浽 m �У������������浽 n �У��ظ�����������ÿ�ζ����ж�n�Ƿ�Ϊ 0 ��


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<math.h>


int main() {
	int m, n;
	scanf("%d %d", &m, &n);
	while (n != 0)
	{
		int t = m % n;
		m = n;
		n = t;
	}
	printf("%d", m);
	return 0;
}
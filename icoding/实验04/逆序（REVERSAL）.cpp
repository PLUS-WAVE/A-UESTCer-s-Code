//��д�����һ����Ϣ��Ȼ�������ӡ��������Ϣ��
//
//���������
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
//��ʾ��һ�ζ�ȡ��Ϣ�е�һ���ַ�����getchar�����������Ұ���Щ�ַ��洢�������У�������д�����߶����ַ� '\n' ʱֹͣ���롣


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
//��д��������һ�ֹᴩ10��10�ַ����飨��ʼʱȫΪ�ַ�'.'���ġ�����������������������ش�һ��Ԫ�ء��ߵ�����һ��Ԫ�أ�ÿ�ζ����ϡ����¡�����������ƶ�һ��Ԫ��λ�á��ѷ��ʹ���Ԫ�ذ�����˳������ĸA��Z���б�ǡ�
//
//������һ�����ʾ����
//
//A	.	.	.	.	.	.	.	.	.
//B	C	D	.	.	.	.	.	.	.
//.	F	E	.	.	.	.	.	.	.
//H	G	.	.	.	.	.	.	.	.
//I	.	.	.	.	.	.	.	.	.
//J	.	.	.	.	.	.	.	Z	.
//K	.	.	R	S	T	U	V	Y	.
//L	M	P	Q	.	.	.	W	X	.
//.	N	O	.	.	.	.	.	.	.
//����srand������rand���������������Ȼ��鿴��������4������������һ����4�ֿ��ܵ�ֵ��0��1��2��3����ָʾ��һ���ƶ���4�ֿ��ܷ�����ִ���ƶ�֮ǰ����Ҫ����������ݣ�һ�ǲ����ߵ��������棬���ǲ����ߵ�������ĸ��ǵ�λ�á�ֻҪһ�����������㣬�͵ó��Ի�һ�������ƶ������4�����򶼶�ס�ˣ�����ͱ�����ֹ�ˡ���������ǰ������һ��ʾ��:
//
//A	B	G	H	I	.	.	.	.	.
//.	C	F	O	J	K	.	.	.	.
//.	D	E	N	M	L	.	.	.	.
//.	.	.	.	.	.	.	.	.	.
//.	.	.	.	.	.	.	.	.	.
//.	.	.	.	.	.	.	.	.	.
//.	.	.	.	.	.	.	.	.	.
//.	.	.	.	.	.	.	.	.	.
//.	.	.	.	.	.	.	.	.	.
//��ΪY��4�����򶼶�ס�ˣ�����û�еط����Է�����һ����Z�ˡ�



#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	char ch = 'A';
	char a[11][11];
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			a[i][j] = '.';
		}
	}

	srand((unsigned)time(NULL));
	a[1][1] = 'A';
	int step = rand() % 4 + 1;
	int row = 1, col = 1, flag = 0;
	for (int i = 1; i < 26; i++) {
		while (flag != 1) {
			if (a[row][col + 1] != '.' && a[row + 1][col] != '.' && a[row][col - 1] != '.' && a[row - 1][col] != '.') {
				flag = 1;
				break;
			}
			switch (step)
			{
			case 1:if (a[row][col + 1] != '.') {
				step = rand() % 4 + 1;
				break;
			}
				  else
			{
				flag = 1;
				a[row][col + 1] = ch + i;
				col++;
			}

				  break;
			case 2:if (a[row + 1][col] != '.') {
				step = rand() % 4 + 1;
				break;
			}
				  else
			{
				flag = 1;
				a[row + 1][col] = ch + i;
				row++;
			}

				  break;
			case 3:if (a[row][col - 1] != '.' || col - 1 < 0) {
				step = rand() % 4 + 1;
				break;
			}
				  else
			{
				flag = 1;
				a[row][col - 1] = ch + i;
				col--;
			}
				  break;
			case 4:if (a[row - 1][col] != '.' || row - 1 < 0) {
				step = rand() % 4 + 1;
				break;
			}
				  else
			{
				flag = 1;
				a[row - 1][col] = ch + i;
				row--;
			}
				  break;
			}
			/*for (int i = 1; i < 11; i++) {
				for (int j = 1; j < 11; j++) {
					printf("%c", a[i][j]);
				}
				printf("\n");
			}*/
		}
		flag = 0;
		step = rand() % 4 + 1;

	}

	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			printf("%c", a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
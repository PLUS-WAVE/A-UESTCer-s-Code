//编写程序，生成一种贯穿10×10字符数组（初始时全为字符'.'）的“随机步法”。程序必须随机地从一个元素“走到”另一个元素，每次都向上、向下、向左或向右移动一个元素位置。已访问过的元素按访问顺序用字母A到Z进行标记。
//
//下面是一个输出示例：
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
//利用srand函数和rand函数产生随机数，然后查看次数除以4的余数。余数一共有4种可能的值（0、1、2和3），指示下一次移动的4种可能方向。在执行移动之前，需要检查两项内容：一是不能走到数组外面，二是不能走到已有字母标记的位置。只要一个条件不满足，就得尝试换一个方向移动。如果4个方向都堵住了，程序就必须终止了。下面是提前结束的一个示例:
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
//因为Y的4个方向都堵住了，所以没有地方可以放置下一步的Z了。



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
//编写程序显示单月的日历。用户指定这个月的天数和该月起始日是星期几。
//
//输出范例：
//
//Enter number of days in month : 31
//
//Enter starting day of the week(1 = Sun, 7 = Sat) : 3
//
//日 一	二	三	四	五	六
//		1	2	3	4	5
//6	 7	8	9	10	11	12
//13 14	15	16	17	18	19
//20 21	22	23	24	25	26
//27 28	29	30	31


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<math.h>


int main(void) {
	int days, starting;
	printf("Enter number of days in month: ");
	scanf("%d", &days);
	printf("\n");
	printf("Enter starting day of the week(1=Sun, 7=Sat): ");
	scanf("%d", &starting);
	printf("\n");
	printf("日      一      二      三      四      五      六\n");

	for (int j = 2; j <= starting; j++) {
		printf("\t");
	}
	int x;
	for (x = 1; x + starting < 9; x++) {
		printf("%d\t", x);
	}
	printf("\n");
	printf(" ");
	int d = x;
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 8; j++) {
			printf("%d\t", d);
			d++;
			if (d > days) {
				break;
			}
		}
		printf("\n");
		printf(" ");
	}
	return 0;
}
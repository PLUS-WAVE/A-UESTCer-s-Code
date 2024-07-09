//编写程序，提示用户输入一个数 n，然后显示出 1~n 的所有偶数的平方值。
//
//输出范例：
//Enter a number : 100
//4
//16
//36
//64
//100
//
//Enter a number : 50
//4
//16
//36


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<math.h>


int main(void) {
    int n, Square = 0;
    scanf("%d", &n);
    for (int i = 1; Square < n; i++) {
        if (i % 2 == 0) {
            printf("%d\n", i * i);
            Square = i * i;
        }
    }
    return 0;
}
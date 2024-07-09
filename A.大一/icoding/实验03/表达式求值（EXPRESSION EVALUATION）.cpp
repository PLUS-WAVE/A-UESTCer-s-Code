//编写程序对表达式求值。
//
//Enter an expression : 1 + 2.5 * 3
//Value of expression : 10.5
//
//
//表达式中的操作数是浮点数，运算符是 + 、 - 、 * 和 / 。表达式从左向右求值（所有运算符的优先级都⼀样）。
//
//
//输出范例：
//
//
//Enter an expression : 2 + 3 * 4 - 5 / 2
//Value of expression : 7.5


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    printf("Enter an expression: ");
    double sum = 0, num = 0;
    char ch;
    scanf("%lf", &sum);

    while ((ch = getchar()) != '\n') {
        scanf("%lf", &num);
        switch (ch) {
        case '+':
            sum = sum + num;
            break;
        case '-':
            sum = sum - num;
            break;
        case '*':
            sum = sum * num;
            break;
        case '/':
            sum = sum / num;
            break;
        }
    }
    printf("Value of expression : %lf", sum);
    return 0;
}
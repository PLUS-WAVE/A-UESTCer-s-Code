//修改如下程序，使它存储字符而不是整数。
//
//增加 main 函数，用来要求用户输入一串圆括号或花括号，然后指出它们之间的嵌套是否正确。
//
//输出范例：
//
//
//Enter parentheses and /or braces: ()({})({})
//Parentheses / braces are nested properly
//
//
//Enter parentheses and /or braces : ((}
//Parentheses / braces are NOT nested properly


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdbool.h>   /* C99 only */
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

/* external variables */
char contents[STACK_SIZE];
int top = 0;


void stack_overflow(void)
{
    printf("Stack overflow\n");
    exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
    printf("Stack underflow\n");
    exit(EXIT_FAILURE);
}


void make_empty(void)
{
    top = 0;
}

bool is_empty(void)
{
    return top == 0;
}

bool is_full(void)
{
    return top == STACK_SIZE;
}

void push(char ch)
{
    if (is_full())
        stack_overflow();
    else
        contents[top++] = ch;
}

char pop(void)
{
    if (is_empty())
        stack_underflow();
    else
        return contents[--top];

    return '\0'; /* prevents compiler warning due to stack_underflow() call */
}

char reverse(char c) {
    if (c == '}') {
        return '{';
    }
    if (c == ']') {
        return '[';
    }
    return '(';
}

int main(void)
{
    int flag = 0;
    printf("Enter parentheses and/or braces: ");
    char braces[100] = { '/0' };
    scanf("%s", braces);
    for (int i = 0; i < 100; i++) {
        if (braces[i] == 0) {
            break;
        }
        if (braces[i] == '(' || braces[i] == '[' || braces[i] == '{') {
            push(braces[i]);
        }
        else {
            if (!is_empty() && reverse(braces[i]) == contents[top - 1]) {
                pop();
            }
            else {
                flag = 0;
            }
        }

    }
    if (top == 0) {
        flag = 1;
    }
    if (flag == 0) {
        printf("Parentheses/braces are NOT nested properly");
    }
    else
    {
        printf("Parentheses/braces are nested properly");
    }
    return 0;
}
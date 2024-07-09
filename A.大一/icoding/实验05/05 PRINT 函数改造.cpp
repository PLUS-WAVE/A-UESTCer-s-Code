//修改inventory.c(点击下载)程序，使 inventory 和 num_parts 为 main 函数的局部变量。
//
//本小题只需完成 print 函数的改造即可，相关结构及函数声明如下：
//
//#define NAME_LEN 25
//
//#define MAX_PARTS 100
//
//struct part {
//	int number;
//	char name[NAME_LEN + 1];
//	int on_hand;
//};
//
//
//int read_line(char str[], int n);
//int find_part(int number, const struct part inv[], int np);
//void insert(struct part inv[], int* np);
//void search(const struct part inv[], int np);
//void update(struct part inv[], int np);
//void print(const struct part inv[], int np);
//
//该部分声明已包含在 “lab51.h”中。


#include <stdio.h>
#include <stdlib.h>
#include "lab51.h" // 请不要删除本行头文件，否则检查不通过

void print(const struct part inv[], int np)
{
    int i;

    printf("Part Number   Part Name                  "
        "Quantity on Hand\n");
    for (i = 0; i < np; i++)
        printf("%7d       %-25s%11d\n", inv[i].number,
            inv[i].name, inv[i].on_hand);
}
//�޸�inventory.c(�������)����ʹ inventory �� num_parts Ϊ main �����ľֲ�������
//
//��С��ֻ����� update �����ĸ��켴�ɣ���ؽṹ�������������£�
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
//�ò��������Ѱ����� ��lab51.h���С�


#include <stdio.h>
#include <stdlib.h>
#include "lab51.h" // �벻Ҫɾ������ͷ�ļ��������鲻ͨ��

void update(struct part inv[], int np)
{
    int i, number, change;

    printf("Enter part number: ");
    scanf("%d", &number);
    i = find_part(number, inv, np);
    if (i >= 0) {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        inv[i].on_hand += change;
    }
    else
        printf("Part not found.\n");
}
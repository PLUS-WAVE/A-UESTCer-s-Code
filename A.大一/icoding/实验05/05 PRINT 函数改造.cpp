//�޸�inventory.c(�������)����ʹ inventory �� num_parts Ϊ main �����ľֲ�������
//
//��С��ֻ����� print �����ĸ��켴�ɣ���ؽṹ�������������£�
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

void print(const struct part inv[], int np)
{
    int i;

    printf("Part Number   Part Name                  "
        "Quantity on Hand\n");
    for (i = 0; i < np; i++)
        printf("%7d       %-25s%11d\n", inv[i].number,
            inv[i].name, inv[i].on_hand);
}
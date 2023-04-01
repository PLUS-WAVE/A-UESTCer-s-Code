//�޸�inventory.c(�������)����ʹ inventory �� num_parts Ϊ main �����ľֲ�������
//
//��С��ֻ����� insert �����ĸ��켴�ɣ���ؽṹ�������������£�
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
void insert(struct part inv[], int* np)
{
    int part_number;

    if (*np == MAX_PARTS) {
        printf("Database is full; can't add more parts.\n");
        return;
    }

    printf("Enter part number: ");
    scanf("%d", &part_number);
    if (find_part(part_number, inv, *np) >= 0) {
        printf("Part already exists.\n");
        return;
    }

    inv[*np].number = part_number;
    printf("Enter part name: ");
    read_line(inv[*np].name, NAME_LEN);
    printf("Enter quantity on hand: ");
    scanf("%d", &inv[*np].on_hand);
    (*np)++;
}
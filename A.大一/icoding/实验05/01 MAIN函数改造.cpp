//�޸�inventory.c(�������)����ʹ inventory �� num_parts Ϊ main �����ľֲ�������
//
//��С��ֻ����� main �����ĸ��켴�ɣ���ؽṹ�������������£�
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

int main()
{
    char code;
    int num_parts = 0;
    struct part inventory[MAX_PARTS];
    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')   /* skips to end of line */
            ;
        switch (code) {
        case 'i': insert(num_parts, inventory);
            break;
        case 's': search(num_parts, inventory);
            break;
        case 'u': update(num_parts, inventory);
            break;
        case 'p': print(num_parts, inventory);
            break;
        case 'q': return 0;
        default:  printf("Illegal code\n");
        }
        printf("\n");
    }
}
//��д�����ҳ�һ�鵥���С���С�����ʺ͡���󡱵��ʡ�
//
//�û����뵥�ʺ󣬳�������ֵ�˳�����������ǰ��������ĵ��ʡ�
//
//���û�����4����ĸ�ĵ���ʱ������ֹͣ���롣�������е��ʶ�������20����ĸ��
//
//�������1��
//Enter word : dog
//Enter word : zebra
//Enter word : rabbit
//Enter word : catfish
//Enter word : walrus
//Enter word : cat
//Enter word : fish
//
//
//Smallest word : cat
//Largest word zebra
//
//
//�������2��
//
//
//Enter word : computer
//Enter word : ink
//Enter word : light
//Enter word : bookrack
//Enter word : book
//
//
//Smallest word : book
//Largest word : light


#include <stdio.h>
#include<string.h>
#define WIDTH 100
#define LENGTH 20
int main()
{
    char a[WIDTH][LENGTH + 1], str[100] = { "\0" };
    int i, j, k, m;
    for (i = 0; j != 4; ++i)
    {
        printf("Enter word:");
        scanf("%s", &a[i]);
        j = strlen(a[i]);
    }
    for (j = 0; j < i; ++j)
    {
        for (k = 0; k < i - j; ++k)
        {
            if (strcmp(a[k], a[k + 1]) > 0)
            {
                strcpy(str, a[k]);

                strcpy(a[k], a[k + 1]);

                strcpy(a[k + 1], str);
            }
        }
    }
    printf("Smallest word:%s", a[1]);
    printf("Largest word:%s", a[i]);
    return 0;
}
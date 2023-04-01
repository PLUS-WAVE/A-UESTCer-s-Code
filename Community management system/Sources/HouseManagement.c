#define _CRT_SECURE_NO_WARNINGS 1
#include"HouseManagement.h"
#include"VIP.h"
#include"Screen.h"
void HouseManagement(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
    int n;
    start_H();
    _getch();
    menu_H();
    while (1)
    {
        printf("\t\t\t\t����ѡ��(1~7): ");
        scanf("%d", &n);
        if (n <= 0 || n >= 8)
        {
            printf("\t\t\t\t����������,������ѡ��!\n");
        }

        switch (n)
        {
        case 1:
            input_H();
            break;
        case 2:
            view_H();
            break;
        case 3:
            search_H();
            break;
        case 4:
            del_H();
            break;
        case 5:
            add_H();
            break;
        case 6:
            modify_H();
            break;
        case 7:
            menuScreen_M(h, p_head, hs, H);
        default:
            break;
        }
        printf("\n");
        printf("\t\t\t\t�����������\n");
        _getch();
        system("cls");
        menu_H();
    }
}
void start_H() //��ʼ����
{
    system("cls");
    system("color 3F");
    printf("\n\n\n\n\n\n");
    printf("\t\t********************************************************************************\n");
    printf("\n");
    printf("\t\t************************��ӭʹ�����ǵķ������۹���ϵͳ**************************");
    printf("\n\n");
    printf("\t\t********************************************************************************\n\n\n\n\n");
    printf("\t\t\t\t\t      ������: ����ΰ\n");
    printf("\t\t\t\t\t      ����ʱ��: 2022��11��\n\n\n\n");
    printf("\t\t\t\t\t      ***�����������***\n");
}
void menu_H() //�˵�����
{
    system("cls");
    system("color 3F");
    printf("\n\n");
    printf("\t\t\t\t��������������������ϵͳ����������������\n\n");
    printf("\t\t\t\t\t************************\n");
    printf("\t\t\t\t\t********���ݲ˵�********\n");
    printf("\t\t\t\t\t************************\n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  �½�����(����ʼ��)      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  ��ʾ����      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  ���ҷ���      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  ɾ������      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  ��ӷ���      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t6  �޸ķ���      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t7  �˳�      \n\n");
    printf("\t\t\t\tע�⣺\n");
    printf("\t\t\t\t�½�����ѡ�����Ḳ��ԭ����Ϣ��\n\n");
}
void input_H() {          //�½�����(����ʼ��)

    int amount;
    system("cls");
    do {
        printf("\n��Ҫ¼��ķ��ݸ���(1����100): ");
        scanf("%d", &amount);
        if (amount < 1 || amount>100)
        {
            printf("\n������1����100��������\n");
        }
        else
        {
            break;
        }
    } while (1);

    for (int i = 0; i < amount; i++)
    {
        do {
            int flag = 1;
            printf("\n�����뷿������(Apartment, CommonHouse, Villa): ");
            scanf("%s", &house[i].type);
            if (strcmp(house[i].type, "Apartment") != 0)
            {
                flag = 0;
            }
            else
            {
                break;
            }
            if (strcmp(house[i].type, "CommonHouse") != 0)
            {
                flag = 0;
            }
            else
            {
                break;
            }
            if (strcmp(house[i].type, "Villa") != 0)
            {
                flag = 0;
            }
            else
            {
                break;
            }
            if (!flag) {
                printf("\n�����롰Apartment, CommonHouse, Villa���е�һ��");
            }
        } while (1);
        printf("\n�����뷿�ݱ��: ");
        scanf("%s", &house[i].number);
        printf("\n�������Ƿ��۳�(yes/no): ");
        scanf("%s", &house[i].sold);
        printf("\n�����������۸�(��Ԫ): ");
        scanf("%d", &house[i].price);
        printf("\n�����뷿�ݹ���(����): ");
        scanf("%s", &house[i].BelongTo);
    }

    FILE* fp1, * fp2, * fp3;

    if ((fp1 = fopen(File_H1, "w+")) == NULL)   //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }
    if ((fp2 = fopen(File_H2, "w+")) == NULL) //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }
    if ((fp3 = fopen(File_H3, "w+")) == NULL)       //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }

    for (int i = 0; i < amount; i++) /*���ڴ��з��ݵ���Ϣ����������ļ���ȥ*/
    {
        if (strcmp(house[i].type, "Apartment") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp1) != 1) 
                printf("�ļ���д����\n");

        }
        else if (strcmp(house[i].type, "CommonHouse") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp2) != 1)
                printf("�ļ���д����\n");

        }
        else
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp3) != 1)
                printf("�ļ���д����\n");

        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    printf("\n�������!\n");
}
void save_H(int a) {  //a�Ƿ�������
    FILE* fp1, * fp2, * fp3;

    if ((fp1 = fopen(File_H1, "r+")) == NULL)   //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }
    if ((fp2 = fopen(File_H2, "r+")) == NULL) //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }
    if ((fp3 = fopen(File_H3, "r+")) == NULL)       //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }

    for (int i = 0; i < a; i++) /*���ڴ��з��ݵ���Ϣ����������ļ���ȥ*/
    {
        if (strcmp(house[i].type, "Apartment") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp1) != 1) 
                printf("�ļ���д����\n");

        }
        else if (strcmp(house[i].type, "CommonHouse") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp2) != 1)
                printf("�ļ���д����\n");

        }
        else
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp3) != 1)
                printf("�ļ���д����\n");

        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
}
int read_H(int type) {
    FILE* fp = NULL;
    int i = 0;
    if (type == 1) {
        if ((fp = fopen(File_H1, "r")) == NULL)
        {
            printf("�Ҳ����ļ�\n");
            exit(0);
        }
        else
        {
            while (feof(fp) == 0)  //������ϵ��ļ�������
            {
                fread(&house[i], sizeof(struct House), 1, fp); //��ȡ
                i++;
            }
        }
    }
    if (type == 2) {
        if ((fp = fopen(File_H2, "r")) == NULL)
        {
            printf("�Ҳ����ļ�\n");
            exit(0);
        }
        else
        {
            while (feof(fp) == 0)  //������ϵ��ļ�������
            {
                fread(&house[i], sizeof(struct House), 1, fp); //��ȡ
                i++;
            }
        }
    }
    if (type == 3) {
        if ((fp = fopen(File_H3, "r")) == NULL)
        {
            printf("�Ҳ����ļ�\n");
            exit(0);
        }
        else
        {
            while (feof(fp) == 0)  //������ϵ��ļ�������
            {
                fread(&house[i], sizeof(struct House), 1, fp); //��ȡ
                i++;
            }
        }
    }
    fclose(fp);
    return i - 1;//���ظ��෿�ݸ���
}
void search_H() {
    int t;
    system("cls");//����
    do
    {
        printf("\n��1 ��ѯ\t��2 �����˵�\n\n");
        scanf("%d", &t);
        if (t >= 1 && t <= 2)
        {
            break;
        }
        else
        {
            printf("�������");
        }
    } while (1);
    while (1)
    {
        switch (t)
        {
        case 1:
            printf("\n���ڲ�ѯ...\n\n");
            SreachByNum_H();
            
        case 2:
            return;
            break;
        default:
            break;
        }
    }
}
void SreachByNum_H() {
    char Housetype[20];
    int type;
    printf("\n������Ҫ��ѯ�ķ�������(Apartment, CommonHouse, Villa): ");
    scanf("%s", &Housetype);
    if (strcmp(Housetype, "Apartment") == 0) {
        type = 1;
    }
    else if (strcmp(Housetype, "CommonHouse") == 0) {
        type = 2;
    }
    else if (strcmp(Housetype, "Villa") == 0) {
        type = 3;
    }
    else {
        printf("��������ȷ�ķ�������\n\n");
        SreachByNum_H();
    }
    int amount = read_H(type);
    printf("������Ҫ���ҵķ��ݱ��: ");
    char number[10];
    int flag = 0;
    scanf("%s", &number);
    for (int i = 0; i < amount; i++) {
        if (!strcmp(number, house[i].number)) {
            printf("\n�������ͣ�%s\n���ݱ�ţ�%s\n����״̬��%s\n�۸�(��Ԫ)��%d\n����(����)��%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
        }
    }
    if (flag == 0 || amount == 0) {
        printf("\nû�в�ѯ���÷�\n");
    }
    printf("\n");
    printf("�����������밴1\n������ѯ���ݱ���밴2\n\n");
    int t;
    scanf("%d", &t);
    switch (t)
    {
    case 1:
        return;
        break;
    case 2:
        SreachByNum_H();
        break;
    default:
        break;
    }
}
void view_H() {
    system("cls");
    int amount1 = read_H(1);
    printf("-----------------------------------------------------------------------------------------------------------------------");
    printf("\n|     ��������     |   ���ݱ��   |   ����״̬   |   �۸�(��Ԫ)   |   ����(����)        |\n");
    printf("-----------------------------------------------------------------------------------------------------------------------");
    for (int i = 0; i < amount1; i++) {
        printf("\n|     %-13s|      %-8s|      %-8s|      %-10d|        %-13s|\n",
            house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
        printf("-----------------------------------------------------------------------------------------------------------------------");
    }
    int amount2 = read_H(2);
    for (int i = 0; i < amount2; i++) {
        printf("\n|     %-13s|      %-8s|      %-8s|      %-10d|        %-13s|\n",
            house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
        printf("-----------------------------------------------------------------------------------------------------------------------");
    }
    int amount3 = read_H(3);
    for (int i = 0; i < amount3; i++) {
        printf("\n|     %-13s|      %-8s|      %-8s|      %-10d|        %-13s|\n",
            house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
        printf("-----------------------------------------------------------------------------------------------------------------------");
    }
}
void modify_H() {
    system("cls");
    printf("�����������Ϣ...");
    printf("\n\n�����������\n");
    _getch();
    view_H();
    char Housetype[20];
    int type = 0;
    printf("\n������Ҫ�޸ĵķ��ݵ�����(Apartment, CommonHouse, Villa): ");
    scanf("%s", &Housetype);
    if (strcmp(Housetype, "Apartment") == 0) {
        type = 1;
    }
    else if (strcmp(Housetype, "CommonHouse") == 0) {
        type = 2;
    }
    else if (strcmp(Housetype, "Villa") == 0) {
        type = 3;
    }
    else {
        printf("��������ȷ�ķ�������\n\n");
        _getch();
        modify_H();
    }
    int amount = read_H(type);

    printf("\n������Ҫ�޸ĵķ��ݱ��: ");
    int flag = 0;
    char number[10];
    int n;
    scanf("%s", &number);
    for (int i = 0; i < amount; i++) {
        if (!strcmp(number, house[i].number)) {
            printf("\nҪ�޸ĵķ��ݵ���Ϣ���£�\n");
            printf("\n�������ͣ�%s\n���ݱ�ţ�%s\n����״̬��%s\n�۸�(��Ԫ)��%d\n����(����)��%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
            n = i;
        }
    }

    if (flag == 0 || amount == 0) {
        printf("\nû���ҵ����÷�\n");
        _getch();
        modify_H();
    }

    printf("\nȷ�� ��1 ; ���޸��밴0\n");
    int sure;
    int choise;
    scanf("%d", &sure);
    if (sure == 0) {
        modify_H();
    }
    else {
        do
        {
            do
            {
                printf("\n��Ҫ�����޸ĵ�ѡ��(1~6):\n 1.���ݱ��    2.����״̬    3.�۸�(��Ԫ)    4.����(����)\n\n");
                scanf("%d", &choise);
                if (choise < 1 || choise>6) {
                    printf("\n\n�������,������ѡ��1~6!\n\n");
                }
                else {
                    break;
                }
            } while (1);

            switch (choise)
            {
            case 1:
                printf("���ݱ�Ÿ�Ϊ: \n");
                char NewNum[10];
                scanf("%s", &NewNum);
                strcpy(house[n].number, NewNum);
                break;
            case 2:
                printf("�÷����Ƿ��۳���Ϊ(yes/no): \n");
                char NewS[10];
                scanf("%s", &NewS);
                strncpy(house[n].sold, NewS, sizeof(house[n].sold - 1));
                break;
            case 3:
                printf("���ݼ۸��Ϊ(��Ԫ): \n");
                int NewP;
                scanf("%d", &NewP);
                house[n].price = NewP;
                break;
            case 4:
                printf("���ݹ�����Ϊ(����): \n");
                char NewB[30] = {0};
                scanf("%s", &NewB);
                strncpy(house[n].BelongTo, NewB, sizeof(house[n].BelongTo - 1));
                break;
            default:
                break;
            }

            printf("\nҪ�޸ĵķ��ݵ���Ϣ���£�\n");
            printf("\n�������ͣ�%s\n���ݱ�ţ�%s\n����״̬��%s\n�۸�(��Ԫ)��%d\n����(����)��%s\n",
                house[n].type, house[n].number, house[n].sold, house[n].price, house[n].BelongTo);
            printf("\n\n��1�����޸ģ���0�˳��޸�\n\n");
            int flag2;
            scanf("%d", &flag2);
            if (flag2 == 0) {
                break;
            }
        } while (1);
    }
    save_H(amount);
    printf("\n����1����������\n����0�����޸�\n");
    int flag3 = 0;
    scanf("%d", &flag3);
    if (flag3 == 1) {
        return;
    }
    else if (flag3 == 0) {
        modify_H();
    }
    else {
        printf("\n��᲻�ῴ������֣����ҹ�\n");
        exit(0);
    }
}
void del_H() {
    system("cls");
    printf("�����������Ϣ...");
    printf("\n\n�����������\n");
    _getch();
    view_H();
    char Housetype[20] = {0};
    int type = 0;
    printf("\n������Ҫɾ���ķ��ݵ�����(Apartment, CommonHouse, Villa): ");
    scanf("%s", &Housetype);
    if (strcmp(Housetype, "Apartment") == 0) {
        type = 1;
    }
    else if (strcmp(Housetype, "CommonHouse") == 0) {
        type = 2;
    }
    else if (strcmp(Housetype, "Villa") == 0) {
        type = 3;
    }
    else {
        printf("��������ȷ�ķ�������\n\n");
        _getch();
        del_H();
    }
    int amount = read_H(type);

    printf("\n������Ҫɾ���ķ��ݱ��: ");
    int flag = 0;
    int n = 0;
    char number[10] = {0};
    scanf("%s", &number);
    for (int i = 0; i < amount; i++) {
        if (!strcmp(number, house[i].number)) {
            printf("\nҪ�޸ĵķ��ݵ���Ϣ���£�\n");
            printf("\n�������ͣ�%s\n���ݱ�ţ�%s\n����״̬��%s\n�۸�(��Ԫ)��%d\n����(����)��%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
            n = i;
        }
    }

    if (flag == 0 || amount == 0) {
        printf("\nû���ҵ����÷�\n");
        _getch();
        del_H();
    }

    printf("\nȷ���밴1 ; �����밴0\n");
    int sure;
    scanf("%d", &sure);
    if (sure == 0) {
        del_H();
    }
    else {
        for (int i = n; i < amount; i++) {
            strcpy(house[i].type, house[i + 1].type);
            strcpy(house[i].number, house[i + 1].number);
            strcpy(house[i].sold, house[i + 1].sold);
            strcpy(house[i].BelongTo, house[i + 1].BelongTo);
            house[i].price = house[i + 1].price;

        }

        if (type == 1) {
            FILE* fp1;
            if ((fp1 = fopen(File_H1, "w+")) == NULL)       //�򿪷����б��ļ�Ϊ��
            {
                printf("��ʧ��\n");
                exit(0);
            }
            
            for (int i = 0; i < amount - 1; i++) {
                if (fwrite(&house[i], sizeof(struct House), 1, fp1) != 1)
                    printf("�ļ���д����\n");                   
            }
            fclose(fp1);
        }
        if (type == 2) {
            FILE* fp2;
            if ((fp2 = fopen(File_H2, "w+")) == NULL)       //�򿪷����б��ļ�Ϊ��
            {
                printf("��ʧ��\n");
                exit(0);
            }
           
            for (int i = 0; i < amount - 1; i++) {
                if (fwrite(&house[i], sizeof(struct House), 1, fp2) != 1)
                    printf("�ļ���д����\n");
            }
            fclose(fp2);
        }
        if (type == 3) {
            FILE* fp3;
            if ((fp3 = fopen(File_H3, "w+")) == NULL)       //�򿪷����б��ļ�Ϊ��
            {
                printf("��ʧ��\n");
                exit(0);
            }
            
            for (int i = 0; i < amount - 1; i++) {
                if (fwrite(&house[i], sizeof(struct House), 1, fp3) != 1)
                    printf("�ļ���д����\n");
            }
            fclose(fp3);
        }
        
        printf("ɾ�����");
    }
    
    printf("\n����1����������\n����0����ɾ��\n");
    int flag3 = 0;
    scanf("%d", &flag3);
    if (flag3 == 1) {
        return;
    }
    else if (flag3 == 0) {
        del_H();
    }
    else {
        printf("\n��᲻�ῴ������֣����ҹ�\n");
        exit(0);
    }
}
void add_H() {
    system("cls");
    printf("�����������Ϣ...");
    printf("\n\n�����������\n");
    _getch();
    view_H();
    char Housetype[20] = { 0 };
    int type = 0;
    printf("\n������Ҫ���ӵķ��ݵ�����(Apartment, CommonHouse, Villa): ");
    scanf("%s", &Housetype);
    if (strcmp(Housetype, "Apartment") == 0) {
        type = 1;
    }
    else if (strcmp(Housetype, "CommonHouse") == 0) {
        type = 2;
    }
    else if (strcmp(Housetype, "Villa") == 0) {
        type = 3;
    }
    else {
        printf("��������ȷ�ķ�������\n\n");
        _getch();
        add_H();
    }
    int amount = read_H(type);
    int n;
    do {
        printf("\n���з���%d\n\n��������Ҫ���ӵķ��ݸ���(1~%d): ", amount, 100 - amount);
        scanf("%d", &n);
        if (n < 1 || n > 100 - amount)
        {
            printf("\n������1����100��������\n");
        }
        else
        {
            break;
        }
    } while (1);

    for (int i = 1; i <= n; i++)
    {
        if (type == 1) {
            strcpy(house[amount + i].type, "Apartment");
        }
        else if (type == 2) {
            strcpy(house[amount + i].type, "CommonHouse");
        }
        else
        {
            strcpy(house[amount + i].type, "Villa");
        }

        printf("\n�����뷿�ݱ��: ");
        scanf("%s", &house[amount + i].number);
        printf("\n�������Ƿ��۳�(yes/no): ");
        scanf("%s", &house[amount + i].sold);
        printf("\n�����������۸�(��λ����Ԫ): ");
        scanf("%d", &house[amount + i].price);
        printf("\n�����뷿�ݹ���(����): ");
        scanf("%s", &house[amount + i].BelongTo);
    }
    
    FILE* fp1, * fp2, * fp3;

    if ((fp1 = fopen(File_H1, "a")) == NULL)   //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }
    if ((fp2 = fopen(File_H2, "a")) == NULL) //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }
    if ((fp3 = fopen(File_H3, "a")) == NULL)       //�򿪷����б��ļ�Ϊ��
    {
        printf("��ʧ��\n");
        exit(0);
    }

    for (int i = 1; i <= n; i++) /*���ڴ��з��ݵ���Ϣ����������ļ���ȥ*/
    {
        if (strcmp(house[amount + i].type, "Apartment") == 0)
        {
            if (fwrite(&house[amount + i], sizeof(struct House), 1, fp1) != 1) 
                printf("�ļ���д����\n");

        }
        else if (strcmp(house[amount + i].type, "CommonHouse") == 0)
        {
            if (fwrite(&house[amount + i], sizeof(struct House), 1, fp2) != 1)
                printf("�ļ���д����\n");

        }
        else
        {
            if (fwrite(&house[amount + i], sizeof(struct House), 1, fp3) != 1)
                printf("�ļ���д����\n");

        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    printf("\n�������!\n");
    printf("\n��Ҫ���������밴1\n��Ҫ�������˵��밴0\n");
    int flag3 = 0;
    scanf("%d", &flag3);
    if (flag3 == 0) {
        return;
    }
    else if (flag3 == 1) {
        add_H();
    }
    else {
        printf("\n��᲻�ῴ������֣����ҹ�\n");
        exit(0);
    }
}
void buy_H(VIP* p_head, char ID[10]) {
    system("cls");
    
    readVIPs(p_head);
    VIP* p_move = p_head->next;
    while (strcmp(p_move->ID,ID))
    {
        p_move = p_move->next;
    }
    printf("\t\t\t\t\t�����������Ϣ...");
    printf("\n\n\t\t\t\t\t�����������\n");
    _getch();
    view_H();
    char Housetype[20];
    int type;
    do
    {
        printf("\n\n\n\n������Ҫ����ķ��ݵ�����(Apartment, CommonHouse, Villa): ");
        scanf("%s", &Housetype);
        if (strcmp(Housetype, "Apartment") == 0) {
            type = 1;
            break;

        }
        else if (strcmp(Housetype, "CommonHouse") == 0) {
            type = 2;
            break;

        }
        else if (strcmp(Housetype, "Villa") == 0) {
            type = 3;
            break;
        }
        else {
            printf("��������ȷ�ķ�������\n\n");
        }
    } while (1);
    int amount = read_H(type);

    printf("������Ҫ����ķ��ݵı�ţ�");
    char num[10];
    int flag = 0, n = 0;
    scanf("%s", &num);
    for (int i = 0; i < amount; i++) {
        if (strcmp(house[i].sold, "yes")) {
            printf("�˷��ݲ����ۣ�");
            _getch();
            buy_H(p_head, ID);
        }
        if (!strcmp(num, house[i].number)) {
            printf("\n�������ͣ�%s\n���ݱ�ţ�%s\n����״̬��%s\n�۸�(��Ԫ)��%d\n����(����)��%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
            n = i;
        }
    }
    if (flag == 0 || amount == 0) {
        printf("\nû�в�ѯ���÷�\n");
    }
    printf("\n����1ȷ��������0����\n\n");
    int choise;
    scanf("%d", &choise);
    if (choise == 1) {

        strcpy(house[n].BelongTo, p_move->name);
        strcpy(house[n].sold, "no");
        printf("����ɹ�");
        strcpy(p_move->HouseID, house[n].number);
    }
    else
    {
        return;
    }

    save_H(amount);
    saveVIPs(p_head);
    return;
}

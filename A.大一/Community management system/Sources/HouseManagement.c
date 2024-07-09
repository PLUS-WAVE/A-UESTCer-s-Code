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
        printf("\t\t\t\t功能选择(1~7): ");
        scanf("%d", &n);
        if (n <= 0 || n >= 8)
        {
            printf("\t\t\t\t您输入有误,请重新选择!\n");
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
        printf("\t\t\t\t按任意键继续\n");
        _getch();
        system("cls");
        menu_H();
    }
}
void start_H() //开始界面
{
    system("cls");
    system("color 3F");
    printf("\n\n\n\n\n\n");
    printf("\t\t********************************************************************************\n");
    printf("\n");
    printf("\t\t************************欢迎使用我们的房屋销售管理系统**************************");
    printf("\n\n");
    printf("\t\t********************************************************************************\n\n\n\n\n");
    printf("\t\t\t\t\t      制作人: 王嘉伟\n");
    printf("\t\t\t\t\t      制作时间: 2022年11月\n\n\n\n");
    printf("\t\t\t\t\t      ***按任意键进入***\n");
}
void menu_H() //菜单界面
{
    system("cls");
    system("color 3F");
    printf("\n\n");
    printf("\t\t\t\t————————管理系统————————\n\n");
    printf("\t\t\t\t\t************************\n");
    printf("\t\t\t\t\t********房屋菜单********\n");
    printf("\t\t\t\t\t************************\n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  新建房屋(仅初始化)      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  显示房屋      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  查找房屋      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  删除房屋      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  添加房屋      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t6  修改房屋      \n\n");
    printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t7  退出      \n\n");
    printf("\t\t\t\t注意：\n");
    printf("\t\t\t\t新建房屋选项，输入会覆盖原有信息。\n\n");
}
void input_H() {          //新建房屋(仅初始化)

    int amount;
    system("cls");
    do {
        printf("\n需要录入的房屋个数(1——100): ");
        scanf("%d", &amount);
        if (amount < 1 || amount>100)
        {
            printf("\n请输入1——100的整数！\n");
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
            printf("\n请输入房屋类型(Apartment, CommonHouse, Villa): ");
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
                printf("\n请输入“Apartment, CommonHouse, Villa”中的一种");
            }
        } while (1);
        printf("\n请输入房屋编号: ");
        scanf("%s", &house[i].number);
        printf("\n请输入是否售出(yes/no): ");
        scanf("%s", &house[i].sold);
        printf("\n请输入售卖价格(万元): ");
        scanf("%d", &house[i].price);
        printf("\n请输入房屋归属(姓名): ");
        scanf("%s", &house[i].BelongTo);
    }

    FILE* fp1, * fp2, * fp3;

    if ((fp1 = fopen(File_H1, "w+")) == NULL)   //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }
    if ((fp2 = fopen(File_H2, "w+")) == NULL) //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }
    if ((fp3 = fopen(File_H3, "w+")) == NULL)       //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }

    for (int i = 0; i < amount; i++) /*将内存中房屋的信息输出到磁盘文件中去*/
    {
        if (strcmp(house[i].type, "Apartment") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp1) != 1) 
                printf("文件读写错误\n");

        }
        else if (strcmp(house[i].type, "CommonHouse") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp2) != 1)
                printf("文件读写错误\n");

        }
        else
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp3) != 1)
                printf("文件读写错误\n");

        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    printf("\n创建完毕!\n");
}
void save_H(int a) {  //a是房屋数量
    FILE* fp1, * fp2, * fp3;

    if ((fp1 = fopen(File_H1, "r+")) == NULL)   //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }
    if ((fp2 = fopen(File_H2, "r+")) == NULL) //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }
    if ((fp3 = fopen(File_H3, "r+")) == NULL)       //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }

    for (int i = 0; i < a; i++) /*将内存中房屋的信息输出到磁盘文件中去*/
    {
        if (strcmp(house[i].type, "Apartment") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp1) != 1) 
                printf("文件读写错误\n");

        }
        else if (strcmp(house[i].type, "CommonHouse") == 0)
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp2) != 1)
                printf("文件读写错误\n");

        }
        else
        {
            if (fwrite(&house[i], sizeof(struct House), 1, fp3) != 1)
                printf("文件读写错误\n");

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
            printf("找不到文件\n");
            exit(0);
        }
        else
        {
            while (feof(fp) == 0)  //检测流上的文件结束符
            {
                fread(&house[i], sizeof(struct House), 1, fp); //读取
                i++;
            }
        }
    }
    if (type == 2) {
        if ((fp = fopen(File_H2, "r")) == NULL)
        {
            printf("找不到文件\n");
            exit(0);
        }
        else
        {
            while (feof(fp) == 0)  //检测流上的文件结束符
            {
                fread(&house[i], sizeof(struct House), 1, fp); //读取
                i++;
            }
        }
    }
    if (type == 3) {
        if ((fp = fopen(File_H3, "r")) == NULL)
        {
            printf("找不到文件\n");
            exit(0);
        }
        else
        {
            while (feof(fp) == 0)  //检测流上的文件结束符
            {
                fread(&house[i], sizeof(struct House), 1, fp); //读取
                i++;
            }
        }
    }
    fclose(fp);
    return i - 1;//返回该类房屋个数
}
void search_H() {
    int t;
    system("cls");//清屏
    do
    {
        printf("\n按1 查询\t按2 回主菜单\n\n");
        scanf("%d", &t);
        if (t >= 1 && t <= 2)
        {
            break;
        }
        else
        {
            printf("输入错误");
        }
    } while (1);
    while (1)
    {
        switch (t)
        {
        case 1:
            printf("\n正在查询...\n\n");
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
    printf("\n请输入要查询的房屋类型(Apartment, CommonHouse, Villa): ");
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
        printf("请输入正确的房屋类型\n\n");
        SreachByNum_H();
    }
    int amount = read_H(type);
    printf("请输入要查找的房屋编号: ");
    char number[10];
    int flag = 0;
    scanf("%s", &number);
    for (int i = 0; i < amount; i++) {
        if (!strcmp(number, house[i].number)) {
            printf("\n房屋类型：%s\n房屋编号：%s\n房屋状态：%s\n价格(万元)：%d\n归属(姓名)：%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
        }
    }
    if (flag == 0 || amount == 0) {
        printf("\n没有查询到该房\n");
    }
    printf("\n");
    printf("返回主界面请按1\n继续查询房屋编号请按2\n\n");
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
    printf("\n|     房屋类型     |   房屋编号   |   房屋状态   |   价格(万元)   |   归属(姓名)        |\n");
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
    printf("请浏览房屋信息...");
    printf("\n\n按任意键继续\n");
    _getch();
    view_H();
    char Housetype[20];
    int type = 0;
    printf("\n请输入要修改的房屋的种类(Apartment, CommonHouse, Villa): ");
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
        printf("请输入正确的房屋类型\n\n");
        _getch();
        modify_H();
    }
    int amount = read_H(type);

    printf("\n请输入要修改的房屋编号: ");
    int flag = 0;
    char number[10];
    int n;
    scanf("%s", &number);
    for (int i = 0; i < amount; i++) {
        if (!strcmp(number, house[i].number)) {
            printf("\n要修改的房屋的信息如下：\n");
            printf("\n房屋类型：%s\n房屋编号：%s\n房屋状态：%s\n价格(万元)：%d\n归属(姓名)：%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
            n = i;
        }
    }

    if (flag == 0 || amount == 0) {
        printf("\n没有找到到该房\n");
        _getch();
        modify_H();
    }

    printf("\n确定 按1 ; 不修改请按0\n");
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
                printf("\n需要进行修改的选项(1~6):\n 1.房屋编号    2.房屋状态    3.价格(万元)    4.归属(姓名)\n\n");
                scanf("%d", &choise);
                if (choise < 1 || choise>6) {
                    printf("\n\n输入错误,请重新选择1~6!\n\n");
                }
                else {
                    break;
                }
            } while (1);

            switch (choise)
            {
            case 1:
                printf("房屋编号改为: \n");
                char NewNum[10];
                scanf("%s", &NewNum);
                strcpy(house[n].number, NewNum);
                break;
            case 2:
                printf("该房屋是否售出改为(yes/no): \n");
                char NewS[10];
                scanf("%s", &NewS);
                strncpy(house[n].sold, NewS, sizeof(house[n].sold - 1));
                break;
            case 3:
                printf("房屋价格改为(万元): \n");
                int NewP;
                scanf("%d", &NewP);
                house[n].price = NewP;
                break;
            case 4:
                printf("房屋归属改为(姓名): \n");
                char NewB[30] = {0};
                scanf("%s", &NewB);
                strncpy(house[n].BelongTo, NewB, sizeof(house[n].BelongTo - 1));
                break;
            default:
                break;
            }

            printf("\n要修改的房屋的信息如下：\n");
            printf("\n房屋类型：%s\n房屋编号：%s\n房屋状态：%s\n价格(万元)：%d\n归属(姓名)：%s\n",
                house[n].type, house[n].number, house[n].sold, house[n].price, house[n].BelongTo);
            printf("\n\n按1继续修改，按0退出修改\n\n");
            int flag2;
            scanf("%d", &flag2);
            if (flag2 == 0) {
                break;
            }
        } while (1);
    }
    save_H(amount);
    printf("\n输入1返回主界面\n输入0继续修改\n");
    int flag3 = 0;
    scanf("%d", &flag3);
    if (flag3 == 1) {
        return;
    }
    else if (flag3 == 0) {
        modify_H();
    }
    else {
        printf("\n你会不会看上面的字，给我滚\n");
        exit(0);
    }
}
void del_H() {
    system("cls");
    printf("请浏览房屋信息...");
    printf("\n\n按任意键继续\n");
    _getch();
    view_H();
    char Housetype[20] = {0};
    int type = 0;
    printf("\n请输入要删除的房屋的种类(Apartment, CommonHouse, Villa): ");
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
        printf("请输入正确的房屋类型\n\n");
        _getch();
        del_H();
    }
    int amount = read_H(type);

    printf("\n请输入要删除的房屋编号: ");
    int flag = 0;
    int n = 0;
    char number[10] = {0};
    scanf("%s", &number);
    for (int i = 0; i < amount; i++) {
        if (!strcmp(number, house[i].number)) {
            printf("\n要修改的房屋的信息如下：\n");
            printf("\n房屋类型：%s\n房屋编号：%s\n房屋状态：%s\n价格(万元)：%d\n归属(姓名)：%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
            n = i;
        }
    }

    if (flag == 0 || amount == 0) {
        printf("\n没有找到到该房\n");
        _getch();
        del_H();
    }

    printf("\n确定请按1 ; 返回请按0\n");
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
            if ((fp1 = fopen(File_H1, "w+")) == NULL)       //打开房屋列表文件为空
            {
                printf("打开失败\n");
                exit(0);
            }
            
            for (int i = 0; i < amount - 1; i++) {
                if (fwrite(&house[i], sizeof(struct House), 1, fp1) != 1)
                    printf("文件读写错误\n");                   
            }
            fclose(fp1);
        }
        if (type == 2) {
            FILE* fp2;
            if ((fp2 = fopen(File_H2, "w+")) == NULL)       //打开房屋列表文件为空
            {
                printf("打开失败\n");
                exit(0);
            }
           
            for (int i = 0; i < amount - 1; i++) {
                if (fwrite(&house[i], sizeof(struct House), 1, fp2) != 1)
                    printf("文件读写错误\n");
            }
            fclose(fp2);
        }
        if (type == 3) {
            FILE* fp3;
            if ((fp3 = fopen(File_H3, "w+")) == NULL)       //打开房屋列表文件为空
            {
                printf("打开失败\n");
                exit(0);
            }
            
            for (int i = 0; i < amount - 1; i++) {
                if (fwrite(&house[i], sizeof(struct House), 1, fp3) != 1)
                    printf("文件读写错误\n");
            }
            fclose(fp3);
        }
        
        printf("删除完成");
    }
    
    printf("\n输入1返回主界面\n输入0继续删除\n");
    int flag3 = 0;
    scanf("%d", &flag3);
    if (flag3 == 1) {
        return;
    }
    else if (flag3 == 0) {
        del_H();
    }
    else {
        printf("\n你会不会看上面的字，给我滚\n");
        exit(0);
    }
}
void add_H() {
    system("cls");
    printf("请浏览房屋信息...");
    printf("\n\n按任意键继续\n");
    _getch();
    view_H();
    char Housetype[20] = { 0 };
    int type = 0;
    printf("\n请输入要增加的房屋的种类(Apartment, CommonHouse, Villa): ");
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
        printf("请输入正确的房屋类型\n\n");
        _getch();
        add_H();
    }
    int amount = read_H(type);
    int n;
    do {
        printf("\n现有房屋%d\n\n请输入需要增加的房屋个数(1~%d): ", amount, 100 - amount);
        scanf("%d", &n);
        if (n < 1 || n > 100 - amount)
        {
            printf("\n请输入1——100的整数！\n");
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

        printf("\n请输入房屋编号: ");
        scanf("%s", &house[amount + i].number);
        printf("\n请输入是否售出(yes/no): ");
        scanf("%s", &house[amount + i].sold);
        printf("\n请输入售卖价格(单位：万元): ");
        scanf("%d", &house[amount + i].price);
        printf("\n请输入房屋归属(姓名): ");
        scanf("%s", &house[amount + i].BelongTo);
    }
    
    FILE* fp1, * fp2, * fp3;

    if ((fp1 = fopen(File_H1, "a")) == NULL)   //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }
    if ((fp2 = fopen(File_H2, "a")) == NULL) //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }
    if ((fp3 = fopen(File_H3, "a")) == NULL)       //打开房屋列表文件为空
    {
        printf("打开失败\n");
        exit(0);
    }

    for (int i = 1; i <= n; i++) /*将内存中房屋的信息输出到磁盘文件中去*/
    {
        if (strcmp(house[amount + i].type, "Apartment") == 0)
        {
            if (fwrite(&house[amount + i], sizeof(struct House), 1, fp1) != 1) 
                printf("文件读写错误\n");

        }
        else if (strcmp(house[amount + i].type, "CommonHouse") == 0)
        {
            if (fwrite(&house[amount + i], sizeof(struct House), 1, fp2) != 1)
                printf("文件读写错误\n");

        }
        else
        {
            if (fwrite(&house[amount + i], sizeof(struct House), 1, fp3) != 1)
                printf("文件读写错误\n");

        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    printf("\n增加完毕!\n");
    printf("\n若要继续增加请按1\n若要返回主菜单请按0\n");
    int flag3 = 0;
    scanf("%d", &flag3);
    if (flag3 == 0) {
        return;
    }
    else if (flag3 == 1) {
        add_H();
    }
    else {
        printf("\n你会不会看上面的字，给我滚\n");
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
    printf("\t\t\t\t\t请浏览房屋信息...");
    printf("\n\n\t\t\t\t\t按任意键继续\n");
    _getch();
    view_H();
    char Housetype[20];
    int type;
    do
    {
        printf("\n\n\n\n请输入要购买的房屋的种类(Apartment, CommonHouse, Villa): ");
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
            printf("请输入正确的房屋类型\n\n");
        }
    } while (1);
    int amount = read_H(type);

    printf("请输入要购买的房屋的编号：");
    char num[10];
    int flag = 0, n = 0;
    scanf("%s", &num);
    for (int i = 0; i < amount; i++) {
        if (strcmp(house[i].sold, "yes")) {
            printf("此房屋不出售！");
            _getch();
            buy_H(p_head, ID);
        }
        if (!strcmp(num, house[i].number)) {
            printf("\n房屋类型：%s\n房屋编号：%s\n房屋状态：%s\n价格(万元)：%d\n归属(姓名)：%s\n",
                house[i].type, house[i].number, house[i].sold, house[i].price, house[i].BelongTo);
            flag = 1;
            n = i;
        }
    }
    if (flag == 0 || amount == 0) {
        printf("\n没有查询到该房\n");
    }
    printf("\n输入1确定，输入0返回\n\n");
    int choise;
    scanf("%d", &choise);
    if (choise == 1) {

        strcpy(house[n].BelongTo, p_move->name);
        strcpy(house[n].sold, "no");
        printf("购买成功");
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

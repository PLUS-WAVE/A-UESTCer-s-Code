#define _CRT_SECURE_NO_WARNINGS
#include"WorkerManagement.h"
#include"VIP.h"
#include"Serve.h"
void start_W() {
	system("cls");
	system("color 3F");
	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t************************欢迎使用我们的工作人员管理系统**************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t\t      制作人: 卫建业\n");
	printf("\t\t\t\t\t      制作时间: 2022年\n\n\n\n");
	printf("\t\t\t\t\t      ***按任意键进入***\n");
	_getch();
}
void menu_W(Service* H) {

	int count = 0;
	readserve(H);
	Service* p_move = H->next;
	while (p_move != NULL) {
		
		if (strcmp(p_move->acc, "已接受")) {
			count++;

		}
		p_move = p_move->next;
	}
	
	system("cls");
	system("color 3F");
	printf("\n\n");
	printf("\t\t\t\t————————管理系统————————\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********菜单**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  查看当前所有工作人员      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  新增工作人员      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  删除工作人员      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  修改人员信息      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  VIP服务处理(未处理信息：%d)      \n\n",count);
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t6  退出      \n\n");
	printf("\t\t\t\t请选择：");

	deleteLink_S(H);
}
void WorkerManagement(list* hs, Service*H, VIP* p_head)
{
	start_W();
	menu_W(H);
	int i = 0;
	scanf_s("%d", &i);
	switch (i)
	{
	case 1:
		showuser(hs);
		break;
	case 2:
		adduser(hs); 
		break;
	case 3:
		deleteuser(hs); 
		break;
	case 4:
		change(hs); 
		break;
	case 5:
		serveM(H, hs, p_head);
		break;
	case 6:
		printf("再见！\n"); 
		return;
		break;
	default:
		printf("嫑乱输"); 
		Sleep(2000);
		return;
	}
	WorkerManagement(hs, H, p_head);
}
void readuser(list* hs)
{
	system("cls");
	FILE* fp;
	if ((fp = fopen(file, "r")) == NULL)
	{
		printf("打开失败！\n");
	}
	else
	{
		fp = fopen(file, "r");
		date dates;
		node_w* node_ws;
		hs->head = NULL;
		hs->num = 0;
		while (!feof(fp))
		{
			fscanf(fp, "%s\t%s\t%s", dates.name, dates.job, dates.object);
			node_ws = (node_w*)malloc(sizeof(node_w));
			node_ws->date = dates;
			node_ws->next = hs->head;
			hs->head = node_ws;
			hs->num += 1;
		}
	}
	fclose(fp);
}
void showuser(list*hs)
{
	
	readuser(hs);
	printf("\n\n\t\t\t\t---------------工作人员详情--------------\n");
	printf("\t\t\t\t姓名\t\t职务\t\t服务对象\n");
	node_w* p = (node_w*)malloc(sizeof(node_w));
	node_w* q;
	q = hs->head;
	p = q->next;
	while (p) {
		printf("\t\t\t\t%s\t\t", p->date.name);
		if (strlen(p->date.job) < 8)
			printf("%s\t\t", p->date.job);
		else if (strlen(p->date.job) >= 8)
			printf("%s\t", p->date.job);
		printf("%s", p->date.object);
		printf("\n");
		p = p->next;
	}
	
	printf("\n\n\t\t\t\t\t--------1.返回--------\n\t\t\t\t\t--------2.退出--------\n");
    L1:printf("\t\t\t\t\t请输入：");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("\t\t\t\t\t嫑乱输！\n"); goto L1;
	}
}
void adduser(list* hs)
{
	hs->head = NULL;
	system("cls");
	//向链表中添加
	node_w* p = (node_w*)malloc(sizeof(node_w));
	date dates;
	printf("请输入工作人员姓名：\n");
	scanf("%s", dates.name);
	printf("请输入工作人员职务：\n");
	scanf("%s", dates.job);
	printf("请输入工作人员服务对象：\n");
	scanf("%s", dates.object);
	p->date = dates;
	p->next = hs->head;
	hs->head = p;
	hs->num += 1;
	//写入文件
	writeuser(hs);
	printf("添加成功！\n");
	printf("--------1.返回--------\n--------2.退出--------\n");
L1:printf("请输入：");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("\t\t\t\t\t嫑乱输！\n"); goto L1;
	}
}
void writeuser(list*hs)
{
		FILE* fp;
		node_w* t = hs->head;
		if ((fp = fopen(file, "r+")) == NULL)
		{
			printf("打开失败！\n");
			return;
		}
		fp = fopen(file, "a+");
		while (t)
		{
			fprintf(fp, "%s\t", t->date.name);
			fprintf(fp, "%s\t", t->date.job);
			fprintf(fp, "%s\t", t->date.object);
			t = t->next;
		}
		fclose(fp);
	}
void rewriteuser(list* hs)
{
	FILE* fp;
	node_w* t = hs->head->next;
	if ((fp = fopen(file, "r+")) == NULL)
	{
		printf("打开失败！\n");
		return;
	}
	fp = fopen(file, "w+");
	while (t)
	{
		fprintf(fp, "%s\t", t->date.name);
		fprintf(fp, "%s\t", t->date.job);
		fprintf(fp, "%s\t", t->date.object);
		t = t->next;
	}
	fclose(fp);
}
void print_one_w(node_w*p)
{
	printf("------------------------------------\n");
	printf("姓名:%s\t",p->date.name);
	printf("职务:%s\t",p->date.job);
	printf("服务对象:%s\n",p->date.object);
	printf("------------------------------------");
}
void deleteuser(list*hs)
{
	readuser(hs);
	if (hs->num <= 0)
	{
		printf("目前不存在工作人员！\n");
		return;
	}
    printf("请输入工作人员姓名:\n");
	char Name[20];
	scanf("%s", Name);
	node_w* p = hs->head;
	if (!strcmp(p->date.name, Name))//首结点就是要删除的信息
	{
		print_one_w(p);
		printf("\n是否删除此人信息？\n1.是\n2.否\n请选择：");
		int y = 0;
		scanf("%d", &y);
		if (y == 1)
		{
			hs->head= p->next;
			free(p);
			printf("删除成功！");
			rewriteuser(hs);
			goto L4;
		}
		else while (1)
		{
			printf("--------1.返回--------\n--------2.继续--------\n");
		L6:printf("请输入：");
			int j = 0;
			scanf("%d", &j);
			switch (j)
			{
			case 1:return;
				break;
			case 2:deleteuser(hs);
				break;
			default:printf("嫑乱输！\n"); goto L6;
			}
		}
	}
	while (p->next != NULL && (strcmp(p->next->date.name, Name)))//非首节点
		p = p->next;
	if (p->next == NULL)
		printf("此人不存在！\n");
	else
	{
		print_one_w(p->next);
		printf("\n是否删除此人信息？\n1.是\n2.否\n请选择：");
		int y = 0;
		scanf("%d", &y);
		if (y == 1)
		{
			node_w* tmp;
			tmp = p->next;
			p->next = tmp->next;
			free(tmp);
			printf("\n删除成功！");
			hs->num -= 1;
		}
		else while (1)
		{
			printf("--------1.返回--------\n--------2.继续--------\n");
		L5:printf("请输入：");
			int j = 0;
			scanf("%d", &j);
			switch (j)
			{
			case 1:return;
				break;
			case 2:deleteuser(hs);
				break;
			default:printf("嫑乱输！\n"); goto L5;
			}
			
		}
	}
	rewriteuser(hs);
L4:	printf("\n--------1.返回--------\n--------2.退出--------\n");
L3:printf("请输入：");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("嫑乱输！\n"); goto L3;
	}
}
void change(list*hs)
{
	//hs->head = NULL;

	readuser(hs);
	system("cls");
	printf("请输入要修改人员的姓名：\n");
	char Name[20];
	scanf("%s",Name);
	node_w* p = hs->head->next;
	while (p != NULL && (strcmp(p->date.name, Name)))
		p = p->next;
	if (p==NULL)
		printf("此人不存在!");
	else {
		printf("\n该人员原信息如下：\n");
		print_one_w(p);
		printf("\n\n请输入新的信息\n");
		printf("姓名：\n");
		scanf("%s", p->date.name);
		printf("职务：\n");
		scanf("%s", p->date.job);
		printf("服务对象：\n");
		scanf("%s", p->date.object);
		printf("\n新的信息如下：\n");
		print_one_w(p);
	}
	rewriteuser(hs);
	printf("\n\n--------1.返回--------\n--------2.退出--------\n");
L7:printf("请输入：");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("嫑乱输！\n"); goto L7;
	}
}


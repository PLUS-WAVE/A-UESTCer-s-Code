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
	printf("\t\t************************��ӭʹ�����ǵĹ�����Ա����ϵͳ**************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t\t      ������: ����ҵ\n");
	printf("\t\t\t\t\t      ����ʱ��: 2022��\n\n\n\n");
	printf("\t\t\t\t\t      ***�����������***\n");
	_getch();
}
void menu_W(Service* H) {

	int count = 0;
	readserve(H);
	Service* p_move = H->next;
	while (p_move != NULL) {
		
		if (strcmp(p_move->acc, "�ѽ���")) {
			count++;

		}
		p_move = p_move->next;
	}
	
	system("cls");
	system("color 3F");
	printf("\n\n");
	printf("\t\t\t\t��������������������ϵͳ����������������\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********�˵�**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  �鿴��ǰ���й�����Ա      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  ����������Ա      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  ɾ��������Ա      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  �޸���Ա��Ϣ      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  VIP������(δ������Ϣ��%d)      \n\n",count);
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t6  �˳�      \n\n");
	printf("\t\t\t\t��ѡ��");

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
		printf("�ټ���\n"); 
		return;
		break;
	default:
		printf("������"); 
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
		printf("��ʧ�ܣ�\n");
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
	printf("\n\n\t\t\t\t---------------������Ա����--------------\n");
	printf("\t\t\t\t����\t\tְ��\t\t�������\n");
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
	
	printf("\n\n\t\t\t\t\t--------1.����--------\n\t\t\t\t\t--------2.�˳�--------\n");
    L1:printf("\t\t\t\t\t�����룺");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("\t\t\t\t\t�����䣡\n"); goto L1;
	}
}
void adduser(list* hs)
{
	hs->head = NULL;
	system("cls");
	//�����������
	node_w* p = (node_w*)malloc(sizeof(node_w));
	date dates;
	printf("�����빤����Ա������\n");
	scanf("%s", dates.name);
	printf("�����빤����Աְ��\n");
	scanf("%s", dates.job);
	printf("�����빤����Ա�������\n");
	scanf("%s", dates.object);
	p->date = dates;
	p->next = hs->head;
	hs->head = p;
	hs->num += 1;
	//д���ļ�
	writeuser(hs);
	printf("��ӳɹ���\n");
	printf("--------1.����--------\n--------2.�˳�--------\n");
L1:printf("�����룺");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("\t\t\t\t\t�����䣡\n"); goto L1;
	}
}
void writeuser(list*hs)
{
		FILE* fp;
		node_w* t = hs->head;
		if ((fp = fopen(file, "r+")) == NULL)
		{
			printf("��ʧ�ܣ�\n");
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
		printf("��ʧ�ܣ�\n");
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
	printf("����:%s\t",p->date.name);
	printf("ְ��:%s\t",p->date.job);
	printf("�������:%s\n",p->date.object);
	printf("------------------------------------");
}
void deleteuser(list*hs)
{
	readuser(hs);
	if (hs->num <= 0)
	{
		printf("Ŀǰ�����ڹ�����Ա��\n");
		return;
	}
    printf("�����빤����Ա����:\n");
	char Name[20];
	scanf("%s", Name);
	node_w* p = hs->head;
	if (!strcmp(p->date.name, Name))//�׽�����Ҫɾ������Ϣ
	{
		print_one_w(p);
		printf("\n�Ƿ�ɾ��������Ϣ��\n1.��\n2.��\n��ѡ��");
		int y = 0;
		scanf("%d", &y);
		if (y == 1)
		{
			hs->head= p->next;
			free(p);
			printf("ɾ���ɹ���");
			rewriteuser(hs);
			goto L4;
		}
		else while (1)
		{
			printf("--------1.����--------\n--------2.����--------\n");
		L6:printf("�����룺");
			int j = 0;
			scanf("%d", &j);
			switch (j)
			{
			case 1:return;
				break;
			case 2:deleteuser(hs);
				break;
			default:printf("�����䣡\n"); goto L6;
			}
		}
	}
	while (p->next != NULL && (strcmp(p->next->date.name, Name)))//���׽ڵ�
		p = p->next;
	if (p->next == NULL)
		printf("���˲����ڣ�\n");
	else
	{
		print_one_w(p->next);
		printf("\n�Ƿ�ɾ��������Ϣ��\n1.��\n2.��\n��ѡ��");
		int y = 0;
		scanf("%d", &y);
		if (y == 1)
		{
			node_w* tmp;
			tmp = p->next;
			p->next = tmp->next;
			free(tmp);
			printf("\nɾ���ɹ���");
			hs->num -= 1;
		}
		else while (1)
		{
			printf("--------1.����--------\n--------2.����--------\n");
		L5:printf("�����룺");
			int j = 0;
			scanf("%d", &j);
			switch (j)
			{
			case 1:return;
				break;
			case 2:deleteuser(hs);
				break;
			default:printf("�����䣡\n"); goto L5;
			}
			
		}
	}
	rewriteuser(hs);
L4:	printf("\n--------1.����--------\n--------2.�˳�--------\n");
L3:printf("�����룺");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("�����䣡\n"); goto L3;
	}
}
void change(list*hs)
{
	//hs->head = NULL;

	readuser(hs);
	system("cls");
	printf("������Ҫ�޸���Ա��������\n");
	char Name[20];
	scanf("%s",Name);
	node_w* p = hs->head->next;
	while (p != NULL && (strcmp(p->date.name, Name)))
		p = p->next;
	if (p==NULL)
		printf("���˲�����!");
	else {
		printf("\n����Աԭ��Ϣ���£�\n");
		print_one_w(p);
		printf("\n\n�������µ���Ϣ\n");
		printf("������\n");
		scanf("%s", p->date.name);
		printf("ְ��\n");
		scanf("%s", p->date.job);
		printf("�������\n");
		scanf("%s", p->date.object);
		printf("\n�µ���Ϣ���£�\n");
		print_one_w(p);
	}
	rewriteuser(hs);
	printf("\n\n--------1.����--------\n--------2.�˳�--------\n");
L7:printf("�����룺");
	int j = 0;
	scanf("%d", &j);
	switch (j)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("�����䣡\n"); goto L7;
	}
}


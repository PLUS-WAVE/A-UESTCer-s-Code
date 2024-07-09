#define _CRT_SECURE_NO_WARNINGS 1
#include"FacilitiesManagement.h"
#include"VIP.h"
void faci_init_f(Linkedlist *h) {
	if (h->head != NULL) {
		Node* p = h->head;
		while (h->head) {
			p = h->head;
			h->head = h->head->next;
			free(p);
		}
	}
	
	system("cls");
	FILE* fp;  
	if ((fp = fopen(File_F, "r")) == NULL) {
		if (((fp = fopen(File_F, "w")) == NULL))
			printf("\t\t\t\t\t�����ļ�ʧ��\n");
	}	//������ļ�·�����޸�
	else {
		Recreational_facilities tmp;
		Node* node;
		h->head = NULL;
		h->current_num = 0;
		while (!feof(fp)) {
			fscanf(fp, "%s\t%s\t%d\t%d\t%s", tmp.name, tmp.condition,&tmp.now,&tmp.error, tmp.director);
			node = (Node*)malloc(sizeof(Node));
			node->recreational_facilities = tmp;
			node->next = h->head;
			h->head = node;
			h->current_num += 1;
		}
	}
	fclose(fp);
	printf("\t\t\t\t\t��ʼ�����\n");
}
void print_info_f(Linkedlist *h) {
	system("cls");
	if (h->current_num <= 0)
		printf("\t\t\t\t\t����Ϊ��\n");
	Node* p = h->head;
	while (p) {
		printf("\n\n\t\t\t���ƣ�%s\t", p->recreational_facilities.name);
		printf("״̬��%s(%d/%d)\t", p->recreational_facilities.condition, p->recreational_facilities.now, p->recreational_facilities.error);
		printf("�����ˣ�%s\n", p->recreational_facilities.director);
		p = p->next;
	}
	printf("\n\n\t\t\t�������������");
	_getch();
}
void search_f(Linkedlist *h) {
	system("cls");
	printf("\t\t\t\t\tѡ����ҷ�ʽ��1�����Ʋ��ң�2��״̬����,-1ȡ������");
	int way;
	scanf("%d", &way);
	if (way == -1)
		return;
	else if (way == 1) 
	{printf("\t\t\t\t\t�����������ĳ������ƣ�-1ȡ����:");
		char name[NAME_LEN];
		scanf("%s", name);
		if (!strcmp(name, "-1"))
			return;
		Node* p = h->head;
		while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
			p = p->next;
		if (p == NULL)
			printf("\t\t\t\t\t���ݲ�����\n");
		else {
			printf("\t\t\t���ƣ�%s\t", p->recreational_facilities.name);
			printf("״̬��%s(%d/%d)\t", p->recreational_facilities.condition, p->recreational_facilities.now, p->recreational_facilities.error);
			printf("�����ˣ�%s\n", p->recreational_facilities.director);
		}
	}
	else if (way == 2) {
		printf("\t\t\t\t\t�������������ݵ�״̬��-1ȡ������");
		char condition[CON_LEN];
		scanf("%s", condition);
		if (!strcmp(condition, "-1"))
			return;
		Node* q = h->head;
		while (q != NULL) {
			if (!strcmp(q->recreational_facilities.condition, condition)) {
				printf("\t\t\t���ƣ�%s\t", q->recreational_facilities.name);
				printf("״̬��%s(%d/%d)\t", q->recreational_facilities.condition, q->recreational_facilities.now, q->recreational_facilities.error);
				printf("�����ˣ�%s\n", q->recreational_facilities.director);
			}
			q = q->next;
		}
	}
	printf("\n\n\n\t\t\t�������������");
	_getch();
}
void update_f(Linkedlist *h) {
	system("cls");
	printf("\t\t\t\t\t������Ҫ�޸���Ϣ�ĳ������ƣ�-1ȡ����:");
	char name[NAME_LEN];
	scanf("%s", name);
	if (!strcmp(name, "-1"))
		return;
	Node* p = h->head;
	while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
		p = p->next;
	if (p == NULL)
		printf("\t\t\t\t\t���ݲ�����\n");
	else {
		printf("\t\t\t\t\t���볡����Ϣ\n");
		printf("\t\t\t\t\t����\n");
		scanf("%s", p->recreational_facilities.name);
		printf("\t\t\t\t\t״̬�����������������Կո�����\n");
		scanf("%s %d", p->recreational_facilities.condition,&p->recreational_facilities.error);
		printf("\t\t\t\t\t������\n");
		scanf("%s", p->recreational_facilities.director);
		printf("\t\t\t\t\t������Ϣ�������\n");
	}
	printf("�������������");
	_getch();
}
void delete_f(Linkedlist *h) {
	system("cls");
	if (h->current_num <= 0) {
		printf("\t\t\t\t\t����Ϊ��\n");
		return;
	}
	printf("\t\t\t\t\t����Ҫɾ���ĳ������ƣ�-1ȡ����:");
	char name[NAME_LEN];
	scanf("%s", name);
	if (!strcmp(name, "-1"))
		return;
	Node* p = h->head;
	if (!strcmp(p->recreational_facilities.name, name)) {
		h->head = p->next;
		free(p);
		return;
	}
	while (p->next != NULL && (strcmp(p->next->recreational_facilities.name, name)))
		p = p->next;
	if (p->next == NULL)
		printf("\t\t\t\t\t���ݲ�����");
	else {
		printf("\t\t\t\t\t���ƣ�%s\n", p->next->recreational_facilities.name);
		printf("\t\t\t\t\t״̬��%s\n", p->next->recreational_facilities.condition);
		printf("\t\t\t\t\t�����ˣ�%s\n", p->next->recreational_facilities.director);
		printf("\t\t\t\t\tɾ�����ݣ�(Y/N)\n");
		char answer[10];
		scanf("%s", &answer);
		if (!strcmp(answer,"Y")) {
			Node* tmp;
			tmp = p->next;
			p->next = tmp->next;
			free(tmp);
			h->current_num -= 1;
		}
		else return;
	}
	printf("�������������");
	_getch();
}
void add_f(Linkedlist *h) {
	system("cls");
	Node* p = (Node*)malloc(sizeof(Node)), * tmp;
	Recreational_facilities recreational_facilities;
	printf("\t\t\t\t\t���볡����Ϣ\n");
	printf("\t\t\t\t\t�������ƣ�");
	scanf("%s", recreational_facilities.name);
	printf("\t\t\t\t\t����״̬�����������������Կո�������");
	scanf("%s %d", recreational_facilities.condition, &recreational_facilities.error);
	recreational_facilities.now = 0;
	printf("\t\t\t\t\t���븺���ˣ�");
	scanf("%s", recreational_facilities.director);
	p->recreational_facilities = recreational_facilities;
	tmp = h->head;
	while (tmp->next)
		tmp = tmp->next;;
	tmp->next = p;
	p->next = NULL;
	h->current_num += 1;
	printf("\t\t\t\t\t�½��ɹ�\n");
	printf("�������������");
	_getch();
}
void record_f(Linkedlist* h,VIP* p_head,char ID[ID_LEN]) {
	faci_init_f(h);
	system("cls");
	printf("\t\t\t\t\t�������ʹ�õĳ������ƣ�-1ȡ����:");
	char name[NAME_LEN];
	VIP* tmp = p_head->next;
	scanf("%s", name);
	if (!strcmp(name, "-1"))
		return;
	Node* p = h->head;
	while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
		p = p->next;
	if (p == NULL) {
		printf("\t\t\t\t\t���ݲ�����\n");
		return;
	}	
	else {
		if (!strcmp(p->recreational_facilities.condition, "ά����"))
			printf("\t\t\t\t\t��Ǹ���ó�������ά��");
		else if (!strcmp(p->recreational_facilities.condition, "����"))
		{
			printf("\t\t\t\t\t��ӭʹ��"); p->recreational_facilities.now++;
			while (tmp != NULL && strcmp(tmp->ID, ID))
				tmp = tmp->next;
			strcpy(tmp->facility, name);
		}
		else if (!strcmp(p->recreational_facilities.condition, "ӵ��"))
		{
			printf("\t\t\t\t\t�ó��������϶࣬����Ӱ��ʹ�����飬�Ƿ������(Y/N)");
			char answer; scanf("%c", &answer);
			if (answer == 'Y' || answer == 'y') {
				printf("\t\t\t\t\t��ӭʹ��\n"); p->recreational_facilities.now++;
				while (tmp != NULL && strcmp(tmp->ID, ID))
					tmp = tmp->next;
				strcpy(tmp->facility, name);
				
			}
		}
	}
	if (p->recreational_facilities.now > p->recreational_facilities.error)
		strcpy(p->recreational_facilities.condition, "ӵ��");

	printf("�������������");
	saveVIPs(p_head);

	_getch();

	flush_f(h);
}
void leave_f(Linkedlist* h,VIP* p_head, char ID[ID_LEN]) {
	faci_init_f(h);
	system("cls");
	VIP* tmp = p_head->next;
	while (tmp != NULL && strcmp(tmp->ID, ID))
		tmp = tmp->next;
	if (!strcmp(tmp->facility, "��"))
	{
		printf("��ǰδʹ�ó���"); return;
	}
	char name[NAME_LEN];
	strcpy(name, tmp->facility);
	Node* p = h->head;
	while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
		p = p->next;
		printf("\t\t\t\t\t�˳��ɹ�\n");
		p->recreational_facilities.now--;
	if (p->recreational_facilities.now <= p->recreational_facilities.error)
		strcpy(p->recreational_facilities.condition, "����");
	strcpy(tmp->facility, "��");
	printf("�������������");
	saveVIPs(p_head);

	_getch();
	flush_f(h);
}
void flush_f(Linkedlist *h) {
	system("cls");
	FILE* fp;
	Node* p = h->head;
	int count = 0;
	if ((fp = fopen(File_F, "w")) == NULL) {
		printf("\t\t\t\t\t���ļ�ʧ��\n");
			return;
	}
	while (p) {
		fprintf(fp, "%s\t", p->recreational_facilities.name);
		fprintf(fp, "%s\t%d\t%d\t", p->recreational_facilities.condition, p->recreational_facilities.now, p->recreational_facilities.error);
		if (p->next == NULL)
			fprintf(fp, "%s", p->recreational_facilities.director);
		else fprintf(fp, "%s\n", p->recreational_facilities.director);
		p = p->next;
		count++;
	}
	fclose(fp);

	while (h->head) {
		p = h->head;
		h->head = h->head->next;
		free(p);
	}

	if (count > 0)
		printf("\t\t\t\t\t���α���%d����Ϣ\n", count);
	else printf("\t\t\t\t\t������д��\n");
	printf("�������������");
}
void FacilitiesManagement(Linkedlist* h) {
	
	faci_init_f(h);
	start_F();
	while (1) {
		menu_F();
		printf("\t\t\t\t����ѡ��(1~6): ");
		int choose;
		scanf("%d", &choose);
		switch (choose) {
		case 1:print_info_f(h); break;
		case 2:search_f(h); break;
		case 3:update_f(h); break;
		case 4:add_f(h); break;
		case 5:delete_f(h); break;
		case 6:flush_f(h); return;
		default:break;
		}
	}
}
void start_F() {
	system("cls");
	system("color 3F");
	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t************************��ӭʹ�����ǵ�������ʩ����ϵͳ**************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t\t      ������: ������\n");
	printf("\t\t\t\t\t      ����ʱ��: 2022��\n\n\n\n");
	printf("\t\t\t\t\t      ***�����������***\n");
	_getch();
}
void menu_F() {
	system("cls");
	system("color 3F");
	printf("\n\n");
	printf("\t\t\t\t��������������������ϵͳ����������������\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t********��ʩ�˵�********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  �鿴���г�����Ϣ      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  �����ض�����      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  �޸ĳ�����Ϣ      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  ����������Ϣ      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  ɾ��������Ϣ      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t6  ���沢�˳�      \n\n");
}
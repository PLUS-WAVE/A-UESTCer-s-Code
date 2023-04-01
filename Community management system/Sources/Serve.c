#define _CRT_SECURE_NO_WARNINGS 1
#include"Serve.h"
#include"HouseManagement.h"
#include"VIP.h"
#include"FacilitiesManagement.h"
#include"WorkerManagement.h"
#include"struct.h"
void rewriteserve(Service* H, list* hs)
{

	Service* p;
	p = H->next;
	FILE* fp;
	if ((fp = fopen(file1, "w+")) == NULL) {
		printf("\n\n��ʧ��\n");
		exit(0);
	}
	while (p != NULL) {
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
			&p->name, &p->tel, &p->house, &p->needs, &p->acc, &p->worker, &p->ok);

		p = p->next;
	}
	fclose(fp);
}
void writeserve(Service* H)
{
	Service* p;
	p = H->next;
	FILE* fp;
	if ((fp = fopen(file1, "a")) == NULL) {
		printf("\n\n��ʧ��\n");
		exit(0);
	}
	while (p != NULL) {
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
			&p->name, &p->tel, &p->house, &p->needs, &p->acc, &p->worker, &p->ok);

		p = p->next;
	}
	fclose(fp);
}
void deleteLink_S(Service* H) {
	Service* p2;
	while (H->next != NULL)
	{
		p2 = H->next;
		H->next = p2->next;
		free(p2);
	}
}
void link_creat_head_S(Service* H, Service* p) {
	Service* p_move_w = H->next;
	if (H->next == NULL) {
		H->next = p;
		p->next = NULL;
	}
	else
	{
		while (p_move_w->next != NULL) {
			p_move_w = p_move_w->next;
		}
		p_move_w->next = p;
		p->next = NULL;
	}
}
void readserve(Service* H)
{


	if (H->next != NULL) {
		deleteLink_S(H);
	}

	FILE* fp_IsEmpty;
	if ((fp_IsEmpty = fopen(file1, "r")) == NULL)
	{
		printf("�Ҳ����ļ�\n");
		exit(0);
	}
	if (fgetc(fp_IsEmpty) == EOF) {
		return;
	}
	fclose(fp_IsEmpty);

	FILE* fp;
	Service* p;
	p = H->next;
	if ((fp = fopen(file1, "r")) == NULL)
	{
		printf("�Ҳ����ļ�\n");
		exit(0);
	}


	while (feof(fp) == 0)
	{
		p = (Service*)malloc(sizeof(Service));
		fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n",
			&p->name, &p->tel, &p->house, &p->needs, &p->acc, &p->worker, &p->ok);
		link_creat_head_S(H, p);
	}


}
void addserve(Service* H, list* hs, VIP* p_head, char ID[ID_LEN])
{
	readVIPs(p_head);
	VIP* p_move = p_head->next;
	while (strcmp(p_move->ID, ID)) {
		p_move = p_move->next;
		if (p_move == NULL) {
			printf("\nδ�ҵ���Ϣ\n");
			return;
		}
	}
	system("cls");
	printf("\n\n-----------------------��������ҪԤԼ�ķ�������-----------------------\n");
	//�����������

	Service* p = (Service*)malloc(sizeof(Service));


	strcpy(p->name, p_move->name);
	strcpy(p->tel, p_move->Phone);
	strcpy(p->house, p_move->HouseID);
	strcpy(p->acc, "������");
	strcpy(p->worker, "��");
	strcpy(p->ok, "no");
	scanf("%s", p->needs);

	link_creat_head_S(H, p);
	
	//д���ļ�
	writeserve(H);

	strcpy(p_move->Service, "���������");
	saveVIPs(p_head);
	printf("\n\n��������ɹ��������ĵȴ����񱻽���\n");

	printf("\n�����������");
	_getch();
	deleteLink_S(H);
}
void changeserve(Service* H, list* hs, VIP* p_head)
{
	printf("\n\n��������������������");
	char Name[20];
	scanf("%s", Name);

	printf("\n\n������������������");
	char need[20];
	scanf("%s", need);

	readVIPs(p_head);
	VIP* p_move = p_head->next;
	while (strcmp(p_move->name, Name)) {
		p_move = p_move->next;
		if (p_move == NULL) {
			printf("\nδ�ҵ��û�\n");
			return;
		}
	}

	readserve(H);
	Service* p = H->next;
	while (strcmp(p->name, Name) || strcmp(p->needs, need)) {
		p = p->next;
		if (p == NULL) {
			printf("�˼�¼������!");
			return;
		}
	}
	
	printf("\n��Ҫ���������Ϣ���£�\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("|����:%s\n", p->name);
	printf("|��ϵ��ʽ:%s\n", p->tel);
	printf("|����:%s\n", p->house);
	printf("|����:%s\n", p->needs);
	printf("|����״̬���ѽ���/�����ܣ�:%s\n", p->acc);
	printf("|ָ����Ա:%s\n", p->worker);
	printf("|������(yes/no):%s\n", p->ok);
	printf("\n----------------------------------------------------------------------------------------------------------------------");
L11:printf("\n\n����·�����Ϣ:\n");
	printf("\n����״̬���ѽ���/�����ܣ���");
	scanf("%s", p->acc);
	printf("\n\nָ����Ա��");
	scanf("%s", p->worker);
	
	readuser(hs);
	if (hs->num <= 0)
	{
		printf("\n\nĿǰ�����ڹ�����Ա��\n");
		return;
	}
	node_w* p_worker = hs->head->next;
	if (!strcmp(p_worker->date.name, p->worker))//�׽��
	{
		strcpy(p_worker->date.object, p->name);
		strcpy(p->worker, p_worker->date.name);
		rewriteuser(hs);
		rewriteserve(H, hs);
		printf("������......");
		strcpy(p_move->Service, "���ܷ�����");
		saveVIPs(p_head);
		goto L9;
	}
	while (p_worker != NULL && (strcmp(p_worker->date.name, p->worker)))//���׽ڵ�
		p_worker = p_worker->next;
	if (p_worker == NULL)
	{
		printf("�����ڸù�����Ա��\n���������룺"); goto L11;
	}

	if (strcmp(p_worker->date.object,"��"))
	{
		printf("�ù�����Ա�ѱ�ָ�ɣ�\n���������룺"); goto L11;
	}
	else
	{
		strcpy(p_worker->date.object, p->name);
		strcpy(p->worker, p_worker->date.name);
		rewriteuser(hs);
		rewriteserve(H, hs);
		strcpy(p_move->Service, "���ܷ�����");
		saveVIPs(p_head);

		printf("������......");
	}
	
L9:printf("\n\n--------1.����--------\n--------2.�˳�--------\n");
L7:printf("�����룺");
	int k = 0;
	scanf("%d", &k);
	switch (k)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("�����䣡\n"); goto L7;
	}

	deleteLink_S(H);

}
void deleteserve(Service* p, Service* H)
{
	if (p->next == NULL)
	{
		H->next = p->next;
		free(p);
	}

	else if (p->next != NULL) {
		Service* tmp;
		tmp = p->next;
		strcpy(p->name, tmp->name);
		strcpy(p->acc, tmp->acc);
		strcpy(p->house, tmp->house);
		strcpy(p->needs, tmp->needs);
		strcpy(p->ok, tmp->ok);
		strcpy(p->tel, tmp->tel);
		strcpy(p->worker, tmp->worker);
		p->next = tmp->next;
		free(tmp);
	}

}
void serveM(Service* H, list* hs, VIP* p_head) {

	readserve(H);
	showserve(H);
	changeserve(H, hs, p_head);
	deleteLink_S(H);

}
void endserve(Service* H, list* hs, VIP* p_head, char ID[ID_LEN]) {

	readVIPs(p_head);
	VIP* p_move = p_head->next;
	while (strcmp(p_move->ID, ID)) {
		p_move = p_move->next;
		if (p_move == NULL) {
			printf("\nδ�ҵ���Ϣ\n");
			return;
		}
	}

	readserve(H);

	Service* p1 = (Service*)malloc(sizeof(Service));
	p1 = H->next;

	system("cls");
	printf("-----------------------------------------------����������-----------------------------------------------\n");
	printf("����\t\t��ϵ��ʽ\t����\t\t����\t\t\t\t�Ƿ����\tָ����Ա\t������\n");
	while (p1 != NULL) {
		if (!strcmp(p1->name, p_move->name)) {

			printf("%s\t\t", p1->name);
			printf("%s\t", p1->tel);
			printf("%s\t\t", p1->house);
			/*printf("%s\t\t", p1->needs);*/
			if (strlen(p1->needs) < 8)
				printf("%s\t\t\t\t", p1->needs);
			else if (strlen(p1->needs) >= 8)
				printf("%s\t\t\t", p1->needs);
			printf("%s\t\t", p1->acc);
			printf("%s\t\t", p1->worker);
			printf("%s\t\t", p1->ok);
			printf("\n");

		}
		p1 = p1->next;
	}


	printf("\n\n��������Ҫ��������Ĺ�����Ա������\n");
	char Name[20];
	scanf("%s", Name);
	Service* p;
	p = H->next;
	while (p != NULL && (strcmp(p->worker, Name)))
		p = p->next;
	if (p == NULL)
		printf("�˶��󲻴���!");
	else {
		printf("\n��Ϣ���£�\n");
		printf("------------------------------------\n");
		printf("����:%s\n", p->name);
		printf("��ϵ��ʽ:%s\n", p->tel);
		printf("����:%s\n", p->house);
		printf("����:%s\n", p->needs);
		printf("����״̬���ѽ���/�����ܣ�:%s\n", p->acc);
		printf("ָ����Ա:%s\n", p->worker);
		printf("������(yes/no):%s\n", p->ok);
		printf("\n------------------------------------");
		printf("\n\n���������״̬:\n");
		printf("��������\n");
		scanf("%s", p->ok);
		if (!(strcmp(p->ok, "no")) && !(strcmp(p->acc, "�ѽ���")))
			printf("������......");
		else if (!(strcmp(p->ok, "no") && strcmp(p->acc, "δ����")))
			printf("��������У������ĵȴ���");
		else if (!(strcmp(p->ok, "yes")))
		{
			printf("��������ɣ�");
			deleteserve(p, H);
			rewriteserve(H, hs);
			strcpy(p_move->Service, "��");
			saveVIPs(p_head);
			printf("\n\n--------1.����--------\n--------2.����--------\n");
		L10:printf("�����룺");
			int j = 0;
			scanf("%d", &j);
			switch (j)
			{
			case 1:return;
				break;
			case 2:endserve(H, hs, p_head, ID);
				break;
			default:printf("�����䣡\n"); goto L10;
			}
		}
	}

	deleteLink_S(H);

}
void showserve(Service* H)
{

	readserve(H);
	Service* p = (Service*)malloc(sizeof(Service));
	p = H->next;

	system("cls");
	printf("-----------------------------------------------����������-----------------------------------------------\n");
	printf("����\t\t��ϵ��ʽ\t����\t\t����\t\t\t\t�Ƿ����\tָ����Ա\t������\n\n");
	while (p) {
		printf("%s\t\t", p->name);
		printf("%s\t", p->tel);
		printf("%s\t\t", p->house);
		/*printf("%s\t\t\t", p->needs);*/
		if (strlen(p->needs) < 8)
			printf("%s\t\t\t\t", p->needs);
		else if (strlen(p->needs) >= 8)
			printf("%s\t\t\t", p->needs);
		printf("%s\t\t", p->acc);
		printf("%s\t\t", p->worker);
		printf("%s\t\t", p->ok);
		printf("\n");
		p = p->next;
	}
	deleteLink_S(H);

}




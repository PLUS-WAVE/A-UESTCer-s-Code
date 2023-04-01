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
		printf("\n\n打开失败\n");
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
		printf("\n\n打开失败\n");
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
		printf("找不到文件\n");
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
		printf("找不到文件\n");
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
			printf("\n未找到信息\n");
			return;
		}
	}
	system("cls");
	printf("\n\n-----------------------请输入需要预约的服务内容-----------------------\n");
	//向链表中添加

	Service* p = (Service*)malloc(sizeof(Service));


	strcpy(p->name, p_move->name);
	strcpy(p->tel, p_move->Phone);
	strcpy(p->house, p_move->HouseID);
	strcpy(p->acc, "待接受");
	strcpy(p->worker, "无");
	strcpy(p->ok, "no");
	scanf("%s", p->needs);

	link_creat_head_S(H, p);
	
	//写入文件
	writeserve(H);

	strcpy(p_move->Service, "申请服务中");
	saveVIPs(p_head);
	printf("\n\n服务申请成功，请耐心等待服务被接受\n");

	printf("\n按任意键返回");
	_getch();
	deleteLink_S(H);
}
void changeserve(Service* H, list* hs, VIP* p_head)
{
	printf("\n\n请输入申请服务的姓名：");
	char Name[20];
	scanf("%s", Name);

	printf("\n\n请输入申请服务的需求：");
	char need[20];
	scanf("%s", need);

	readVIPs(p_head);
	VIP* p_move = p_head->next;
	while (strcmp(p_move->name, Name)) {
		p_move = p_move->next;
		if (p_move == NULL) {
			printf("\n未找到用户\n");
			return;
		}
	}

	readserve(H);
	Service* p = H->next;
	while (strcmp(p->name, Name) || strcmp(p->needs, need)) {
		p = p->next;
		if (p == NULL) {
			printf("此记录不存在!");
			return;
		}
	}
	
	printf("\n需要服务对象信息如下：\n");
	printf("----------------------------------------------------------------------------------------------------------------------\n");
	printf("|姓名:%s\n", p->name);
	printf("|联系方式:%s\n", p->tel);
	printf("|房号:%s\n", p->house);
	printf("|需求:%s\n", p->needs);
	printf("|接收状态（已接受/待接受）:%s\n", p->acc);
	printf("|指派人员:%s\n", p->worker);
	printf("|完成情况(yes/no):%s\n", p->ok);
	printf("\n----------------------------------------------------------------------------------------------------------------------");
L11:printf("\n\n请更新服务信息:\n");
	printf("\n接收状态（已接受/待接受）：");
	scanf("%s", p->acc);
	printf("\n\n指派人员：");
	scanf("%s", p->worker);
	
	readuser(hs);
	if (hs->num <= 0)
	{
		printf("\n\n目前不存在工作人员！\n");
		return;
	}
	node_w* p_worker = hs->head->next;
	if (!strcmp(p_worker->date.name, p->worker))//首结点
	{
		strcpy(p_worker->date.object, p->name);
		strcpy(p->worker, p_worker->date.name);
		rewriteuser(hs);
		rewriteserve(H, hs);
		printf("服务中......");
		strcpy(p_move->Service, "接受服务中");
		saveVIPs(p_head);
		goto L9;
	}
	while (p_worker != NULL && (strcmp(p_worker->date.name, p->worker)))//非首节点
		p_worker = p_worker->next;
	if (p_worker == NULL)
	{
		printf("不存在该工作人员！\n请重新输入："); goto L11;
	}

	if (strcmp(p_worker->date.object,"无"))
	{
		printf("该工作人员已被指派！\n请重新输入："); goto L11;
	}
	else
	{
		strcpy(p_worker->date.object, p->name);
		strcpy(p->worker, p_worker->date.name);
		rewriteuser(hs);
		rewriteserve(H, hs);
		strcpy(p_move->Service, "接受服务中");
		saveVIPs(p_head);

		printf("服务中......");
	}
	
L9:printf("\n\n--------1.返回--------\n--------2.退出--------\n");
L7:printf("请输入：");
	int k = 0;
	scanf("%d", &k);
	switch (k)
	{
	case 1:return;
		break;
	case 2:exit(1);
		break;
	default:printf("嫑乱输！\n"); goto L7;
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
			printf("\n未找到信息\n");
			return;
		}
	}

	readserve(H);

	Service* p1 = (Service*)malloc(sizeof(Service));
	p1 = H->next;

	system("cls");
	printf("-----------------------------------------------服务工作详情-----------------------------------------------\n");
	printf("姓名\t\t联系方式\t房号\t\t需求\t\t\t\t是否接受\t指派人员\t完成情况\n");
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


	printf("\n\n请输入需要结束服务的工作人员姓名：\n");
	char Name[20];
	scanf("%s", Name);
	Service* p;
	p = H->next;
	while (p != NULL && (strcmp(p->worker, Name)))
		p = p->next;
	if (p == NULL)
		printf("此对象不存在!");
	else {
		printf("\n信息如下：\n");
		printf("------------------------------------\n");
		printf("姓名:%s\n", p->name);
		printf("联系方式:%s\n", p->tel);
		printf("房号:%s\n", p->house);
		printf("需求:%s\n", p->needs);
		printf("接收状态（已接受/待接受）:%s\n", p->acc);
		printf("指派人员:%s\n", p->worker);
		printf("完成情况(yes/no):%s\n", p->ok);
		printf("\n------------------------------------");
		printf("\n\n请输入服务状态:\n");
		printf("完成情况：\n");
		scanf("%s", p->ok);
		if (!(strcmp(p->ok, "no")) && !(strcmp(p->acc, "已接受")))
			printf("服务中......");
		else if (!(strcmp(p->ok, "no") && strcmp(p->acc, "未接受")))
			printf("服务接收中，请耐心等待。");
		else if (!(strcmp(p->ok, "yes")))
		{
			printf("服务已完成！");
			deleteserve(p, H);
			rewriteserve(H, hs);
			strcpy(p_move->Service, "无");
			saveVIPs(p_head);
			printf("\n\n--------1.返回--------\n--------2.继续--------\n");
		L10:printf("请输入：");
			int j = 0;
			scanf("%d", &j);
			switch (j)
			{
			case 1:return;
				break;
			case 2:endserve(H, hs, p_head, ID);
				break;
			default:printf("嫑乱输！\n"); goto L10;
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
	printf("-----------------------------------------------服务工作详情-----------------------------------------------\n");
	printf("姓名\t\t联系方式\t房号\t\t需求\t\t\t\t是否接受\t指派人员\t完成情况\n\n");
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




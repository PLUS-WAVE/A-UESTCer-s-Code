#define _CRT_SECURE_NO_WARNINGS 1
#include"HouseManagement.h"
#include"VIP.h"
#include"FacilitiesManagement.h"
#include"WorkerManagement.h"
#include"Serve.h"
void BuyHouse(VIP* p_head, char ID[ID_LEN]) {
	system("cls");
	int choise;
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********菜单**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  进入买房     \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  返回菜单     \n\n");
	printf("\n\t\t\t\t请选择功能：");
	scanf("%d", &choise);
	if (choise == 1) {
		buy_H(p_head, ID);
	}
	else {
		return;
	}
}
void UseFacility(Linkedlist* h, VIP* p_head, char ID[ID_LEN]) {
	system("cls");
	int choise;
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********菜单**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  设施打卡     \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  设施签退     \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  返回菜单     \n\n");
	printf("\n\t\t\t\t请选择功能：");
	scanf("%d", &choise);
	if (choise == 1) {
		record_f(h, p_head, ID);
	}
	else if (choise == 2) {
		leave_f(h, p_head, ID);
	}
	else if (choise == 3) {
		return;
	}
	else {
		UseFacility(h, p_head, ID);
	}
	
}
void UseService(Service* H, list* hs, VIP* p_head, char ID[ID_LEN]) {
	system("cls");
	int choise;
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********菜单**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  服务预约     \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  结束服务     \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  返回菜单     \n\n");
	printf("\n\t\t\t\t请选择功能：");
	scanf("%d", &choise);
	if (choise == 1) {
		addserve(H, hs, p_head, ID);
	}
	else if (choise == 2) {
		endserve(H, hs, p_head, ID);
	}
	else if (choise == 3) {
		return;
	}
	else {
		UseService(H, hs, p_head, ID);
	}
}
void VIPManagement(VIP* p_head) {
	system("cls");
	system("color 3F");

	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t************************欢迎使用我们的社区会员管理系统**************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t\t      制作人: 王嘉伟，阿依木拉提，张楷奇\n");
	printf("\t\t\t\t\t      制作时间: 2022年\n\n\n\n");
	printf("\t\t\t\t\t      ***按任意键进入***\n");
	_getch();
	system("cls");
	do
	{
		printf("\n\n");
		printf("\t\t\t\t————————管理系统————————\n\n");
		printf("\t\t\t\t\t************************\n");
		printf("\t\t\t\t\t********会员菜单********\n");
		printf("\t\t\t\t\t************************\n\n");
		printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  新建VIP      \n\n");
		printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  显示VIP      \n\n");
		printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  删除VIP      \n\n");
		printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  修改VIP      \n\n");
		printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  退出      \n\n");
		printf("\n\t\t\t\t请选择功能：");
		int choise = 0;
		scanf("%d", &choise);

		switch (choise)
		{
		case 1:
			system("cls");
			createVIP(p_head);
			system("cls");
			break;
		case 2:
			system("cls");
			viewVIPs(p_head);
			_getch();
			system("cls");
			break;
		case 3:
			system("cls");
			delVIPs(p_head);
			_getch();
			system("cls");
			break;
		case 4:
			system("cls");
			modifyVIPs(p_head);
			_getch();
			system("cls");
			break;
		case 5:
			system("cls");
			return;
		default:
			system("cls");
			break;
		}
	} while (1);
}
void RegisterVIP(VIP* p_head) {
	system("cls");
	VIP* p_new = NULL;
	int amount = 0;
	p_new = (VIP*)malloc(sizeof(VIP));
	printf("-------------------------------------");
	printf("\n\n请输入VIP的姓名：");
	scanf("%s", p_new->name);
	printf("\n\n请输入VIP的ID：");
	scanf("%s", p_new->ID);
	printf("\n\n请输入VIP的密码：");
	scanf("%s", p_new->password);
	printf("\n\n请输入VIP的电话：");
	scanf("%s", p_new->Phone);
	strcpy(p_new->HouseID, "无");
	strcpy(p_new->facility, "无");
	strcpy(p_new->Service, "无");
	link_creat_head(p_head, p_new);
	saveVIPsAdd(p_head);
	printf("注册成功");
}
void createVIP(VIP* p_head) {
	VIP* p_new = NULL;
	int amount = 0;
	printf("\n\n请输入录入的VIP的人数：");
	scanf("%d", &amount);
	for (int i = 0; i < amount; i++) {
		p_new = (VIP*)malloc(sizeof(VIP));
		printf("-------------------------------------");
		printf("\n\n请输入VIP的姓名：");
		scanf("%s", p_new->name);
		printf("\n\n请输入VIP的ID：");
		scanf("%s", p_new->ID);
		printf("\n\n请输入VIP的密码：");
		scanf("%s", p_new->password);
		printf("\n\n请输入VIP的电话：");
		scanf("%s", p_new->Phone);
		printf("\n\n请输入VIP的房屋ID：");
		scanf("%s", p_new->HouseID);
		printf("\n\n请输入VIP的使用的设施：");
		scanf("%s", p_new->facility);
		printf("\n\n请输入VIP的使用的服务：");
		scanf("%s", p_new->Service);

		link_creat_head(p_head, p_new);
	}
	saveVIPsAdd(p_head);
}
void deleteLink(VIP* p_head) {
	VIP* p_move;
	while (p_head->next != NULL) {
		p_move = p_head->next;
		p_head->next = p_move->next;
		free(p_move);
	}
}
void link_creat_head(VIP* p_head, VIP* p_new) {
	VIP* p_move =  p_head->next;
	if (p_head->next == NULL) {
		p_head->next = p_new;
		p_new->next = NULL;
	}
	else
	{
		while (p_move->next != NULL) {
			p_move = p_move->next;
		}
		p_move->next = p_new;
		p_new->next = NULL;
	}
}
void saveVIPs(VIP* p_head) {
	VIP* p_move;
	p_move = p_head->next;
	FILE* fp;
	if ((fp = fopen(File_V, "w+")) == NULL) {
		printf("\n\n打开失败\n");
		exit(0);
	}
	while (p_move != NULL) {
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t", 
			p_move->name, p_move->ID, p_move->password, p_move->Phone, p_move->HouseID, p_move->Service, p_move->facility);
		p_move = p_move->next;
	}
	fclose(fp);
}
void saveVIPsAdd(VIP* p_head) {
	VIP* p_move;
	p_move = p_head->next;
	FILE* fp;
	if ((fp = fopen(File_V, "a")) == NULL) {
		printf("\n\n打开失败\n");
		exit(0);
	}
	while (p_move != NULL) {
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t", 
			p_move->name, p_move->ID, p_move->password, p_move->Phone, p_move->HouseID, p_move->Service, p_move->facility);
		p_move = p_move->next;
	}
	fclose(fp);
}
void readVIPs(VIP* p_head) {
	if (p_head->next != NULL) {
		deleteLink(p_head);
	}
	FILE* fp;
	VIP* p_new;
	p_new = p_head->next;
	if ((fp = fopen(File_V, "r")) == NULL)
	{
		printf("找不到文件\n");
		exit(0);
	}
	while (feof(fp) == 0) {
		p_new = (VIP*)malloc(sizeof(VIP));
		fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t",
			&p_new->name, &p_new->ID, &p_new->password, &p_new->Phone, &p_new->HouseID, &p_new->Service, &p_new->facility);
		link_creat_head(p_head, p_new);
	}
	
}
void viewVIPs(VIP* p_head) {
	readVIPs(p_head);
	if (p_head->next == NULL) {
		printf("链表为空！");
		return;
	}
	system("cls");
	printf("\n目前用户信息如下\n\n");
	printf("---------------------------------------------------------------------------------------------------");
	printf("\n|   姓名   |   ID   |     密码     |    房屋   |      电话       |    服务状态     |    设施状态   |\n");
	printf("---------------------------------------------------------------------------------------------------");
	VIP* p_move = p_head->next;
	while (p_move != NULL) {
		printf("\n|   %-7s|   %-5s|   %-11s|     %-6s|  %-15s|    %-13s|    %-11s|",
			p_move->name, p_move->ID, p_move->password, p_move->HouseID, p_move->Phone, p_move->Service, p_move->facility);
		printf("\n---------------------------------------------------------------------------------------------------");
		p_move = p_move->next;
	}
	deleteLink(p_head);
	
}
void delVIPs(VIP* p_head) {

	viewVIPs(p_head);

	readVIPs(p_head);
	if (p_head->next == NULL) {
		printf("链表为空！");
		return;
	}
	

	VIP* p_move = p_head->next;
	VIP* temp = NULL;

	printf("\n\n请输入要删除的VIP的ID:");
	char DelID[10];
	scanf("%s", &DelID);
	if (!(strcmp(p_move->ID, DelID))) {
		p_head->next = p_move->next;
		free(p_move);
	}
	else
	{
		while (strcmp(p_move->ID, DelID)) {
			temp = p_move;
			p_move = p_move->next;
			if (p_move == NULL) {
				printf("\n未找到信息\n");
				return;
			}
		}
		temp->next = p_move->next;
		free(p_move);
	}

	printf("\n\n删除成功\n");
	saveVIPs(p_head);
	deleteLink(p_head);
}
void modifyVIPs(VIP* p_head) {

	viewVIPs(p_head);

	readVIPs(p_head);
	if (p_head->next == NULL) {
		printf("链表为空！");
		return;
	}

	VIP* p_move;
	p_move = p_head->next;

	printf("\n\n请输入要修改的VIP的ID：");
	char DelID[10];
	scanf("%s", DelID);
	while (strcmp(p_move->ID, DelID)) {
		p_move = p_move->next;
		if (p_move == NULL) {
			printf("\n未找到信息\n");
			return;
		}
	}

	do
	{
		printf("\n\n输入1修改姓名，2修改ID，3修改密码，4修改电话，5修改房屋ID，6修改服务状态，7修改设施状态");
		printf("\n\n请选择需要修改的内容：");
		int choise1;
		scanf("%d", &choise1);
		switch (choise1)
		{
		case 1:
			printf("\n\n请输入VIP的姓名：");
			scanf("%s", p_move->name);
			break;
		case 2:
			printf("\n\n请输入VIP的ID：");
			scanf("%s", p_move->ID);
			break;
		case 3:
			printf("\n\n请输入VIP的密码：");
			scanf("%s", p_move->password);
			break;
		case 4:
			printf("\n\n请输入VIP的电话：");
			scanf("%s", p_move->Phone);
			break;
		case 5:
			printf("\n\n请输入VIP的房屋ID：");
			scanf("%s", p_move->HouseID);
			break;
		case 6:
			printf("\n\n请输入VIP的服务状态：");
			scanf("%s", p_move->Service);
			break;
		case 7:
			printf("\n\n请输入VIP的设施状态：");
			scanf("%s", p_move->facility);
			break;
		default:
			break;
		}
		printf("\n\n修改完成的信息如下");
		printf("\n\n---------------------------------------------------------------------------------------------------");
		printf("\n|   姓名   |   ID   |     密码     |    房屋   |      电话       |    服务状态     |    设施状态   |\n");
		printf("---------------------------------------------------------------------------------------------------");
		printf("\n|   %-7s|   %-5s|   %-11s|     %-6s|  %-15s|    %-13s|    %-11s|",
			p_move->name, p_move->ID, p_move->password, p_move->HouseID, p_move->Phone, p_move->Service, p_move->facility);
		printf("\n---------------------------------------------------------------------------------------------------");
		
		printf("\n\n继续修改请按1，返回请按0\n");
		int choise2;
		scanf("%d", &choise2);
		switch (choise2)
		{
		case 1:
			break;
		default:
			saveVIPs(p_head);
			return;
		}
	} while (1);
	
}

#define _CRT_SECURE_NO_WARNINGS 1
#include"struct.h"
#include"HouseManagement.h"
#include"VIP.h"
#include"FacilitiesManagement.h"
#include"WorkerManagement.h"
#include"Screen.h"
void WelcomeScreen() {
	system("cls");
	system("color 3F");
	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t************************��ӭʹ�����ǵ�������������ϵͳ**************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t\t      ������: ��һС��\n");
	printf("\t\t\t\t\t      ����ʱ��: 2022��\n\n\n\n");
	printf("\t\t\t\t\t      ***�����������***\n");
	_getch();
}
void StartScreen(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********���**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t\t��2�˳�\n\n");
	printf("\t\t\t\t\t��1����VIPϵͳ\n\n");
	printf("\t\t\t\t\t��0�������Աϵͳ\n\n\n");
	printf("\t\t\t\t\t��ѡ���ܣ�");
	int choise;
	scanf("%d", &choise);
	if (choise == 1) {
		welcomeScreen_U();
		EnterScreen_U(h, p_head, hs, H);
	}
	else if (choise == 0) {
		welcomeScreen_M();
		SignInScreen_M();
		menuScreen_M(h, p_head, hs, H);
	}
	else if (choise == 2) {
		exit(0);
	}
	else {
		StartScreen(h, p_head, hs, H);
	}
}
void welcomeScreen_M() {
	system("cls");
	system("color 3F");
	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t******************************��ӭʹ�ù���Աϵͳ********************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");

	printf("\t\t\t\t\t      ***�����������***\n");
	_getch();
}
void welcomeScreen_U() {
	system("cls");
	system("color 3F");
	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t********************************��ӭʹ��VIPϵͳ*********************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");

	printf("\t\t\t\t\t      ***�����������***\n");
	_getch();
}
void EnterScreen_U(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t����������������VIPϵͳ����������������\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t********��ӭ��VIP*******\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t0  ע��      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  ��¼      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  ����      \n\n");
	printf("\n\t\t\t\t��ѡ���ܣ�");
	int choise;
	scanf("%d", &choise);
	if (choise == 1) {
		SignInScreen_U(h, p_head, hs, H);
	}
	else if (choise == 0) {
		RegisterVIP(p_head);
		EnterScreen_U(h, p_head, hs, H);
	}
	else if (choise == 2) {
		return;
	}
	else {
		EnterScreen_U(h, p_head, hs, H);
	}
}
void SignInScreen_U(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	readVIPs(p_head);
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********��¼**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t\t������VIP��ID(����0�˳�): ");
	char ID[10];
	char password[10];
	scanf("%s", &ID);
	if (!strcmp(ID, "0")) {
		exit(0);
	}
	VIP* p_move;
	p_move = p_head->next;
	while (strcmp(p_move->ID, ID)) {
		p_move = p_move->next;
		if (p_move == NULL) {
			printf("\n\t\t\t\t\tδ�ҵ���Ϣ\n");
			exit(0);
		}
	}
	printf("\n\n\t\t\t\t\t����������:");
	scanf("%s", &password);
	if (!strcmp(password, p_move->password)) {
		menuScreen_U(h, p_head, ID, hs, H);
	}
	else {
		printf("\n\n\t\t\t\t\t������󣡣���");
		SignInScreen_U(h, p_head, hs, H);
	}

	return;
}
void menuScreen_U(Linkedlist* h, VIP* p_head, char ID[ID_LEN], list* hs, Service* H) {
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t\t**-----------��ӭ��, �𾴵�VIP-----------**\n");
	Sleep(2000);

	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t*********���˵�*********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  ���ݹ���      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  ��ʩ��/ǩ��      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  ����ԤԼ/����      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  �˳�      \n\n");
	printf("\n\t\t\t\t��ѡ���ܣ�");
	int n;
	scanf_s("%d", &n);
	do {
		switch (n) {
		case 1:
			BuyHouse(p_head, ID);
			break;
		case 2:
			UseFacility(h, p_head, ID);
			break;
		case 3:
			UseService(H, hs, p_head, ID);
			break;
		case 4:
			Quit(h, p_head, hs, H);
			break;
		default:
			break;
		}
		Sleep(500);
		menuScreen_U(h, p_head, ID, hs, H);
	} while (1);
}
void SignInScreen_M() {
	int name, code;
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********��¼**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t\t�������û���(����0�˳�):");
	scanf_s("%d", &name);
	if (name == 0) {
		exit(0);
	}
	printf("\n\n\t\t\t\t\t����������:");
	scanf_s("%d", &code);
	if (name == 1 && code == 888888) {
		printf("\n\n\n");
		printf("\t\t\t\t**-----------��ӭ��, �𾴵Ĺ���Ա-----------**\n");
		Sleep(2000);
		system("cls");
		return;
	}
	else {
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t****----�û����������������������----****\n");
		Sleep(1000);
		system("cls");
		SignInScreen_M();
	}
}
void menuScreen_M(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t*********���˵�*********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  ��Ա����      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  ���ݹ���      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  ��ʩ����      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  ������Ա����      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  �˳�      \n\n");
	printf("\n\t\t\t\t��ѡ���ܣ�");
	int n;
	scanf_s("%d", &n);
	do {
		switch (n) {
		case 1:
			VIPManagement(p_head);
			break;
		case 2:
			HouseManagement(h, p_head, hs, H);
			break;
		case 3:
			FacilitiesManagement(h);
			break;
		case 4:
			WorkerManagement(hs, H, p_head);
			break;
		case 5:
			Quit(h, p_head, hs, H);
			break;
		default:
			break;
		}

		menuScreen_M(h, p_head, hs, H);
	} while (1);
}
void Quit(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t\t*******------*��һС���л����ʹ��*------*******\n");
	Sleep(1500);
	system("cls");
	StartScreen(h, p_head, hs, H);
}

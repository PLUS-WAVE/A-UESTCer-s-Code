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
	printf("\t\t************************欢迎使用我们的阳光社区管理系统**************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t\t      制作人: 第一小组\n");
	printf("\t\t\t\t\t      制作时间: 2022年\n\n\n\n");
	printf("\t\t\t\t\t      ***按任意键进入***\n");
	_getch();
}
void StartScreen(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t**********入口**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t\t按2退出\n\n");
	printf("\t\t\t\t\t按1进入VIP系统\n\n");
	printf("\t\t\t\t\t按0进入管理员系统\n\n\n");
	printf("\t\t\t\t\t请选择功能：");
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
	printf("\t\t******************************欢迎使用管理员系统********************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");

	printf("\t\t\t\t\t      ***按任意键进入***\n");
	_getch();
}
void welcomeScreen_U() {
	system("cls");
	system("color 3F");
	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t********************************欢迎使用VIP系统*********************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");

	printf("\t\t\t\t\t      ***按任意键进入***\n");
	_getch();
}
void EnterScreen_U(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t————————VIP系统————————\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t********欢迎您VIP*******\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t0  注册      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  登录      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  返回      \n\n");
	printf("\n\t\t\t\t请选择功能：");
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
	printf("\t\t\t\t\t**********登录**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t\t请输入VIP的ID(输入0退出): ");
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
			printf("\n\t\t\t\t\t未找到信息\n");
			exit(0);
		}
	}
	printf("\n\n\t\t\t\t\t请输入密码:");
	scanf("%s", &password);
	if (!strcmp(password, p_move->password)) {
		menuScreen_U(h, p_head, ID, hs, H);
	}
	else {
		printf("\n\n\t\t\t\t\t密码错误！！！");
		SignInScreen_U(h, p_head, hs, H);
	}

	return;
}
void menuScreen_U(Linkedlist* h, VIP* p_head, char ID[ID_LEN], list* hs, Service* H) {
	system("cls");
	printf("\n\n\n");
	printf("\t\t\t\t**-----------欢迎您, 尊敬的VIP-----------**\n");
	Sleep(2000);

	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t*********主菜单*********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  房屋购买      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  设施打卡/签退      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  服务预约/结束      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  退出      \n\n");
	printf("\n\t\t\t\t请选择功能：");
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
	printf("\t\t\t\t\t**********登录**********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t\t请输入用户名(输入0退出):");
	scanf_s("%d", &name);
	if (name == 0) {
		exit(0);
	}
	printf("\n\n\t\t\t\t\t请输入密码:");
	scanf_s("%d", &code);
	if (name == 1 && code == 888888) {
		printf("\n\n\n");
		printf("\t\t\t\t**-----------欢迎您, 尊敬的管理员-----------**\n");
		Sleep(2000);
		system("cls");
		return;
	}
	else {
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t\t\t****----用户名或密码错误，请重新输入----****\n");
		Sleep(1000);
		system("cls");
		SignInScreen_M();
	}
}
void menuScreen_M(Linkedlist* h, VIP* p_head, list* hs, Service* H) {
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t*********主菜单*********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  会员管理      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  房屋管理      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  设施管理      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  工作人员管理      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  退出      \n\n");
	printf("\n\t\t\t\t请选择功能：");
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
	printf("\t\t\t\t*******------*第一小组感谢您的使用*------*******\n");
	Sleep(1500);
	system("cls");
	StartScreen(h, p_head, hs, H);
}

#define _CRT_SECURE_NO_WARNINGS 1
#include"struct.h"
#include"HouseManagement.h"
#include"VIP.h"
#include"FacilitiesManagement.h"
#include"WorkerManagement.h"
#include"Screen.h"


int main()
{
	system("cls");
	system("color 3F");
	
	//VIP�����ͷ
	VIP* p_head = (VIP*)malloc(sizeof(VIP));
	p_head->next = NULL;
	
	//��ʩ�����ͷ
	Linkedlist linkedlist;
	Linkedlist* h;
	h = &linkedlist;
	h->head = NULL;
	h->current_num = 0;
	
	//������Ա�����ͷ
	list* hs = (list*)malloc(sizeof(list));
	hs->head = NULL;

	//������Ϣ
	Service* H = (Service*)malloc(sizeof(Service));
	H->next = NULL;


	WelcomeScreen();
	StartScreen(h, p_head, hs, H);

	return 0;
}


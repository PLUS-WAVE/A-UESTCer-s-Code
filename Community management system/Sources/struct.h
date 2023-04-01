#ifndef _STRUCT_H
#define _STRUCT_H
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<conio.h>
#define NAME_LEN 50
#define CON_LEN 20
#define DRCTR_LEN 50
#define ID_LEN 10
#define File_V "D:\\Code\\Projects\\test2\\save\\VIPs\\VIPs.txt"
#define file1 "D:\\Code\\Projects\\test2\\save\\Service\\Service.txt"
#define file "D:\\Code\\Projects\\test2\\save\\Service\\Worker.txt"
#define File_F "D:\\Code\\Projects\\test2\\save\\Facilities\\Facilities.txt"
#define File_H1 "D:\\Code\\Projects\\test2\\save\\House\\Apartment.txt"
#define File_H2 "D:\\Code\\Projects\\test2\\save\\House\\CommonHouse.txt"
#define File_H3 "D:\\Code\\Projects\\test2\\save\\House\\Villa.txt"


//VIP
typedef struct VIP   
{
	char name[30];
	char ID[10];
	char password[10];
	char Phone[20];
	char HouseID[10];
	char Service[30];
	char facility[30];
	struct VIP* next;
}VIP;

//房屋
struct House  
{
	char type[20];      //房屋类型
	char number[10];         //房屋编号 
	char sold[10];      //是否售出
	int price;         //售卖价格
	char BelongTo[30];     //房屋归属
} house[120];


//设施
typedef struct Recreational_facilities {
	char name[NAME_LEN];
	char condition[CON_LEN];
	int now; int error;
	char director[DRCTR_LEN];
}Recreational_facilities;

typedef struct node {
	Recreational_facilities recreational_facilities;
	struct node* next;
}Node;

typedef struct Linkedlist {
	Node* head;
	int current_num;
}Linkedlist;


//工作人员
typedef struct user
{
	char name[20];
	char job[20];
	char object[20];
}date;



typedef struct node_w
{
	struct user date;
	struct node_w* next;
}node_w;



typedef struct
{
	node_w* head;
	int num;
}list;

//服务结构
typedef struct Service
{
	char name[200];
	char tel[200];
	char house[200];
	char needs[500];
	char acc[100];
	char worker[200];
	char ok[100];
	struct Service* next;
}Service;


#endif

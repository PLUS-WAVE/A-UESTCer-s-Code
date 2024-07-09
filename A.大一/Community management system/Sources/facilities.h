#ifndef _FACILITY_H
#define _FACILITY_H

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define NAME_LEN 50
#define CON_LEN 20
#define DRCTR_LEN 50
typedef struct {
	char name[NAME_LEN];
	char condition[CON_LEN];
	int now; int error;
	char director[DRCTR_LEN];
}Recreational_facilities;
typedef struct node {
	Recreational_facilities recreational_facilities;
	struct node* next;
}Node;
typedef struct {
	Node* head;
	int current_num;
}Linkedlist;
void faci_init_f(Linkedlist* h);
void print_info_f(Linkedlist* h);
void search_f(Linkedlist* h);
void update_f(Linkedlist* h);
void delete_f(Linkedlist* h);
void add_f(Linkedlist* h);
void record_f(Linkedlist* h, VIP* p_head, char ID[ID_LEN]);
void leave_f(Linkedlist* h, VIP* p_head, char ID[ID_LEN]);
void flush_f(Linkedlist* h);
#endif

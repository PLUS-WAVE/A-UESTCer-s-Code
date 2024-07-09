#ifndef _HOUSE_H
#define _HOUSE_H
#include"struct.h"
void HouseManagement(Linkedlist* h, VIP* p_head, list* hs, Service* H);
void start_H();
void menu_H();
void input_H();
void save_H(int a);
int read_H(int type);
void search_H();
void SreachByNum_H();
void view_H();
void modify_H();
void del_H();
void add_H();
void buy_H(VIP * p_head, char ID[10]);
#endif



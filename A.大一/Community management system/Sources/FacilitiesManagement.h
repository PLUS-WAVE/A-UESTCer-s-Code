#ifndef _FACILITY_H
#define _FACILITY_H
#include"struct.h"
void menu_F();
void start_F();
void FacilitiesManagement(Linkedlist* h);
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

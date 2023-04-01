#ifndef _WORKER_H
#define _WORKER_H
#include"struct.h"
void start_W();
void menu_W(Service* H);
void readuser(list* hs);
void showuser(list* hs);
void adduser(list* hs);
void writeuser(list* hs);
void rewriteuser(list* hs);
void print_one_w(node_w* p);
void deleteuser(list* hs);
void change(list* hs);
void WorkerManagement(list* hs, Service* H, VIP* p_head);
void serveM(Service* H, list* hs, VIP* p_head);
#endif


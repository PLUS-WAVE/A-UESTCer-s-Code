#ifndef _SERVE_H
#define _SERVE_H
#include"struct.h"
void addserve(Service* H, list* hs, VIP* p_head, char ID[ID_LEN]);
void changeserve(Service* H, list* hs, VIP* p_head);
void deleteserve(Service* p, Service* H);
void serveM(Service* H, list* hs, VIP* p_head);
void endserve(Service* H, list* hs, VIP* p_head, char ID[ID_LEN]);
void link_creat_head_S(Service* H, Service* p);
void deleteLink_S(Service* H);
void writeserve(Service* H);
void readserve(Service* H);
void showserve(Service* H);
void rewriteserve(Service* H, list* hs);
#endif

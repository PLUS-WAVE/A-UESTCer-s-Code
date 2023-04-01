#ifndef _VIP_H
#define _VIP_H
#include"struct.h"
void link_creat_head(VIP* p_head, VIP* p_new);
void deleteLink(VIP* p_head);
void RegisterVIP(VIP* p_head);
void createVIP(VIP* p_head);
void viewVIPs(VIP* p_head);
void saveVIPs(VIP* p_head);
void saveVIPsAdd(VIP* p_head);
void readVIPs(VIP* p_head);
void delVIPs(VIP* p_head);
void modifyVIPs(VIP* p_haed);
void VIPManagement(VIP* p_head);
void BuyHouse(VIP* p_head, char ID[ID_LEN]);
void UseFacility(Linkedlist* h, VIP* p_head, char ID[ID_LEN]);
void UseService(Service* H, list* hs, VIP* p_head, char ID[ID_LEN]);
#endif

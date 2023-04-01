#ifndef _SCREEN_H
#define _SCREEN_H
#include"struct.h"
void WelcomeScreen();
void StartScreen(Linkedlist* h, VIP* p_head, list* hs, Service* H);
void welcomeScreen_M();
void menuScreen_M(Linkedlist* h, VIP* p_head, list* hs, Service* H);
void SignInScreen_M();
void Quit(Linkedlist* h, VIP* p_head, list* hs, Service* H);
void welcomeScreen_U();
void EnterScreen_U(Linkedlist* h, VIP* p_head, list* hs, Service* H);
void SignInScreen_U(Linkedlist* h, VIP* p_head, list* hs, Service* H);
void menuScreen_U(Linkedlist* h, VIP* p_head, char ID[ID_LEN], list* hs, Service* H);
#endif
#define _CRT_SECURE_NO_WARNINGS 1
#include"FacilitiesManagement.h"
#include"VIP.h"
void faci_init_f(Linkedlist *h) {
	if (h->head != NULL) {
		Node* p = h->head;
		while (h->head) {
			p = h->head;
			h->head = h->head->next;
			free(p);
		}
	}
	
	system("cls");
	FILE* fp;  
	if ((fp = fopen(File_F, "r")) == NULL) {
		if (((fp = fopen(File_F, "w")) == NULL))
			printf("\t\t\t\t\t创建文件失败\n");
	}	//打包后文件路径需修改
	else {
		Recreational_facilities tmp;
		Node* node;
		h->head = NULL;
		h->current_num = 0;
		while (!feof(fp)) {
			fscanf(fp, "%s\t%s\t%d\t%d\t%s", tmp.name, tmp.condition,&tmp.now,&tmp.error, tmp.director);
			node = (Node*)malloc(sizeof(Node));
			node->recreational_facilities = tmp;
			node->next = h->head;
			h->head = node;
			h->current_num += 1;
		}
	}
	fclose(fp);
	printf("\t\t\t\t\t初始化完成\n");
}
void print_info_f(Linkedlist *h) {
	system("cls");
	if (h->current_num <= 0)
		printf("\t\t\t\t\t链表为空\n");
	Node* p = h->head;
	while (p) {
		printf("\n\n\t\t\t名称；%s\t", p->recreational_facilities.name);
		printf("状态；%s(%d/%d)\t", p->recreational_facilities.condition, p->recreational_facilities.now, p->recreational_facilities.error);
		printf("负责人；%s\n", p->recreational_facilities.director);
		p = p->next;
	}
	printf("\n\n\t\t\t输入任意键返回");
	_getch();
}
void search_f(Linkedlist *h) {
	system("cls");
	printf("\t\t\t\t\t选择查找方式（1按名称查找，2按状态查找,-1取消）：");
	int way;
	scanf("%d", &way);
	if (way == -1)
		return;
	else if (way == 1) 
	{printf("\t\t\t\t\t输入想搜索的场馆名称（-1取消）:");
		char name[NAME_LEN];
		scanf("%s", name);
		if (!strcmp(name, "-1"))
			return;
		Node* p = h->head;
		while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
			p = p->next;
		if (p == NULL)
			printf("\t\t\t\t\t场馆不存在\n");
		else {
			printf("\t\t\t名称；%s\t", p->recreational_facilities.name);
			printf("状态；%s(%d/%d)\t", p->recreational_facilities.condition, p->recreational_facilities.now, p->recreational_facilities.error);
			printf("负责人；%s\n", p->recreational_facilities.director);
		}
	}
	else if (way == 2) {
		printf("\t\t\t\t\t输入想搜索场馆的状态（-1取消）：");
		char condition[CON_LEN];
		scanf("%s", condition);
		if (!strcmp(condition, "-1"))
			return;
		Node* q = h->head;
		while (q != NULL) {
			if (!strcmp(q->recreational_facilities.condition, condition)) {
				printf("\t\t\t名称；%s\t", q->recreational_facilities.name);
				printf("状态；%s(%d/%d)\t", q->recreational_facilities.condition, q->recreational_facilities.now, q->recreational_facilities.error);
				printf("负责人；%s\n", q->recreational_facilities.director);
			}
			q = q->next;
		}
	}
	printf("\n\n\n\t\t\t输入任意键返回");
	_getch();
}
void update_f(Linkedlist *h) {
	system("cls");
	printf("\t\t\t\t\t输入想要修改信息的场馆名称（-1取消）:");
	char name[NAME_LEN];
	scanf("%s", name);
	if (!strcmp(name, "-1"))
		return;
	Node* p = h->head;
	while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
		p = p->next;
	if (p == NULL)
		printf("\t\t\t\t\t场馆不存在\n");
	else {
		printf("\t\t\t\t\t输入场馆信息\n");
		printf("\t\t\t\t\t名称\n");
		scanf("%s", p->recreational_facilities.name);
		printf("\t\t\t\t\t状态及理想容纳人数（以空格间隔）\n");
		scanf("%s %d", p->recreational_facilities.condition,&p->recreational_facilities.error);
		printf("\t\t\t\t\t负责人\n");
		scanf("%s", p->recreational_facilities.director);
		printf("\t\t\t\t\t场馆信息更新完成\n");
	}
	printf("输入任意键返回");
	_getch();
}
void delete_f(Linkedlist *h) {
	system("cls");
	if (h->current_num <= 0) {
		printf("\t\t\t\t\t链表为空\n");
		return;
	}
	printf("\t\t\t\t\t输入要删除的场馆名称（-1取消）:");
	char name[NAME_LEN];
	scanf("%s", name);
	if (!strcmp(name, "-1"))
		return;
	Node* p = h->head;
	if (!strcmp(p->recreational_facilities.name, name)) {
		h->head = p->next;
		free(p);
		return;
	}
	while (p->next != NULL && (strcmp(p->next->recreational_facilities.name, name)))
		p = p->next;
	if (p->next == NULL)
		printf("\t\t\t\t\t场馆不存在");
	else {
		printf("\t\t\t\t\t名称；%s\n", p->next->recreational_facilities.name);
		printf("\t\t\t\t\t状态；%s\n", p->next->recreational_facilities.condition);
		printf("\t\t\t\t\t负责人；%s\n", p->next->recreational_facilities.director);
		printf("\t\t\t\t\t删除场馆？(Y/N)\n");
		char answer[10];
		scanf("%s", &answer);
		if (!strcmp(answer,"Y")) {
			Node* tmp;
			tmp = p->next;
			p->next = tmp->next;
			free(tmp);
			h->current_num -= 1;
		}
		else return;
	}
	printf("输入任意键返回");
	_getch();
}
void add_f(Linkedlist *h) {
	system("cls");
	Node* p = (Node*)malloc(sizeof(Node)), * tmp;
	Recreational_facilities recreational_facilities;
	printf("\t\t\t\t\t输入场馆信息\n");
	printf("\t\t\t\t\t输入名称：");
	scanf("%s", recreational_facilities.name);
	printf("\t\t\t\t\t输入状态及理想容纳人数（以空格间隔）：");
	scanf("%s %d", recreational_facilities.condition, &recreational_facilities.error);
	recreational_facilities.now = 0;
	printf("\t\t\t\t\t输入负责人：");
	scanf("%s", recreational_facilities.director);
	p->recreational_facilities = recreational_facilities;
	tmp = h->head;
	while (tmp->next)
		tmp = tmp->next;;
	tmp->next = p;
	p->next = NULL;
	h->current_num += 1;
	printf("\t\t\t\t\t新建成功\n");
	printf("输入任意键返回");
	_getch();
}
void record_f(Linkedlist* h,VIP* p_head,char ID[ID_LEN]) {
	faci_init_f(h);
	system("cls");
	printf("\t\t\t\t\t请输入待使用的场馆名称（-1取消）:");
	char name[NAME_LEN];
	VIP* tmp = p_head->next;
	scanf("%s", name);
	if (!strcmp(name, "-1"))
		return;
	Node* p = h->head;
	while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
		p = p->next;
	if (p == NULL) {
		printf("\t\t\t\t\t场馆不存在\n");
		return;
	}	
	else {
		if (!strcmp(p->recreational_facilities.condition, "维护中"))
			printf("\t\t\t\t\t抱歉，该场馆正在维护");
		else if (!strcmp(p->recreational_facilities.condition, "正常"))
		{
			printf("\t\t\t\t\t欢迎使用"); p->recreational_facilities.now++;
			while (tmp != NULL && strcmp(tmp->ID, ID))
				tmp = tmp->next;
			strcpy(tmp->facility, name);
		}
		else if (!strcmp(p->recreational_facilities.condition, "拥挤"))
		{
			printf("\t\t\t\t\t该场馆人数较多，可能影响使用体验，是否继续？(Y/N)");
			char answer; scanf("%c", &answer);
			if (answer == 'Y' || answer == 'y') {
				printf("\t\t\t\t\t欢迎使用\n"); p->recreational_facilities.now++;
				while (tmp != NULL && strcmp(tmp->ID, ID))
					tmp = tmp->next;
				strcpy(tmp->facility, name);
				
			}
		}
	}
	if (p->recreational_facilities.now > p->recreational_facilities.error)
		strcpy(p->recreational_facilities.condition, "拥挤");

	printf("输入任意键返回");
	saveVIPs(p_head);

	_getch();

	flush_f(h);
}
void leave_f(Linkedlist* h,VIP* p_head, char ID[ID_LEN]) {
	faci_init_f(h);
	system("cls");
	VIP* tmp = p_head->next;
	while (tmp != NULL && strcmp(tmp->ID, ID))
		tmp = tmp->next;
	if (!strcmp(tmp->facility, "无"))
	{
		printf("当前未使用场馆"); return;
	}
	char name[NAME_LEN];
	strcpy(name, tmp->facility);
	Node* p = h->head;
	while (p != NULL && (strcmp(p->recreational_facilities.name, name)))
		p = p->next;
		printf("\t\t\t\t\t退场成功\n");
		p->recreational_facilities.now--;
	if (p->recreational_facilities.now <= p->recreational_facilities.error)
		strcpy(p->recreational_facilities.condition, "正常");
	strcpy(tmp->facility, "无");
	printf("输入任意键返回");
	saveVIPs(p_head);

	_getch();
	flush_f(h);
}
void flush_f(Linkedlist *h) {
	system("cls");
	FILE* fp;
	Node* p = h->head;
	int count = 0;
	if ((fp = fopen(File_F, "w")) == NULL) {
		printf("\t\t\t\t\t打开文件失败\n");
			return;
	}
	while (p) {
		fprintf(fp, "%s\t", p->recreational_facilities.name);
		fprintf(fp, "%s\t%d\t%d\t", p->recreational_facilities.condition, p->recreational_facilities.now, p->recreational_facilities.error);
		if (p->next == NULL)
			fprintf(fp, "%s", p->recreational_facilities.director);
		else fprintf(fp, "%s\n", p->recreational_facilities.director);
		p = p->next;
		count++;
	}
	fclose(fp);

	while (h->head) {
		p = h->head;
		h->head = h->head->next;
		free(p);
	}

	if (count > 0)
		printf("\t\t\t\t\t本次保存%d条信息\n", count);
	else printf("\t\t\t\t\t无数据写入\n");
	printf("输入任意键返回");
}
void FacilitiesManagement(Linkedlist* h) {
	
	faci_init_f(h);
	start_F();
	while (1) {
		menu_F();
		printf("\t\t\t\t功能选择(1~6): ");
		int choose;
		scanf("%d", &choose);
		switch (choose) {
		case 1:print_info_f(h); break;
		case 2:search_f(h); break;
		case 3:update_f(h); break;
		case 4:add_f(h); break;
		case 5:delete_f(h); break;
		case 6:flush_f(h); return;
		default:break;
		}
	}
}
void start_F() {
	system("cls");
	system("color 3F");
	printf("\n\n\n\n\n\n");
	printf("\t\t********************************************************************************\n");
	printf("\n");
	printf("\t\t************************欢迎使用我们的社区设施管理系统**************************");
	printf("\n\n");
	printf("\t\t********************************************************************************\n\n\n\n\n");
	printf("\t\t\t\t\t      制作人: 杨镇宇\n");
	printf("\t\t\t\t\t      制作时间: 2022年\n\n\n\n");
	printf("\t\t\t\t\t      ***按任意键进入***\n");
	_getch();
}
void menu_F() {
	system("cls");
	system("color 3F");
	printf("\n\n");
	printf("\t\t\t\t————————管理系统————————\n\n");
	printf("\t\t\t\t\t************************\n");
	printf("\t\t\t\t\t********设施菜单********\n");
	printf("\t\t\t\t\t************************\n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t1  查看所有场馆信息      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t2  查找特定场馆      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t3  修改场馆信息      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t4  新增场馆信息      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t5  删除场馆信息      \n\n");
	printf("\t\t\t\t>>>>>>>>>>>>>>>>>>>>>>>>>\t6  保存并退出      \n\n");
}
#include<iostream>
#include<stdlib.h>
using namespace std;

// ��ʽ��� 
typedef struct LNode{
	int data;
	LNode *next;
}LNode, *LinkList;


//��������
void ListTraverse(LinkList list) {
	LNode *p = list->next;
	int i = 1;
	while(p) {
		printf("��%dλֵΪ��%d\n", i, p->data); 
		p = p->next;
		i++;
	}
}
		
//��ʼ�����Ա� 
bool InitList(LinkList &list, int num) {
	if(list = (LNode*)malloc(sizeof(LNode))) {
		list->data = 0;
		list->next = NULL;
		LNode *temp, *p=list;
		for(int i = 1; i <= num; i++) {
			temp = (LNode*)malloc(sizeof(LNode));
			temp->data = i;
			p->next = temp;
			p = temp;
			list->data++;
		}
		p->next = NULL;
		printf("================��ʽ����ǰ===============\n");
		ListTraverse(list);
		return true;
	}
	else return false;
}

//�������Ա�
bool DestroyList(LinkList &list) {
	if(list) {
		LNode *temp, *p = list->next;
		while(p) {
			temp = p;
			p = p->next;
			free(temp);
		}
		free(list);
		return true;
	}
	else return false;
}

//�����Ա�ĵ�iλ����eֵ
bool ListInsert(LinkList &list, int i, LNode *e) {
	if(!list) return false;			//�жϱ��Ƿ�Ϊ��  
	if(i <= 0 || i > list->data+1) return false;		//�ж�i�Ƿ���Ч
	
	LNode *last = list, *p = list->next;
	int j = 1;
	while(p && j++!=i) {							//�Ż�
		last = p;
		p = last->next;
	}
	last->next = e;
	e->next = p;
	list->data++;
	return true;
}


int main() { 
	LinkList list;//˳���ͷ 
	
	int num;
	printf("��������ʽ��Ԫ�صĸ�����");
	scanf("%d", &num);
	
	if(InitList(list, num)) printf("��ʼ����ʽ��ɹ�\n");
	else printf("��ʼ����ʽ��ʧ��\n");
	
	LNode *next = NULL, *p = list->next;
	list->data = 0;
	list->next = NULL;
	while(p) {
		next = p->next;
		if(!ListInsert(list, 1, p)) {
			printf("��ֵʧ��\n");
			break;
		}
		p = next;
	}
	
	printf("================��ʽ���ú�===============\n");
	ListTraverse(list);
	
	if(DestroyList(list)) printf("�������ٳɹ�\n");
	else printf("��������ʧ��\n"); 
}

#include<stdio.h>
#include<stdlib.h>

typedef struct LNode {
	int data;
	LNode *next;
}LNode, *LinkList;

// ��������
void ListTraverse(LinkList list) {
	printf("\n================����==============\n");
	LNode *p = list->next;
	int i = 1;
	while(p) {
		printf("��%dλֵΪ��%d\n", i, p->data); 
		p = p->next;
		i++;
	}
	printf("====================================\n\n");
}

// �����ź���������в���һ����� 
void InsertList(LinkList &list, LNode *temp) {
	LNode *prior = list, *p = list->next;
	while(p && p->data < temp->data) {
		prior = p;
		p = p->next;
	}
	prior->next = temp;
	temp->next = p;
} 

int main() {
	
	int n = 0;
	printf("���������Ա�����ݸ�����");
	scanf("%d", &n);
	
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->data = 0;
	list->next = NULL;
	
	// �������� 
	LNode *temp, *p = list;
	printf("�������������Ա��е����ݣ�\n");
	int i = 0;
	while(i<n) {
		temp = (LNode*)malloc(sizeof(LNode));
		scanf("%d", &temp->data);
		p->next = temp;
		p = p->next;
		i++;
	} 
	p->next = NULL;
	ListTraverse(list);
	
	// ����ȡ����㲢��������������� 
	p = list->next;
	list->next = NULL;
	while(p) {
		temp = p;
		p = p->next;
		InsertList(list, temp);
	}
	ListTraverse(list);
	
	//�������� 
	p = list;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
}





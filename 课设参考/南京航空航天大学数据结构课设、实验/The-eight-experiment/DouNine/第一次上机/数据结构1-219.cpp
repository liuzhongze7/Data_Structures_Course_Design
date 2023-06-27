#include<stdio.h>
#include<stdlib.h>

typedef struct LNode {
	int data;
	LNode *next;
}LNode, *LinkList;

//��������
void ListTraverse(LinkList list) {
	printf("\n================����==============\n");
	LNode *p = list->next;
	int i = 1;
	while(p) {
		printf("��%dλֵΪ��%d\n", i, p->data); 
		p = p->next;
		i++;
	}
}
		
int main() {
	// ��ʼ������ 
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->data = 0;
	list->next = NULL;
	LNode *p, *temp;
	p = list;
	int i = 0;
	while(i<20) {
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = 2*i+4;
		p->next = temp;
		p = p->next;
		i++;
	}
	p->next = NULL;
	ListTraverse(list);
	
	// �������½� 
	int mink = 0, maxk = 0;
	printf("\n��ֱ�����mink��maxk:");
	scanf("%d%d", &mink, &maxk);
	
	// ��ʼɾ��Ԫ��
	LNode *prior;
	prior = list;
	p = list->next;
	while(p && p->data<=mink) {
		prior = p;
		p = p->next;
	} 
	temp = prior;
	while(p && p->data<maxk) {
		prior = p;
		p = p->next;
		free(prior);
	}
	temp->next = p;
	ListTraverse(list);
	
	//�������� 
	p = list;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
}

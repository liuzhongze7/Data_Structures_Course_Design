#include<stdio.h>
#include"LinkList.h"
bool reverseList_L(LinkList &L){
	LNode *p,*q,*s,*head,*end;
	p=L;
	q=(LNode*)malloc(sizeof(LNode));
	head=q;
	while(L->next!=NULL){
		p=L->next;
		s=L;
	while(p->next!=NULL){
		s=p;
		p=p->next;
	}
	s->next=NULL;
	q->next=p;
	q=q->next;
	}
	L=head;
	return OK;
}
int main(){
	LinkList l;
	int i=0,n=0,flag=0;
	char c,temp;

	printf("��������������������ӵ�ֵ������\n"); 
	scanf("%d",&n);
	InitList_L(l,n);
	getchar();
	printf("����������¼���ֵ\n"); 
	for(i=0;i<n;i++){
		scanf("%c",&c);
		ListCreat(l,i,c);	
		getchar();
	}
	ListTraverse(l);
	printf("��������������ֵ����λ��\n");
	scanf("%c%d",&c,&i);
	ListInsert(l,i,c);
	ListTraverse(l);
	printf("����������õ�ֵ��λ��\n");
	scanf("%d",&i);
	flag=GetElem_L(l,i-1,c);
	if(flag==-1) printf("����λ�ô���\n");
	else
	printf("%c\n",c); 
	if(PriorElem_L(l,c,temp)==1)
	printf("����ǰһ��ֵ��%c\n",temp);
	if(NextElem_L(l,c,temp))
	printf("���ĺ�һ��ֵ��%c\n",temp);
	printf("������������ҵ�ֵ\n");
	getchar();
	scanf("%c",&c);
	i=LocateElem(l,c);
	printf("������ҵ�ֵ��λ����%d\n",i);
	printf("�������Ԫ\n");
	reverseList_L(l);
	ListTraverse(l); 
	
}

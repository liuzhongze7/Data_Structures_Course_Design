#include<stdio.h>
#include"list.h"
bool reverseList(Sqlist &L){
	char p;
	int i=0;
	for(i=0;i<L.length/2;i++){
		p=L.elem[i];
		L.elem[i]=L.elem[L.length-i-1];
		L.elem[L.length-i-1]=p;
	}
	return OK;
}
int main(){
	Sqlist l;
	int n=0,i=0;
	char c,ch;
	printf("����һ��˳���\n");
	InitList_Sq(l);
	printf("���������������ֵ������\n");
	scanf("%d",&n);
	printf("����������Ҫ�����ֵ\n");
	getchar();
	while(i<n){
		scanf("%c",&l.elem[i]);
		i++;
		l.length++;
		getchar();
	}
	ListTraverse(l); 
	printf("�ö��еĳ�����%d",ListLength(l));
	printf("��������������ֵ,�Լ�����λ��\n");
	scanf("%c%d",&c,&i);
	ListInsert(l,i,c);
	ListTraverse(l);
	printf("����������ɾ����ֵ��λ��\n");
	scanf("%d",&i);
	ListDelete(l,i,c);
	printf("ɾ����ֵ��%c",c);
	printf("������λ��\n");
	scanf("%d",&i);
	GetElem(l,i,c);
	printf("��λ�������ֵ��%c",c);
	PriorElem(l,c,ch);
	printf("��λ��ǰ���ֵ��%c",ch);
	NextElem(l,c,ch); 
	printf("��λ�ú����ֵ��%c",ch);
	printf("����������Ҫ���ҵ�ֵ\n");
	getchar();
	scanf("%c",&c);
	i=LocateElem(l,c); 
	printf("��λ����%d�����Ϊ0��ʾ��ֵ������",i);
	cout<<"�������Ԫ\n";
	reverseList(l);
	ListTraverse(l); 
	
}

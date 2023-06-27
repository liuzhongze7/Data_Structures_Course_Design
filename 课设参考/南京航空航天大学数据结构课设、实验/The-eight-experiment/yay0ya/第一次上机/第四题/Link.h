#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
typedef struct LNode{
	int id;//��ʾѧ�������
	int lenghts;//���еĳ���
	struct LNode *next; //ָ����һ����� 
}LNode,*LinkList;
int InitLink(LinkList &l,int i){
	LNode *p; int j=0;
	l=NULL;
	if(i>MAXSIZE) return ERROR;
	for(j=0;j<i+1;j++){
		p=(LNode*)malloc(sizeof(LNode));
		p->next=l;
		l=p;
	}
	p=l;
	for(j=0;j<i+1;j++){
		p->id=j;
		p->lenghts=i;
		p=p->next;
	}
	return OK;
}
int Moveafter(LinkList &l,int i,int temp)//i��ʾѧ������ţ�temp��ʾѧ��������ƶ��Ĳ���
{
	LNode *p,*q,*r;
	int j=0,count=0; 
	p=l;
	for(j=0;j<l->lenghts;j++){
		if(p->id==i){
			break;//���Ѿ��ҵ���ѧ�� 
		}
		q=p;//��q����¼pָ���ǰһ��ָ�� 
		p=p->next;//���idֵ��ƥ�䣬���ָ������ƶ���ֱ���ҵ���ѧ�� 
	}
	r=p;//��ָ��r����ʾѧ�� 
	count=j;//��count����¼�������ѧ�������ĸ�λ��
	if(count>=l->lenghts){
		return ERROR;//���ѧ����λ�ó��ȴ��ڵ��ڶ��еĳ��ȣ�˵�����������ѧ�������� 
	}
	q->next=r->next;//qָ��ָ���ƶ�ͬѧ��ǰ��һ��ͬѧ��rָ��ָ���ѧ��
		 //ǰ���ͬѧԽ��rָ�룬ָ��r�����һ��ͬѧ 
	if(l->lenghts-(count+temp)<=0)//����ƶ���������ѧ�����ڵ�λ���Ѿ������򵽴����ĩβʱ
	{
		p=l->next;
		//��ѧ���ƶ���������ĩβ
		 for(j=0;j<(l->lenghts-2);j++){
		 	p=p->next;
		 }//pָ���ƶ�����ĩβ��
		 p->next=r;//p��ĩβ��ͬѧ����r����p���� 
	 	 r->next=NULL;
	 }
	 else{//����ƶ��Ĳ������������һ��λ�õ�ʱ�� 
		p=l->next;	 	
		for(j=0;j<count+temp-1;j++){
	 		q=p;
	 		p=p->next;
		 }
		 q->next=r;
		 r->next=p;//�����ָ�����λ�ò���ͬѧr 
	 }
	 return OK;
 } 
 int Movebefore(LinkList &l,int i,int temp)//��i��ʾѧ�����ڵ���ţ�temp��ʾ��ǰ�ƶ��Ĳ���
 {
 	LNode *p,*q,*r;
	int j=0,count=0; 
	p=l->next;
	for(j=0;j<l->lenghts;j++){
		if(p->id==i){
			break;//���Ѿ��ҵ���ѧ�� 
		}
		q=p;//��q����¼pָ���ǰһ��ָ�� 
		p=p->next;//���idֵ��ƥ�䣬���ָ������ƶ���ֱ���ҵ���ѧ�� 
	}
	r=p;//��ָ��r����ʾѧ�� 
	count=j;//��count����¼�������ѧ�������ĸ�λ��
	if(count>=l->lenghts){
		return ERROR;//���ѧ����λ�ó��ȴ��ڵ��ڶ��еĳ��ȣ�˵�����������ѧ�������� 
	}
	q->next=r->next;//qָ��ָ���ƶ�ͬѧ��ǰ��һ��ͬѧ��rָ��ָ���ѧ��
		 //ǰ���ͬѧԽ��rָ�룬ָ��r�����һ��ͬѧ 
	if(count+temp<=0){
		//����ƶ�tempʱ��ʹѧ���ﵽͷ�������߳���ͷ��
		r->next=l->next;
		l->next=r;//�����ͬѧ��Ϊ�����ͷ�� 
	}
	else {
		p=l->next;
		//���û�е�������ͷ��
		for(j=0;j<count+temp;j++){
			q=p;
			p=p->next;
		}
		q->next=r;
		r->next=p;//������˲嵽ǰ�� 
	}
	return OK;
  } 

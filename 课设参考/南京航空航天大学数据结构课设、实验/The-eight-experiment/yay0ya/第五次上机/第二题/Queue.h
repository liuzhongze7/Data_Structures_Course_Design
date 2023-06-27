#include<stdlib.h>
#include"Stack.h"

typedef BiTNode* QElemType;
typedef int Status; 
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
	QueuePtr front;//��ͷָ��
	QueuePtr rear;//��βָ�� 
}LinkQueue;
//---�����������㷨���������֣�--- 
Status InitQueue(LinkQueue &Q){
	//����һ���ն���Q
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(0);
	Q.front->next=NULL;
	return 1; 
} 
Status DestroyQueue(LinkQueue &Q){
	//���ٶ���Q
	while(Q.front){
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return 1; 
}
Status ClearQueue(LinkQueue &Q){
	//��Q��Ϊ�ն���
	QNode *p;
	p=Q.front; 
	while(Q.front!=Q.rear){
		p=p->next;
		Q.front=p;
		free(p); 
	} 
	Q.front->next=NULL;
	return 1;
}
Status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear) return 1;
	else return 0;
}
int QueueLength(LinkQueue Q){
	QNode *p;
	int i=0;
	if(Q.front==Q.rear) return 0;
	p=Q.front->next;
	while(p!=Q.rear){
		i++;
		p=p->next;
	} 
	i++;
	return i;
}
Status GetHead(LinkQueue Q,QElemType &e){
	//�����в�Ϊ�գ�����e����Q�Ķ�ͷԪ�أ�������1�����򷵻�0
	if(Q.front==Q.rear) return 0;
	e=Q.front->next->data;
	return 1; 
}
Status EnQueue(LinkQueue &Q,QElemType e){
	//����Ԫ��eΪQ���µĶ�βԪ��
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(0);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return 1; 
}
Status DeQueue(LinkQueue &Q,QElemType &e){
	//�����в�Ϊ�գ���ɾ��Q�Ķ�ͷԪ�ء���e������ֵ��������OK��
	//���򷵻�ERROR��
	QueuePtr p,q;
	p=Q.front->next;
	if(Q.front==Q.rear) return 0;
	Q.front->next=p->next;
	e=p->data;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return 1;
}
void visited(int q){
	cout<<q<<" ";
}


#include <stdio.h>
#include <stdlib.h>

typedef struct QNode{
	int data;
	struct QNode *next;
}*QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

void InitQueue(LinkQueue &Q) {
	Q.front = (QNode*)malloc(sizeof(QNode));
	Q.rear = Q.front;
}

void ClearQueue(LinkQueue &Q) {
	QNode *p = Q.front->next, *temp;
	while(p) {
		temp = p;
		p = p->next;
		free(temp);
	}
	Q.rear = Q.front;
}

void DestoryQueue(LinkQueue &Q) {
	ClearQueue(Q);
	free(Q.front);
}

bool QueueEmpty(LinkQueue Q) {
	if(Q.front == Q.rear) return true;
	else return false;
}

int QueueLength(LinkQueue Q) {
	QNode *p = Q.front->next;
	int account = 0;
	while(p) {
		account++;
		p = p->next;
	}
	return account;
}

bool GetHead(LinkQueue Q,int &e) {
	QNode *p = Q.front->next;
	if(p) {
		e = p->data;
		return true;
	}
	else return false;
}

void EnQueue(LinkQueue &Q,int e) {
	QNode *temp = (QNode*)malloc(sizeof(QNode));
	temp->data = e;
	temp->next = NULL;
	Q.rear->next = temp;
	Q.rear = temp;
}

bool DeQueue(LinkQueue &Q,int &e) {
	QNode *p = Q.front->next;
	Q.front->next = p->next;
	e = p->data;
	free(p);
}

void QueueTraverse(LinkQueue Q) {
	printf("=================��������==================\n");
	QNode *p = Q.front->next;
	while(p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n===========================================\n");
}

int main() {
	LinkQueue Q;
	InitQueue(Q);
	printf("���г�ʼ���ɹ�\n");
	
	for(int i=0; i<10; i++) {
		EnQueue(Q, i);
	}
	QueueTraverse(Q);
	
	int temp = 0;
	DeQueue(Q, temp);
	printf("ɾȥ��ͷԪ��\n");
	QueueTraverse(Q);
	
	GetHead(Q, temp);
	printf("����ͷԪ��Ϊ��%d\n", temp);
	
	EnQueue(Q, temp);
	printf("�ڶ�β����%d\n", temp);
	QueueTraverse(Q);
	
	DestoryQueue(Q);
	printf("�������ٳɹ�\n");
} 





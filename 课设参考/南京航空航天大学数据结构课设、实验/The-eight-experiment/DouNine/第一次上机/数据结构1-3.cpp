#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// ˳���ͷ 
typedef struct {
	int *head;
	int length;
}SqList;

// ָ���� 
typedef struct LNode {
	int data;
	struct LNode *next;
}LNode,*LinkList;


int main() {
	
	int m = 0, n = 0; 
	printf("����������n��m:\n");
	scanf("%d%d", &n, &m); 
	
	printf("\n============˳��ṹʵ��==============\n");
	// ����˳������
	SqList List;
	List.head = (int*)malloc(sizeof(int) * n);
	List.length = n;
	 
	// ��ʼ������ֵ 
	int i = 0;
	while(i < n) {
		List.head[i] = i+1;
		i++;
	}
	
	// ��������Ԫ�س��� 
	i = 0;
	int num = 1;
	while(List.length) {
		if(List.head[i%n]) {
			if(num%m == 0) {
				printf("��%d�ų���\n", List.head[i%n]);
				List.head[i%n] = 0;
				List.length--;
			}
			num++;
		}
		i++;
	}
	
	// �ͷſռ� 
	free(List.head);
	
	
	
	printf("\n============��ʽ�ṹʵ��==============\n");
	// �������� 
	LinkList head;
	// ����ʹ�õ���ָ�� 
	LNode *p, *temp;
	// ����ͷ��� 
	head = (LNode*)malloc(sizeof(LNode));
	head->data = n;
	
	// ����������Ϊÿ�����������ֵ 
	p = head;
	i = 0;
	while(i++ < n) {
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = i;
		p->next = temp;
		p = p->next;
	}
	p->next = NULL;
	
	// ��������Ԫ�س���
	num = 1;
	LNode *last = head;
	while(head->data) {
		if(!(last->next)) last = head;
		p = last->next;
		if(num%m == 0) {
			printf("��%d�ų���\n", p->data);
			head->data--;
			last->next = p->next;
			free(p);
		}
		else last = last->next;
		num++;
	} 
	
	// �ͷ�ͷ���
	free(head); 
}



#include<iostream>
#include<stdlib.h>
using namespace std;

//˳���ͷ�ṹ�� 
typedef struct {
	int *head;
	int length;
}Sqlist;


//��������
void ListTraverse(Sqlist list) {
	for(int i = 0; i < list.length; i++) 
		printf("��%dλֵΪ��%d\n", i+1, list.head[i]); 
}
		
//��ʼ�����Ա�
bool InitList(Sqlist &list, int n) {
	if(list.head = (int*)malloc(n*sizeof(int))) {
		list.length = 0;
		for(int i = 0; i < n; i++) {
		list.head[i] = i+1;
			list.length++;
		}
		printf("================˳�����ǰ===============\n");
		ListTraverse(list);
		return true;
	}
	else return false;
}

//�������Ա���freeͷָ��
bool DestroyList(Sqlist &list) {
	if(list.head) {
		free(list.head);
		list.head = NULL;
		return true;
	}
	else return false;
}


int main() {
	Sqlist list;//˳���ͷ 
	
	int num;
	printf("������˳���Ԫ�صĸ�����");
	scanf("%d", &num);
	
	if(InitList(list, num)) printf("��ʼ��˳���ɹ�\n");
	else printf("��ʼ��˳���ʧ��\n");
	
	int temp = 0;
	for(int i = 0; i < list.length/2; i++) {
		temp = list.head[i];
		list.head[i] = list.head[list.length-i-1];
		list.head[list.length-i-1] = temp; 
	}
	printf("=====================˳���ú�=================\n");
	ListTraverse(list);
	
	if(DestroyList(list)) printf("�������ٳɹ�\n");
	else printf("��������ʧ��\n"); 
}

#include<stdio.h>
#include<stdlib.h>

typedef struct LNode{
	int data;
	LNode *next;
}*LinkList, LNode;

//��posλ�ò���e 
bool insertLinkList(LinkList &list, int pos, LNode *e){
	if(pos>list->data+1 || pos<=0) return false;
	
	int i = 1;
	LNode *p = list->next, *prior = list;
	while(p && i<pos){
		prior = p;
		p = prior->next;
		i++;
	}
	prior->next = e;
	e->next = p;
	list->data++;
	return true;
}

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
	printf("==================================\n\n");
}

int main(){
	int n = 0, m = 0;
	scanf("%d%d", &n, &m);
	
	//��ʼ�� 
	LinkList list = (LNode*)malloc(sizeof(LNode));
	list->data = 0;
	LNode *temp, *p = list;
	for(int i=0; i<n; i++){
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = i+1;					//��ѧ�Ÿ������������� 
		p->next = temp;
		p = p->next;
		list->data++;
	}
	p->next = NULL;
	ListTraverse(list);
	
	//��ʼ�Ŷ� 
	int num = 0, pos = 0;
	int j = 0;
	LNode *prior = NULL;
	for(int i=1; i<=m; i++){
		scanf("%d%d", &num, &pos);
		p = list->next;
		prior = list;
		j = 1;
		while(p){
			if(p->data == num){				//�ҵ����ڸ�ѧ�ŵĽ�� 
				prior->next = p->next;		//���ý��ȡ�� 
				list->data--;
				if(!insertLinkList(list, j+pos, p)) {	//�ٽ��ý�������λ�� 
					printf("insert error!\n");
				}
			}
			prior = p;
			p = prior->next;
			j++;
		} 
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

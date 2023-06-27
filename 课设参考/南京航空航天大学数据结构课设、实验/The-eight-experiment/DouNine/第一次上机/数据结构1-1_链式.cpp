#include<iostream>
#include<stdlib.h>
using namespace std;

// ��ʽ��� 
typedef struct LNode{
	int data;
	LNode *next;
}LNode, *LinkList;

// ��ʽ���Ա���
class CLinkList {
	public:
		
		//��ʼ�����Ա�����һ��ͷ��㣬ͷ����data���ݱ�ʾ������ 
		bool InitList(LinkList &list) {
			if(list = (LNode*)malloc(sizeof(LNode))) {
				list->data = 0;
				list->next = NULL;
				return true;
			}
			else return false;
		};

		//�������Ա���freeͷָ��
		bool DestroyList(LinkList &list) {
			if(list) {
				if(ClearList(list)) {
					printf("�������ɹ�\n");
					free(list);
					return true;
				}
				else {
					printf("�������ʧ��\n");
					return false;
				}
			}
			else return false;
		};
		
		//������Ա�������Ľ�㶼ɾ������ͷ���֮�⣩ 
		bool ClearList(LinkList &list) {
			if(list) {
				LNode *temp, *p = list->next;
				while(p) {
					temp = p;
					p = p->next;
					free(temp);
				}
				list->data = 0;
				list->next = NULL;
				return true;
			}
			return false;
		};
		
		//�ж��Ƿ�Ϊ�ձ�
		bool ListEmpty(LinkList list) {
			if(!list) return false;			//�жϱ��Ƿ�Ϊ�� 
			return list->data ? false:true;
		};	
		
		//�������Ա�ĳ���
		int ListLength(LinkList list) {
			if(!list) return 0;				//�жϱ��Ƿ�Ϊ�� 
			return list->data;
		};
		
		//�������Ա��е�i��λ�õĽ�� 
		bool GetElem(LinkList list, int i, LNode *e) {
			if(!list || !list->data) return false;			//�жϱ��Ƿ�Ϊ�� 
			if(i <= 0 || i > list->data) return false;
			else {
				int j = 1;
				LNode *p = list->next;
				while(p && j++!=i) p = p->next;
				e->data = p->data;
				e->next = p->next;
			}
			return true;
		};
		
		//�������Ա���ֵ��e��ȵ�λ�� 
		int LocateElem(LinkList list, LNode *e) {
			if(!list || !list->data) return 0;
			LNode *p = list->next;
			int i = 1;
			while(p) {
				if(p->data == e->data) return i;
				p = p->next;
			}
			return 0;
		};
		
		//����ֵ��cur_e��ͬ��ǰһ��ֵ
		bool PriorElem(LinkList list, LNode *cur_e, LNode *pre_e) {
			if(!list || !list->data) return false;			//�жϱ��Ƿ�Ϊ�� 
			LNode *last = list, *p = list->next;
			int j = 1;
			while(p) {
				if(j == 1 && p->data == cur_e->data) return false;
				if(p->data == cur_e->data) {
					pre_e->data = last->data;
					pre_e->next = last->next;
					return true;
				}
				last = p;
				p = last->next;
				j++;
			}
			return false;
		};
		
		//����ֵ��cur_e��ͬ����һ��ֵ 
		bool NextElem(LinkList list, LNode *cur_e, LNode *next_e) {
			if(!list || !list->data) return false;			//�жϱ��Ƿ�Ϊ�� 
			LNode *next, *p = list;
			int j = 1;
			while(p) {
				next = p->next;
				if(j == list->data && p->data == cur_e->data) return false;
				if(p->data == cur_e->data) {
					next_e->data = next->data;
					next_e->next = next->next;
					return true;
				}
				p = p->next;
				j++;
			}
			return false;
		};
		
		//�����Ա�ĵ�iλ����eֵ
		bool ListInsert(LinkList &list, int i, LNode *e) {
			if(!list) return false;			//�жϱ��Ƿ�Ϊ��  
			if(i <= 0 || i > list->data+1) return false;		//�ж�i�Ƿ���Ч
			
			//��ֹ�û��Ѵ�����ʵ��e���ʹ��
			LNode *temp = (LNode*)malloc(sizeof(LNode));	 
			temp->data = e->data;
			temp->next;
			
			LNode *last = list, *p = list->next;
			int j = 1;
			while(p && j++!=i) {							
				last = p;
				p = last->next;
			}
			last->next = temp;
			temp->next = p;
			list->data++;
			return true;
		};
		
		//ɾ��iλ�õ�ֵ������e������ֵ 
		bool ListDelete(LinkList &list, int i, LNode *e) {
			if(!list || !list->data) return false;			//�жϱ��Ƿ�Ϊ�� 
			if(i <= 0 || i > list->data) return false;		//�ж�i�Ƿ���Ч
			LNode *last = list, *p = list->next;
			int j = 1;
			while(p && j++!=i) {
				last = p;
				p = last->next;
			}
			e->data = p->data;
			e->next = NULL;
			last->next = p->next;
			free(p);
			list->data--;
			return true;
		};
		
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
		};		 
}; 


int main() {
	CLinkList List;//˳������ 
	LinkList list;//˳���ͷ 
	
	if(List.InitList(list)) printf("��ʼ��˳���ɹ�\n");
	else printf("��ʼ��˳���ʧ��\n");
	
	int i = 1;
	LNode *temp, *p=list;
	while(i <= 20) {
		temp = (LNode*)malloc(sizeof(LNode));
		temp->data = i;
		temp->next = NULL;
		p->next = temp;
		p = p->next;
		list->data++;
		i++; 
	}
	
	LNode *test = (LNode*)malloc(sizeof(LNode));
	if(List.GetElem(list, 16, test)) printf("��16λԪ�ص�ֵ�ǣ�%d\n", test->data);
	else printf("���ʵ�16λԪ��ʧ��\n");
	
	LNode *test1 = (LNode*)malloc(sizeof(LNode));
	if(List.PriorElem(list, test, test1)) printf("%dǰһ��Ԫ�ص�ֵΪ��%d\n", test->data, test1->data);
	else printf("����ǰһλԪ��ʧ��\n");
	
	if(List.NextElem(list, test, test1)) printf("%d��һ��Ԫ�ص�ֵΪ��%d\n", test->data, test1->data);
	else printf("���ʺ�һλԪ��ʧ��\n");
	
	test->data = 9999;
	if(List.ListInsert(list, 13, test)) printf("�ڵ�13λ��ֵ�ɹ��������ֵΪ��%d\n", test->data);
	else printf("�ڵ�13λ��ֵʧ��\n");
	
	test->data = 8888;
	if(List.ListInsert(list, 21, test)) printf("�ڵ�21λ��ֵ�ɹ��������ֵΪ��%d\n", test->data);
	else printf("�ڵ�21λ��ֵʧ��\n");
	
	if(List.ListDelete(list, 6, test)) printf("��6λɾֵ�ɹ���ֵΪ��%d\n", test->data);
	else printf("��6λɾֵʧ��\n");
	
	List.ListTraverse(list);
	
	if(List.DestroyList(list)) printf("�������ٳɹ�\n");
	else printf("��������ʧ��\n"); 
}

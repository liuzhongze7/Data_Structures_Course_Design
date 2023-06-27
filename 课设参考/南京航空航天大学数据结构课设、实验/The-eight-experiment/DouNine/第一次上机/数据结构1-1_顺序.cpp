#include<iostream>
#include<stdlib.h>
using namespace std;

#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10

// ˳���ͷ 
typedef struct {
	int *head;
	int length;
	int listSize;
}Sqlist;

//˳�����Ա���
class CSqList {
	public:
		
		//��ʼ�����Ա�������һ���ձ�
		bool InitList(Sqlist &list) {
			if(list.head = (int*)malloc(LIST_INIT_SIZE*sizeof(int))) {
				list.length = 0;
				list.listSize = LIST_INIT_SIZE;
				return true;
			}
			else return false;
		};

		//�������Ա���freeͷָ��
		bool DestroyList(Sqlist &list) {
			if(list.head) {
				free(list.head);
				list.head = NULL;
				return true;
			}
			else return false;
		};
		
		//������Ա������Ϊ��
		void ClearList(Sqlist &list) {
			list.length = 0;
		};
		
		//�ж��Ƿ�Ϊ�ձ�
		bool ListEmpty(Sqlist list) {
			return list.length ? false:true;
		};	
		
		//�������Ա�ĳ���
		int ListLength(Sqlist list) {
			return list.length;
		};
		
		//�������Ա��е�i��λ�õ�ֵ
		bool GetElem(Sqlist list, int i, int &e) {
			if(!list.length) return false;
			if(i <= 0 || i > list.length) return false;
			else e = list.head[i-1];
			return true;
		};
		
		//�������Ա���ֵ��e��ȵ�λ�� 
		int LocateElem(Sqlist list, int e) {
			if(!list.length) return 0;
			for(int i = 0; i < list.length; i++) {
				if(list.head[i] == e) return i+1;
			}
			return 0;
		};
		
		//����ֵ��cur_e��ͬ��ǰһ��ֵ
		bool PriorElem(Sqlist list, int cur_e, int &pre_e) {
			if(!list.length) return false;
			if(list.head[0] == cur_e) return false;
			for(int i = 1; i < list.length; i++) {
				if(list.head[i]  == cur_e) {
					pre_e = list.head[i-1];
					return true;
				}
			}
			return false;
		};
		
		//����ֵ��cur_e��ͬ����һ��ֵ 
		bool NextElem(Sqlist list, int cur_e, int &next_e) {
			if(!list.length) return false;
			if(list.head[list.length - 1] == cur_e) return false;
			for(int i = 0; i < list.length-1; i++) {
				if(list.head[i]  == cur_e) {
					next_e = list.head[i+1];
					return true;
				}
			}
			return false;
		};
		
		//�����Ա�ĵ�iλ֮ǰ����eֵ
		bool ListInsert(Sqlist &list, int i, int e) {
			if(!list.length) return false;					//�жϱ��Ƿ�Ϊ�� 
			if(i <= 0 || i > list.length) return false;		//�ж�i�Ƿ���Ч
			if(list.length == list.listSize) {				//�жϱ�洢�ռ��Ƿ����� 
				int *newBase;
				if(newBase = (int*)realloc(list.head, 
				(list.listSize+LIST_INCREMENT) * sizeof(int))) {
					list.head = newBase;
					list.listSize += LIST_INCREMENT;
				}
				else {
					printf("error from ListInsert(): realloc defeat!\n");
					return false;
				}
			}
			for(int j = list.length-1; j >= i-1; j--) {		//��head[i-2]֮������������һλ 
				list.head[j+1] = list.head[j];
			}
			list.head[i-1] = e;								//��e����head[i-1] 
			list.length++;
			return true;
		};
		
		//ɾ��iλ�õ�ֵ������e������ֵ 
		bool ListDelete(Sqlist &list, int i, int &e) {
			if(!list.length) return false;					//�жϱ��Ƿ�Ϊ�� 
			if(i <= 0 || i > list.length) return false;		//�ж�i�Ƿ���Ч
			e = list.head[i-1];								//��head[i-1]����e 
			for(int j = i; j < list.length; j++) {			//��head[i]֮���������ǰ��һλ 
				list.head[j-1] = list.head[j];
			}
			list.length--;
			return true;
		};
		
		//��������
		void ListTraverse(Sqlist list) {
			printf("\n================����==============\n");
			for(int i = 0; i < list.length; i++) 
				printf("��%dλֵΪ��%d\n", i+1, list.head[i]); 
		};		 
}; 


int main() {
	CSqList List;//˳������ 
	Sqlist list;//˳���ͷ 
	
	if(List.InitList(list)) printf("��ʼ��˳���ɹ�\n");
	else printf("��ʼ��˳���ʧ��\n");
	for(int i = 0; i < 20; i++) {
		list.head[i] = i+1;
		list.length++;
	}
	
	int test = 0;
	if(List.GetElem(list, 16, test)) printf("��16λԪ�ص�ֵ�ǣ�%d\n", test);
	else printf("���ʵ�16λԪ��ʧ��\n");
	
	int test1 = 0;
	if(List.PriorElem(list, test, test1)) printf("%dǰһ��Ԫ�ص�ֵΪ��%d\n", test, test1);
	else printf("����ǰһλԪ��ʧ��\n");
	
	if(List.NextElem(list, test, test1)) printf("%d��һ��Ԫ�ص�ֵΪ��%d\n", test, test1);
	else printf("���ʺ�һλԪ��ʧ��\n");
	
	if(List.ListInsert(list, 13, 1392985954)) printf("�ڵ�13λ��ֵ�ɹ��������ֵΪ��1392985954\n");
	else printf("�ڵ�13λ��ֵʧ��\n");
	
	if(List.ListDelete(list, 6, test)) printf("��6λɾֵ�ɹ���ֵΪ��%d\n", test);
	else printf("��6λɾֵʧ��\n");
	
	List.ListTraverse(list);
	
	if(List.DestroyList(list)) printf("�������ٳɹ�\n");
	else printf("\n��������ʧ��\n"); 
}

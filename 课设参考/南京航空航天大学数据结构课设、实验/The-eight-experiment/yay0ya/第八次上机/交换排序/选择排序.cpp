#include<iostream>
using namespace std;
#define LIST_INIT_SIZE  100
typedef int Sqtype;
typedef struct {
	Sqtype *elem;
	int length;//��ǰ����
	int listsize;//��ǰ����洢���� 
} Sqlist;
void selectsort(Sqlist &l){
	int SelectMinKey(Sqlist l,int i);
	for(int i=0;i<l.length;i++){
		int j=SelectMinKey(l,i);//��i��ʼ�Ը������е�������ֵ��ѡ��һ����Сֵ���±�
		if(i!=j){
			int temp;
			temp=l.elem[i];
			l.elem[i]=l.elem[j];
			l.elem[j]=temp;//���i��=j  ���н�����ʾ���ڵ�i���������е���Сֵ 
		} 
	}
}//selectsort
int SelectMinKey(Sqlist l,int i){
	int flag=i;
	for(int j=i+1;j<l.length;j++){
		if(l.elem[j]<l.elem[flag])
			flag=j;		
	}
	return flag;
} 
int main(){
	int n;
	cin>>n;
	Sqlist l;
	l.length=n;
	l.elem=new int[n];
	Sqtype *q;
	q=l.elem;
	for(int i=0;i<n;i++){
		cin>>*q;
		q++;
	}
	selectsort(l);
	q=l.elem;
	for(int i=0;i<n;i++){
		cout<<*q<<" ";
		q++; 
	}
	return 0;
}

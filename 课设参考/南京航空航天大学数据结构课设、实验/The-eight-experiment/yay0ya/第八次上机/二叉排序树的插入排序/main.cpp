#include<iostream>
using namespace std;
//��ɶ����������Ĳ�����ɾ��
#include"InsertDelete.h"
int main(){
	BiTree T;
	int n;
	createBiTree(T);
	cout<<"����Ҫ�����ֵ"<<endl; 
	cin>>n;
	InsertBST(T,n);
	cout<<"����������"<<endl;
	InOrderTraverse(T);
	cout<<"����Ҫɾ����ֵ"<<endl;
	cin>>n;
	DeleteBST(T,n);
	cout<<"����������"<<endl; 
	InOrderTraverse(T);
	return 0;
} 

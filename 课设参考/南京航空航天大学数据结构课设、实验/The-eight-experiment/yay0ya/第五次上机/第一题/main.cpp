#include"Delete.h"
int main(){
	BiTree T1,T2;
	InitBiTree(T1);
	cout<<"������������ĸ�������֧����-1��ʾ����\n"; 
	createBiTree(T1);
	cout<<"����������\n"; 
	PreOrderTraverse(T1);
	cout<<endl;
	cout<<"����������\n"; 
	PostOrderTraverse(T1);
	cout<<endl;
	cout<<"����������\n";
	InOrderTraverse(T1);
	/*cout<<"�ٴ���һ����";
	InitBiTree(T2);
	cout<<"������������ĸ�������֧����-1��ʾ����\n";
	createBiTree(T2);*/
	BiTNode temp,*p;
	cout<<"������Ҫ��T1���ҵ�ֵ\n"; 
	cin>>temp.data;
	p=RightSibling(T1,temp);
	if(p!=NULL){
		cout<<"�������ֵ���";
		cout<<p->data;
	}
	if(p==NULL){
		cout<<"�����������ֵܻ��߲����ڸ�ֵ\n";
	}
	cout<<"��������һ��ֵ\n";
	cin>>temp.data;
	p=LeftSibling(T1,temp);
	if(p!=NULL){
		cout<<"�������ֵ���";
		cout<<p->data;
	}
	if(p==NULL){
		cout<<"�����������ֵܻ��߲����ڸ�ֵ\n";
	}
	cout<<"����һ���ڵ�ֵ\n";
	BiTNode node;
	cin>>node.data;
	node.lchild=NULL;
	node.rchild=NULL;
	cout<<"����pָ���ֵΪ\n"; 
	cout<<p->data;
	cout<<"���ڽ������뵽p��ָλ�õ��Һ�������"; 
	InsertChild(T1,p,1,&node);
	cout<<"������������\n";
	InOrderTraverse(T1);
	cout<<"����pָ���ֵΪ\n";
	cout<<p->data;
	cout<<"ɾ��p��ָ����ҽ��\n";
	DeleteChile(T1,p,1);
	cout<<"������������\n";
	InOrderTraverse(T1);
	cout<<"����һ�����������е�һ���ڵ�ֵ\n"<<endl;
	cout<<"pָ������������ֵܣ�����ɾ��p���ڵĽ�����������\n" ; 
	cin>>temp.data;
	p=LeftSibling(T1,temp);
	cout<<"p��"<<p->data<<"\n"; 
	cout<<"ɾ��������p���ڽ�����������\n"; 
	Deletechild(T1,p);
	InOrderTraverse(T1);
	return 0;
}


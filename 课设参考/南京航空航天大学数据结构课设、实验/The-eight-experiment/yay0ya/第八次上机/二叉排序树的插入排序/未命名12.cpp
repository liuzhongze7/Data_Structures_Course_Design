#include<iostream>
using namespace std;
typedef int BStype;
typedef struct BSNode{
	BStype data;
	struct BSNode *lchild;
	struct BSNode *rchild;//���Һ��� 
}BSNode,*BiSTree;//��������������Ľ�����
int BFSearch(BiSTree T,BStype ch,BSNode *q,BSNode *temp)//�����������ҵ��ʺϵĽ��λ�� ,���ؽ��ָ�� 
{
	BSNode *p;
	p=T;
	if(p->data==ch)	{
		temp=p;//�ҵ���ֵ����ָ��ָ���ֵ���ڵ�λ��
		return 1; 
	}
	if(p->data>ch){
		if(p->lchild==NULL){
			q=p;
			return 0;
		}
		BFSearch(p->lchild,ch,q,temp);
	}
	if(p->data<ch){
		if(p->rchild==NULL){
			q=p;//��ʾ�Ѿ��ҵ��ʺϵĽ��λ�ÿ��Խ��в��� 
			return 0;
		}
		BFSearch(p->rchild,ch,q,temp);
	}
}
bool InsertBiSTree(BiSTree &T){
	//����һ������������
	BStype ch;
	BSNode *p,*temp,*q;
	cin>>ch;
	p=new BSNode;
	p->data=ch;
	p->lchild=NULL;
	p->rchild=NULL; 
	if(ch!=-1){
		if(!BFSearch(T,ch,q,temp)){
			
		if(ch>p->data){
			q->rchild=p;
		}
		if(ch<p->data){
			q->lchild=p;
		}
	}
	else{
		cout<<"��ֵ�Ѿ�����\n"<<" "; 
		return 1;
	}
	}
	else
		return 0; 
} 
void InitBiStree(BiSTree &T){
	//����ͷ���
	T=new BSNode;
	BStype ch;
	cin>>ch;
	T->data=ch;
	T->lchild=NULL;
	T->rchild=NULL; 
}
void DeleteBSNode(BiSTree &T){
	 
}

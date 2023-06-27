#include<iostream>
using namespace std;
#include<stdlib.h>
#include"Stack.h"
Status Depth(BiTree T,int n,int depth){
		if(!T->lchild)//����һ�������� 
		Depth(T->lchild,n+1,depth);//������Ӳ�Ϊ�գ����룬������һ 
		if(!T->rchild)
		Depth(T->rchild,n+1,depth);
		if(depth<n)//�����depth�ȵ�ǰn�������ʱ����ȣ�С���򽫴�ʱ��ȸ���depth 
		depth=n;
	}
Status InitBiTree(BiTree &T){//����һ���յĶ����� 
	T=(BiTree)malloc(sizeof(BiTNode));
	T->lchild=NULL;
	T->rchild=NULL;
	if(!T) exit(0);
	return 1;
}
Status DestroyBiTree(BiTree &T){
	//����һ����
	free(T);
	return 1; 
} 
void createBiTree(BiTree&T){	
	TElemType c;
	cin>>c;
	if(c==-1){
		T=NULL;
	}
	else{
		T= new BiTNode;
		T->data=c;
		createBiTree(T->lchild);
		createBiTree(T->rchild);
	}
}
Status ClearBiTree(BiTree &T){
	//����������Ϊ����
	if(T){
		T->lchild=NULL;
		T->rchild=NULL;
	}
	return 1;
} 
Status BiTreeEmpty(BiTree T){
	//���շ���1�����շ���0
	if(T->lchild||T->rchild) return 0;
	else return 1; 
}
Status BiTreeDepth(BiTree T){
	int depth=0;
	BiTree p;
	if(!T) return 0;
	p=T;
	Depth(p,0,depth);
	return depth;
}
BiTree Root(BiTree T){
	//���������T���ڣ�����T�ĸ� 
	BiTree p;
	if(!T) return p;
	else return T;
} 
Status Value(BiTree T,BiTNode e){	//�Ƿ���Ҫ�ж�e�Ƿ������T�У�
	/*���������ұȶ�e*/
	BiTree p;
	if(!T) return 0;
	p=T;
	return e.data; 
}
	void find1(BiTree&T,BiTNode e,TElemType value){
		BiTNode*p;
		p=T;
		if(p->data==e.data) T->data=value;
		else{
		find1(p->lchild, e,value);
		find1(p->rchild, e,value);
	}
	}
Status Assign(BiTree T,BiTNode e,TElemType value){
	//������T���ڣ�e��T�е�ĳ����㣬���e��ֵΪvalue
	if(!T) return 0;
	find1(T,e,value);
	return OK;
	
}
	Status find(BiTree T,BiTNode e,BiTNode**p){
		if(T->data==e.data){//���в��Ҳ���������ý����e��ͬ���򷵻����eֵ 
			*p=T;
			return 1;   
		}
		else{
			find(T->lchild,e,p);
			find(T->rchild,e,p);
		}
	}
BiTNode* Parent(BiTree T,BiTNode e){
	//e��������еķǸ���㣬�������˫�ס����򷵻ؿ�
	BiTNode *p;
	if(!T){
	
	find(T,e,&p);
	return p;}
	else return 0;
	
} 
BiTNode LeftChild(BiTree T,BiTNode e){
	//��Ҷ�ӽ�㣬�򷵻����ӣ����ؿ�
	BiTNode* p;
	find(T,e,&p);
	if(!p->lchild&&!p->rchild){
		p=NULL;
		return *p;
	}
	else
		return *p->lchild;
	
}
BiTNode Rightchild(BiTree T,BiTNode e){
	//��Ҷ�ӽ�㣬�򷵻��Һ��ӣ����򷵻ؿ�
	BiTNode* p;
	find(T,e,&p);
	if(!p->lchild&&!p->rchild)	{
		p=NULL;
		return *p;
	}
	else
		return *p->rchild;
} 
void find(BiTree T,BiTNode e,BiTree &p){
		if(T==NULL){
			return;
		}
		else{
			if(T!=NULL){
				if(T->data==e.data){
					p=T;
				}
				find(T->lchild,e,p);
				find(T->rchild,e,p);	
			}
		}
	}
void findq(BiTree T,BiTNode e,BiTree &q){
	if(T==NULL){
		return;
	}
	else{
		if(T->lchild!=NULL&&T->lchild->data==e.data){
			q=T;
		}
		if(T->rchild!=NULL&&T->rchild->data==e.data){
			q=T;
		}
		findq(T->lchild,e,q);
		findq(T->rchild,e,q);
	}
}
BiTNode *LeftSibling(BiTree T,BiTNode e){
	//����e�����ֵܡ���e��T�����ӣ����������ֵܣ��򷵻ؿ�
	BiTNode* p,*q;
	BiTNode* t=NULL;
	find(T,e,p);//q����Ϊ��e����˫�׽�㡣�������ж�e��λ��
	findq(T,e,q);//��ǰ�� 
	if(q->rchild==p){//eֵΪ�ҽ�㣬���������ֵ�	 
			return q->lchild;//����������ֵܣ� 
	}
	else{//��������Ӻ��ӣ�����Error��
		return t; 
	}
	}
BiTNode *RightSibling(BiTree T,BiTNode e){
	//����e�����ֵܡ���e��T���Һ��ӣ����������ֵܣ��򷵻ؿ�
		BiTNode* p,*q;
	BiTNode* t=NULL;
	find(T,e,p);//q����Ϊ��e����˫�׽�㡣�������ж�e��λ��
	findq(T,e,q);//��ǰ�� 
	if(q->lchild==p){//eֵΪ�ҽ�㣬���������ֵ�	 
			return q->rchild;//����������ֵܣ� 
	}
	else{//��������Ӻ��ӣ�����Error��
		return t; 
	}
}
Status InsertChild(BiTree&T,BiTNode *p,int LR,BiTree c){
	//���������ڣ�pָ��t�е�ĳ����㣬LRΪ0��1���ǿն�����c��T���뽻��������Ϊ��
	//����LRΪ0��1����cΪT����֪�Ľ��������������p��ָ����ԭ�е���������������
	//���Ϊc������
	BiTNode *temp; 
	if(LR==0){//����T����֪�Ľ���������
		 if(p->lchild) temp=p->lchild;
		 p->lchild=c;
		 c->rchild=temp; 
		return OK;
	} 
	if(LR==1){//����T����֪�Ľ���������
		temp=p->rchild;//��ָ��tempָ���佫������������������������������ 
		p->rchild=c;//c���뵽������
		c->rchild=temp;
		return OK; 
	}
}
Status DeleteChile(BiTree T,BiTree &p,int LR){
	//���������ڣ�pָ��T�е�ĳ����㣬LRΪ0��1��
	//����LRΪ0��1��ɾ��T��p��ָ������������������
	
	if(LR==0){
		p->lchild=NULL;
	} 
	if(LR==1){
		p->rchild=NULL;
	}
	return OK; 
}
bool Visit(TElemType e){
	cout<<e<<" ";
	return 1;
}
Status PreOrderTraverse(BiTree T){
	if(T){
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild))
				if(PreOrderTraverse(T->rchild)) return OK;
		return ERROR;		
	}
	else return OK;
}
Status InOrderTraverse(BiTree T){
	//�������T
	if(T){
		if(InOrderTraverse(T->lchild))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild)) return OK;
		return ERROR;		 
	
	}
	else
		return OK;
}
Status PostOrderTraverse(BiTree T){
	//�������T
	if(T){
		if(PostOrderTraverse(T->lchild))
			if(PostOrderTraverse(T->rchild))
				if(Visit(T->data)) return OK;
		return ERROR;		
	} 
	else return OK;
}
Status LevelOrderTraverse(BiTree T){
	//�������T
	LinkQueue Q;
	BiTNode *p;
	InitQueue(Q);
	EnQueue(Q,T);
	while(!QueueEmpty(Q)){
		DeQueue(Q,p);
		cout<<p->data<<" ";
		if(p->lchild!=NULL){
			EnQueue(Q,p->lchild);
		}
		if(p->rchild!=NULL){
			EnQueue(Q,p->rchild);
		}
	}
}

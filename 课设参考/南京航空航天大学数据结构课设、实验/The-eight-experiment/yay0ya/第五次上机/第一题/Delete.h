#include"BiTree.h"
Status Deletechild(BiTree T,BiTree &p){
	//���������ڣ���ɾ��p��ָ������������������ͷ����ǵĿռ�
	SqStack S;
	InitStack(S);
	BiTNode *q;
	q=p->lchild;
	Push(S,q);
	while(!StackEmpty(S)){
		while(GetTop(S,q)&&q!=NULL){Push(S,q->lchild);}//�����ߵ���ͷ
		Pop(S,q);//��ָ���ջ 
		if(!StackEmpty(S)){
			Pop(S,q);
			free(q);
			Push(S,q->rchild);
		}
	}//while
	q=p->rchild;
	Push(S,q);
	while(!StackEmpty(S)){
		while(GetTop(S,q)&&q!=NULL){Push(S,q->lchild);}//�����ߵ���ͷ
		Pop(S,q);//��ָ���ջ 
		if(!StackEmpty(S)){
			Pop(S,q);
			free(q);
			Push(S,q->rchild);
		}
	}//while
	p->lchild=NULL;
	p->rchild=NULL;
	return OK; 
}

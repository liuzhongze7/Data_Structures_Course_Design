#include"BiTree.h"
Status EQ(TElemType data,TElemType key){
	if(data==key) return 1;
	else return 0;
}
Status LT(TElemType data,TElemType key){
	if(data<key) return 1;
	else return 0;
}
Status SearchBST(BiTree T,TElemType key,BiTree f,BiTree &p){
	if(T==NULL) {
		p=f;
		return 0; 
	}
	else if(EQ(key,T->data))//���keyֵ��T->data��ֵС 
		{
			p=T;
			return 1;
	}		
	else if(LT(key,T->data)) return SearchBST(T->lchild,key,T,p);
	else return SearchBST(T->rchild,key,T,p); 
}//SearchBST
Status InsertBST(BiTree &T,TElemType e){
	BiTNode *s;
	BiTNode *p;//pָ�룬ָ�����·���ϵ����һ����㣬fָ��˫�� 
	if(!SearchBST(T,e,NULL,p)){//���в����ڸ�ֵ 
		s=new BiTNode;
		s->data=e;
		s->lchild=NULL;
		s->rchild=NULL;
		if(p==NULL) T=s;
		else if(LT(e,p->data))
		p->lchild=s;
		else p->rchild=s;
		return 1;
	}
	else return 0;
}
Status DeleteT(BiTree &p) {
	BiTNode *q,*s;
	if(p->rchild==NULL){//����Һ���Ϊ�գ���ɾ���ý��ʱ��ǰ��ָ��������� 
		q=p;
		p=p->lchild;
		free(q);
	}
	else if(p->lchild==NULL){//����Ϊ�գ�ǰ��ָ���Һ��� 
		q=p;
		p=p->rchild;
		free(q);
	}
	else{//���Һ��ӽԲ�Ϊ�� 
		q=p;s=p->lchild;//qָ��ý�㣬sָ��ý������� 
		while(s->rchild!=NULL){//���s���Һ��Ӳ�Ϊ�� 
			q=s;//qָ��ǰ����sһֱָ���Һ��ӵ�ĩβ 
			s=s->rchild;
		}
		p->data=s->data;//��s���Һ���������ֵ����p 
		if(q!=p) q->rchild=s->lchild;//���q��ָ��λ����p����ȣ�����������Ҷ���ͽ�q�����һ������ֵ����p 
		else q->lchild=s->lchild;// 
		free(s);
	}
	return 1;
}//Delete
Status DeleteBST(BiTree &T,TElemType key){
	if(T==NULL) return 0;
	else{
		if(EQ(key,T->data)) {
			 DeleteT(T);
			 return 1;
		}
		else if(LT(key,T->data)) return DeleteBST(T->lchild,key);//���keyֵ�ȸý���ֵС������Ѱ�Ҳ���λ�� 
		else return DeleteBST(T->rchild,key);
	}
}//DeleteBST

#include<iostream>
using namespace std;
#include<stdlib.h>
#define LH 1 //��� 
#define EH 0 //�ȸ�
#define RH -1 //�Ҹ� 
typedef  int  ElemType;
#define FALSE 0
#define TRUE 1
typedef struct BSTNode{
	ElemType data;
	int bf;//����ƽ������
	struct BSTNode *lchild,*rchild; 
}BSTNode,*BSTree;

void R_Rotate(BSTree &p){
	//����*pΪ���Ķ�������������������������֮��pָ���µ�������㣬��
	//��ת����֮ǰ���������ĸ��ڵ� 
	BSTNode *lc;
	lc=p->lchild;//lcָ��*p���������ĸ���� 
	p->lchild=lc->rchild;//lc���������ҽ�Ϊ*p��������
	lc->rchild=p;
	p=lc; //pָ���µĽ�� 
	
}//R_Rotate

void L_Rotate(BSTree &p){
	//����*pΪ���Ķ�����������������������֮���pָ���µ�������㣬��
	//��ת����֮ǰ���������ĸ����
	BSTNode *rc;
	rc=p->rchild;//rcָ���*p���������ĸ����
	p->rchild=rc->lchild;//rc���������ҽ�Ϊ*p��������
	rc->rchild=p;p=rc;//pָ���µĸ��ڵ� 
} //L_Rotate

int EQ(ElemType e1,ElemType e2){
	if(e1==e2)
		return 1;
	else
		return 0;	
}

int LT(ElemType e1,ElemType e2){
	if(e1<e2)
		return 1;
	else 
		return 0;
}

void LeftBalance (BSTree &T){
	//����ָ��T��ָ���Ϊ���Ķ�����������ƽ����ת�������㷨����ʱ��ָ��Tָ��
	//�µĸ����
	BSTNode *lc,*rd;
	lc=T->lchild;   //lcָ��*T������������� 
	switch(lc->bf){		//���*T����������ƽ��ȣ�������Ӧƽ�⴦�� 
		case LH:			//�½�������*T�����ӵ��������ϣ�Ҫ������������ 
			T->bf=lc->bf=EH;
			R_Rotate(T);
			break;
		case RH:	//�½�������*T�����ӵ��������ϣ�Ҫ��˫������ 
			rd=lc->rchild;//rdָ��*T�����ӵ���������
			switch(rd->bf){
				case LH:
					T->bf=RH;
					lc->bf=EH;
					break;
				case EH:
					T->bf=lc->bf=EH;
					break;
				case RH:
					T->bf=EH;
					lc->bf=LH;
					break;		
			}//switch(rd->bf)
			rd->bf=EH;
			L_Rotate(T->lchild);  //��*T��������������ƽ�⴦��
			R_Rotate(T);		  //��*T������ƽ�⴦�� 
	}//switch(lc->bf) 
}//LeftBalance

void RightBalance(BSTree &T){
	//����ָ��T��ָ���Ϊ����ɲ����������ƽ����ת�������㷨������ʱ��ָ��Tָ��
	//�µĸ��ڵ�
	BSTNode *rc,*ld;
	rc=T->rchild;		//rcָ��*T�����������ڵ�
	switch(rc->bf){     //���*T����������ƽ��ȣ�������Ӧ��ƽ�⴦�� 
		case LH:		//�½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������
			ld=rc->lchild;	// ldָ��*T���Һ��ӵ���������
			switch(ld->bf){
				case LH:
					T->bf=EH;
					rc->bf=RH;
					break;
				case EH:
					T->bf=rc->bf=EH;
					break;
				case RH:
					T->bf=LH;
					rc->bf=EH;
					break;//	
			}//switch(ld->bf)
			ld->bf=EH;
			R_Rotate(T->rchild);	//��*T����������������ƽ�⴦�� 
			L_Rotate(T);		 //��T��������ƽ�⴦�� 
	} 
}

int InsertAVL(BSTree &T,ElemType e,bool &taller){
	//����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��
	//Ϊe���½ڵ㣬������1�����򷵻�0.��������ʹ����������ʧȥƽ�⣬����ƽ��
	//��ת������������taller��ӳT�������
	if(T==NULL){
		//�����½ڵ㣬�������ߡ�����tallerΪTRUE
		T=new BSTNode;
		T->data=e;
		T->lchild=T->rchild=NULL; 
		T->bf=EH; 
		taller=TRUE;
	} 
	else{
		if(EQ(e,T->data)){    //�����Ѿ����ں�e����ͬ�ؼ��ֵĽ�� 
			taller=FALSE;	  //���ٽ��в��� 
			return 0;		 
		}
		if(LT(e,T->data)){	//�������*T���������н������� 
			if(!InsertAVL(T->lchild,e,taller)) return 0;//δ����
			if(taller){					//�Ѳ��뵽*T���������������������� 
				switch(T->bf){		//���*T��ƽ��� 
					case LH:		//ԭ�����������������ߣ���Ҫ����ƽ�⴦�� 
						LeftBalance(T);
						taller=FALSE;
						break;
					case EH:		//ԭ�����������ȸߣ��������������߶�ʹ������ 
						T->bf=LH;
						taller=TRUE;
						break;
					case RH:		//ԭ�����������������ߣ��֣����������ȸ� 
						T->bf=EH;
						taller=FALSE;
						break;		
				}//switch(T->bf) 
			}	
		}//if
		else { //Ӧ������*T���������н������� 
			if(!InsertAVL(T->rchild,e,taller)) return 0;//δ���� 
			if(taller)
				switch(T->bf){
					case LH:
						T->bf=EH;
						taller=FALSE;
						break;
					case EH:
						T->bf=RH;
						taller=TRUE;
						break;
					case RH:
						RightBalance(T);
						taller=FALSE;
						break;	
				}//swich(T->bf)
		}//else 
	}//else
	return 1;
} //InsertAVL

int DeleteAVL(BSTree &T,ElemType e,bool &shorter){
	//����ƽ��Ķ���������T�д��ں�e����ͬ�ؼ��ֵĽ�㣬��ɾ�����Ԫ��
	//������1�����򷵻�0������ɾ����ʹ����������ʧȥƽ�⣬����ƽ��
	//��ת��������������shorter��ӳ�������� 
	if(T==NULL){
		return 0;//���������ƽ���� 
	}
	else{
		if(EQ(e,T->data))  //�ҵ����Ԫ�أ���ʼ����ɾ������
		{
			BSTNode *p=NULL;
			if(T->lchild==NULL){
				//���������Ϊ��
				p=T;//��pָ��Ҫɾ���Ľ�� 
				T=T->rchild;//�ý��ָ���Լ������������������������ĸ��ڵ����� 
				free(p); 
				shorter=TRUE;
			}
			else if(T->rchild==NULL){
				//�������������Ϊ��
				p=T;
				T=T->lchild;
				free(p);
				shorter=TRUE; 
			}
			else{
				//�����������������
				p=T->lchild;
				while(p->rchild!=NULL){
					p=p->rchild;
				} 
				T->data=p->data;
				DeleteAVL(T->lchild,p->data,shorter);//���������еݹ�ɾ��ǰ����� 
			}
			}//����ҵ�������� 
			else if(e<T->data)//������ֵ��������ָ��ֵҪС����������������
			{
				if(!DeleteAVL(T->lchild,e,shorter)){
					return FALSE;
				}
				if(shorter){
					switch(T->bf){
						case LH:
							T->bf=EH;
							shorter=TRUE;
							break;
						case EH:
							T->bf=RH;
							shorter=FALSE;
							break;
						case RH:
							RightBalance(T);
							if(T->rchild->bf==EH){
								shorter=FALSE;
							}
							else 
								shorter=TRUE;
								break;	
					}
				}
			 }
			 else{
			 	//��������������
				 if(!DeleteAVL(T->rchild,e,shorter))
				 	return FALSE;
					 if(shorter){
					 	switch(T->bf){
					 		case LH:
					 			LeftBalance(T);//������ƽ�⴦��
								 if(T->lchild->bf==EH){
								 	shorter=FALSE;
								 } 
								 else shorter=TRUE;
								 break ;
							case EH:
								T->bf=LH;
								shorter=FALSE;
								break;
							case RH:
								T->bf=EH;
								shorter=TRUE;
								break;
						 }//switch(T->bf)
					 }//if 
			 } 
		 } 
		 	return 1;
	}
 

void InOrderTraverse(BSTree T){
	if(T){
		InOrderTraverse(T->lchild);
		cout<<T->data<<" ";
		InOrderTraverse(T->rchild);
	}
}

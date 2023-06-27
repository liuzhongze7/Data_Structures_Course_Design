#include<iostream>
using namespace std;
#include<stdlib.h> 

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef int TElemType;
typedef struct BiTNode{
	//���ṹ
	 TElemType data;
	 struct BiTNode *lchild,*rchild;//���Һ���ָ�� 
}BiTNode,*BiTree;
typedef BiTNode* SElemType;
typedef int Status;

typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

//-----���������ĺ���ԭ��˵��----

Status InitStack(SqStack &S){
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base) exit(0);//�洢����ʧ��
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return 1; 
}//InitStack

Status DestroyStack(SqStack &S){
	//�ݻ�һ��ջ
	SElemType *p;
	p=S.base;//ָ��ָ��ջ�ף�
	while(p!=S.top){//��ָ��û��ָ��ջ��ʱ 
		free(p);
		p++;
	} 
	free(p);//�ͷ�pָ��ĵ�ַ�Ŀռ� 
	S.stacksize=0;//ջ�ռ���Ϊ0 
	return 1;
} 
Status ClearStack(SqStack &S){
	//���һ��ջ 
	S.top=S.base;//ջ����ջ��ָ��ͬһ���ռ�ջ�� 
	return 1; 
} 
Status StackEmpty(SqStack S){
	//�ж�ջ�Ƿ�Ϊ��
	if(S.top==S.base)//ջ�׺�ջ����ͬһ�ռ��ϣ����ж���ջΪ�� 
	return 1;
	else return 0; 
}
Status StackLength(SqStack S){
	//�ж�ջ�Ĵ�С
	SElemType *p=S.base;
	int count=0;
	while(p!=S.top){//ָ����ָ��ջ����ʱ�� count+1 
		p++;
		count++;
	} 
	return count;
} 
Status GetTop(SqStack S,SElemType &e){
	//����ջ��Ԫ��
	if(S.top==S.base) return 0;
	e=*(S.top-1);
	return 1; 
} //GetTop
Status Push(SqStack &S,SElemType &e){
	//����Ԫ��eΪ�µ�ջ��Ԫ��
	if(S.top-S.base>=S.stacksize){
	//ջ��׷�ӿռ�
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base) exit(0);//����洢�ռ�ʧ��
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT; 
	} 
	*S.top++=e;
	return 1;
}//Push
Status Pop(SqStack &S,SElemType &e){
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
	if(S.top==S.base) return 0;
	e=*--S.top;
	return 1; 
}//Pop 

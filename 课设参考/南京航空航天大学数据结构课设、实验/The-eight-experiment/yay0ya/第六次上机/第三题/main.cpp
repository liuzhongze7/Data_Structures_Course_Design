#include"CTree.h"
//���ɵ��Ǻ����ֵ��� 
int main() {
	CSTree T;
	CreateTree(T);
	cout<<"����������"<<endl;
	SqStack S;
	InitStack(S);
	Push(S,0);
	DFSearch(T,S);
	SElemType *p;
	int max;
	p=S.base;
	max=*p;
	while(p!=S.top){
		if(max<*p)
			max=*p;
		p++;	
	}
	cout<<"�������"<<max<<endl;
	return 0;
}

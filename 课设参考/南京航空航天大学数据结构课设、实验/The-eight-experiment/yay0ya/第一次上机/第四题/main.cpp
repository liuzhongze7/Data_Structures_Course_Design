#include<stdio.h>
#include"Link.h"
int main(){
	LinkList l;
	LNode *p;
	int i,n,id,temp,j;//iΪѧ���ĸ���,nΪ�ƶ��Ĵ���,id��ѧ����id��temp����ǰ������ƶ� 
	scanf("%d",&i);
	InitLink(l,i);
	getchar();
	scanf("%d",&n);
	for(j=0;j<n;j++){
		getchar();
		scanf("%d %d",&id,&temp);
		if(temp>=0){
			Moveafter(l,id,temp);
		}
		if(temp<0){
			Movebefore(l,id,temp);
		}
	}
	p=l->next;
	for(j=0;j<l->lenghts;j++){
		printf("%d",p->id);
		p=p->next;
	}
	return 0; 
}

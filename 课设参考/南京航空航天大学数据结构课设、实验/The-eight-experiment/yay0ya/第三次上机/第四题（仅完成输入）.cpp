//*********************
//ʱ�䣺ʮһ�¶�ʮ�ĺ�
//��Ŀ�������µ�����
//���ߣ�������
//*******************
#include<stdio.h>
#include<stdlib.h> 
typedef struct{
	int x;
	int y;
}point,*P;
typedef struct{
	point locate1;
	point locate2;
}windows,*W;
typedef struct click{
	windows data;
	click *next;
}*Clicklist;

int main(){
	int N,M;
	int x,y;
	int i=0;
	Clicklist list;
	P check,l;
	printf("�����봰�ڸ���\n");
	scanf("%d",&N);
	printf("������������\n");
	scanf("%d",&M);
	list=(Clicklist)malloc(N*sizeof(click));
	while(i<N){
		printf("�����봰�ڵ���������\n");
		scanf("%d %d",&x,&y);
		list->data.locate1.x=x;
		list->data.locate1.y=y;
		printf("�����봰�ڵ���������\n");
		scanf("%d %d",&x,&y);
		list->data.locate2.x=x;
		list->data.locate2.y=y; 
		i++;
	}
	i=0;
	check=(P)malloc(M*sizeof(point));
	l=check;
	while(i<M){
		printf("����������λ��\n");
		scanf("%d %d",&x,&y);
		l->x=x;
		l->y=y;
		l++;
		i++; 
	}
	
	 
} 

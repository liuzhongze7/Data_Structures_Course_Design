#include"list.h"
#include<stdlib.h>
#include<stdio.h>
int main(){
	int i,j,t,temp;//���м��� 
	sqlist a,b,c;
	int *q,*p,*r;
	lineup(a);
	lineup(b);
	if(a.length>b.length)
		temp=a.length;
	else
		temp=b.length;
	c.data=new int [temp];
	c.length=0;
	r=c.data;
	q=a.data;
	p=b.data;
	t=0;
	if(*q>*(p+b.length-1)||*(q+a.length-1)<*p)//���a�б�ĵ�һ��ֵ����b�ĵ����һ��ֵ��������û�н��� 
	//���b�б�ĵ�һ��ֵ����a �����һ�����޽���
	{
		c.length=0;
	}
	else{
	for(i=0;i<a.length;i++){
		p=b.data;
		p+=t;
		for(j=t;j<b.length;j++){
			
			if(*q<*p){
				break;
			}
			if(*q==*p){
				*r=*p;	
				c.length++;	
				r++;
				t=j;
				break;
		}
		p++;
		}
		q++;		 
	}
}
	r=c.data;
	if(c.length==0)
	{
		printf("�޽���\n");
	}
	else{
	printf("����Ϊ\n"); 
	for(i=0;i<c.length;i++)
	{
		printf("%d ",*r);
		r++;
	}
}
}

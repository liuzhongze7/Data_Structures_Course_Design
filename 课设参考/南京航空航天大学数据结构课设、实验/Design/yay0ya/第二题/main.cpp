#include <iostream>
#include"newtype.h"
#include<fstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	fstream file;
	file.open("data.txt",ios::in);
	if(!file.is_open())
	exit(0);
	int N,K,w,s,c;
	file>>N;
	file>>K;
	QNode *p;
	newtype *times;
	times=new newtype[N];
	LinkQueue Q;
	InitQueue(Q);//����һ������ 
	 
	for(int i=0;i<N;i++){
		EnQueue(Q,i+1);
	}
	int maxtime=0;
	p=Q.front;
	for(int i=0;i<K;i++){
		file>>times[i].w;//w��ʾʹ��Կ�ױ�� 
		file>>times[i].s;//s��ʾʹ��Կ�׵���ʼʱ�� 
		file>>times[i].c;//c��ʾʹ��Կ�׵�ʱ�䳤�� 
		times[i].count=times[i].c+times[i].s;
		if(maxtime<times[i].count)
			maxtime=times[i].count;//������¼����ʱ�� 
	}
	for(int i=0;i<K;i++){
		for(int j=i+1;j<K;j++){
			if(times[i].s>times[j].s){
				changethenumber(times[i],times[j]);
			}
		}
	}
	bool flag1=0,flag2=0;
	int timerecord=times[0].s;//��ʱ���¼Ϊ���ڵ�q��ʱ�� 
	while(timerecord<=maxtime){
		flag1=0;
		flag2=0;
	for(int i=0;i<K;i++){
		if(times[i].s==timerecord)
			if(outQueue(Q,times[i].w))
				flag1=1;//����ֵΪw��Կ��ȡ�� 
	
	}
		for(int j=0;j<K;j++){
			if(times[j].count==timerecord)//�������Կ�׵�ʱ����timerecord ��ʱ������ϣ���Կ�׷���
				if(putQueue(Q,times[j].w))
					flag2=1; 
		}
		if(flag1||flag2){
		cout<<"����ʱ����"<<timerecord<<"Կ��״��Ϊ��";
		QueueTraverse(Q);
		cout<<"\n";
		}
	
	timerecord++;
}
	file.close();
	return 0;
}

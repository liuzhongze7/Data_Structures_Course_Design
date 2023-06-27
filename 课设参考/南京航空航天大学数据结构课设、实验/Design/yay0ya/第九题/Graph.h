#include<iostream>
using namespace std;
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#define INFINITY -1
#define MAX_VERTEX_NUM 20
#define OK 1
#define ERROR -1 
typedef int Status;
typedef int VertexType;
typedef int VRType;
typedef int InfoType;
typedef enum {DG,DN,UDG,UDN}GraphKind;
typedef struct ArcCell{
	VRType adj;//VRType �Ƕ����ϵ���ͣ�����Ȩͼ����1��0
	//��ʾ����񣬶Դ�Ȩͼ����ΪȨֵ���͡�
	InfoType *info;//�û������Ϣ��ָ�� 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//�������� 
	AdjMatrix arcs;//�ڽӾ��� 
	int  vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ��� 
	GraphKind kind;//ͼ�������־ 
}MGraph;
Status LocateVex(MGraph G,VertexType u){
	//ͼG���ڣ�u��G�ж�������ͬ������
//��G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�������Ϣ
	int i,temp;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==u){//���������������ͬ 
			temp=i;//��temp��¼ס��λ��; 
			return temp;//���ظõ����б��е�λ�� 
		}
	}
	return -1;//�����ڸõ㣬����-1 
}

void caculate(MGraph G,int j){
	int loc=LocateVex(G,j);
	int flag=0;
	for(int i=0;i<G.vexnum;i++){
		if(G.arcs[loc][i].adj==1)
			flag++;
	}
	cout<<"Cc("<<j<<")"<<"="
		<<setiosflags(ios::fixed)
		<<setprecision(2)<<(double)(flag+1)/G.vexnum<<endl;
} 

Status CreateUDG(MGraph &G){//��������ͼ 
	//�������飨�ڽӾ��󣩱�ʾ������������ͼG��
	int i,j,k;
	fstream file;
	file.open("test.txt",ios::in);
	if(!file.is_open()){
		cout<<"�ļ���ʧ��\n";
		return 0;
	}
	VertexType v1,v2;
	file>>G.vexnum;
	file>>G.arcnum;//�ֱ�����˵����ͱ��� 
	for(i=0;i<G.vexnum;i++) G.vexs[i]=i+1;//���춥������
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//���ڽӾ�����г�ʼ��	
	}
	for(k=0;k<G.arcnum;k++){
		file>>v1;
		file>>v2;
		i=LocateVex(G,v1); j=LocateVex(G,v2);//ȷ��v1��v2��G�е�λ��
		G.arcs[i][j].adj=1;
		G.arcs[j][i].adj=1; 
	}
	int K;
	file>>K;
	int number[K]={};
	for(i=0;i<K;i++){
		file>>number[i];	
		caculate(G,number[i]);
	}
		 
}//��������ͼ 

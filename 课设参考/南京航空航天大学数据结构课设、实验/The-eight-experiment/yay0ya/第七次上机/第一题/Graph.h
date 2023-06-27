//�������ϻ���һ��
#include<iostream>
using namespace std;
#include"Queue.h"
#include<stdlib.h>
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
Status CreateDG(MGraph &G){//��������ͼ 
	//�������飨�ڽӾ��󣩱�ʾ��������������G��
	int i,j,k;
	VertexType v1,v2; 
	cout<<"������ ������������"<<endl;
	scanf("%d%d",&G.vexnum,&G.arcnum);//���붥�����뻡�� 
	cout<<"�����붥��ֵ"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//���춥������
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//���ڽӾ�����г�ʼ��	
	}
	cout<<"��������˵Ķ˵�ֵ��Ĭ�ϵ�һ�������Ϊ��β���ڶ���Ϊ��ͷ��"<<endl;
	for(k=0;k<G.arcnum;k++){
		scanf("%d%d",&v1,&v2);
		i=LocateVex(G,v1); j=LocateVex(G,v2);//ȷ��v1��v2��G�е�λ��
		G.arcs[i][j].adj=1; 
	}	 
}//��������ͼ
Status CreateDN(MGraph &G){//����������
	 int i,j,k,w;
	VertexType v1,v2;
	cout<<"����˵���������"<<endl; 
	scanf("%d%d",&G.vexnum,&G.arcnum);//���붥�����뻡�� 
	cout<<"����˵�ֵ"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//���춥������
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//���ڽӾ�����г�ʼ��	
	}
	cout<<"����ߵ������˵㣬ͬʱ����ߵ�Ȩֵ��Ĭ�ϵ�һ�������Ϊ��β���ڶ���Ϊ��ͷ��"<<endl;
	for(k=0;k<G.arcnum;k++){
		scanf("%d%d%d",&v1,&v2,&w);//����ߵ��������㣬�Լ����ϵ�Ȩֵ 
		i=LocateVex(G,v1); j=LocateVex(G,v2);//ȷ��v1��v2��G�е�λ��
		G.arcs[i][j].adj=w; 
	}	
}//���������� 
Status CreateUDG(MGraph &G){//��������ͼ 
	//�������飨�ڽӾ��󣩱�ʾ������������ͼG��
	int i,j,k;
	VertexType v1,v2;
	cout<<"����˵���������"<<endl;
	scanf("%d%d",&G.vexnum,&G.arcnum);//���붥�����뻡�� 
	cout<<"�����붥��ֵ"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//���춥������
	cout<<"��������˵Ķ˵�ֵ"<<endl;
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//���ڽӾ�����г�ʼ��	
	}
	for(k=0;k<G.arcnum;k++){
		scanf("%d%d",&v1,&v2);
		i=LocateVex(G,v1); j=LocateVex(G,v2);//ȷ��v1��v2��G�е�λ��
		G.arcs[i][j].adj=1;
		G.arcs[j][i].adj=1; 
	}	 
}//��������ͼ 
Status CreateUDN(MGraph &G){//����������
	 int i,j,k,w;
	VertexType v1,v2; 
	cout<<"����˵���������"<<endl;
	scanf("%d%d",&G.vexnum,&G.arcnum);//���붥�����뻡�� 
	cout<<"�����붥��ֵ"<<endl;
	for(i=0;i<G.vexnum;i++) scanf("%d",&G.vexs[i]);//���춥������
	for(i=0;i<G.vexnum;i++)
		for(j=0;j<G.vexnum;j++){
			G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;//���ڽӾ�����г�ʼ��	
	}
	cout<<"����ߵ������˵㣬ͬʱ����ߵ�Ȩֵ"<<endl;
	for(k=0;k<G.arcnum;k++){
		cin>>v1;
		cin>>v2;
		cin>>w;//����ߵ��������㣬�Լ����ϵ�Ȩֵ 
		i=LocateVex(G,v1); j=LocateVex(G,v2);//ȷ��v1��v2��G�е�λ��
		G.arcs[i][j].adj=w;
		G.arcs[j][i].adj=w; 
	}	
}//����������
Status CreateGraph(MGraph &G){
//V��ͼ�Ķ��㼯��VR��ͼ�л��ļ���
//��V��VR�Ķ��幹��ͼG
	int n;
	cout<<"������ͼ�����ͣ�1.DG,2.DN,3.UDG,4.UDN\n"; 
	cin>>n;
	switch(n){
		case 1:G.kind=DG;break;
		case 2:G.kind=DN;break;
		case 3:G.kind=UDG;break;
		case 4:G.kind=UDN;break;
	}
	switch(G.kind){
		case DG:return CreateDG(G);
		case DN:return CreateDN(G);
		case UDG:return CreateUDG(G);
		case UDN:return CreateUDN(G);
		default:return ERROR; 
	}
	return OK;	
}
 
Status DestroyGraph(MGraph &G){
	if(!G.vexnum)//����м䲻�����κζ��㣬��Ϊ�����ڸ�ͼ��
		return ERROR;
	else{
		free(G.arcs);
		free(G.vexs);//�ͷŵ�����ͻ��Ŀռ�
		G.vexnum=G.arcnum=0;//���������ͱ�����Ϊ0
		return OK; 
	} 
}//ͼG���ڣ�����ͼG

Status GetVex(MGraph G,VertexType v){//ͼG���ڣ�v��G��ĳ������
//����V��ֵ
	int i;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v){
			 return v;
		}
	}
	return -1;//�����ڸõ㣬����-1 
}
Status PutVex(MGraph &G,VertexType v,int value){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v){
			G.vexs[i]=value;
			return OK;
		}
	}
	return ERROR;
}
//ͼG���ڣ�v��G�е�ĳ������
//��V��ֵValue
Status FirstAdjVex(MGraph G,VertexType v)
{//����ͼG�е�v������ĵ�һ���ڽӵ�
	int i,j=-1;//�����Ƕ�����������
for(i=0;i<G.vexnum;i++)
	{
		if(!G.arcs[v][i].adj||G.arcs[v][i].adj==INFINITY)//��v������ĵ�i���ڽӶ���
		j++;
		else
			{
				j++;
				break;
			}
	}
	if(i==G.vexnum-1&&!G.arcs[v][i].adj||G.arcs[v][i].adj==INFINITY)
		return -1;
	return j;
}

//ͼG���ڣ�v��G�е�ĳ������
//����v�ĵ�һ���ڽӶ��㣬��������G��û���ڽӶ��㣬�򷵻ؿ�
Status NextAdjVex(MGraph G,VertexType v,VertexType w){
	//ͼG���ڣ�v��G��ĳ�����㣬w��v���ڽӶ���
//����v�ģ������w�ģ���һ���ڽӶ��㣬��w��v�����һ���ڽӵ㣬�򷵻ؿ�
	int i,j,k;
	if(!G.vexnum)//���G�Ķ�����Ϊ0Ĭ�ϲ�����
	 	return ERROR;//���ش���
 	i=LocateVex(G,G.vexs[v]);j=LocateVex(G,G.vexs[w]);//����v��w����ֵ�ڱ��е�λ��
	if(j==-1||i==-1||i==j){
		return ERROR;
	}
	for(k=j+1;k<G.vexnum;k++){
		if(G.arcs[i][k].adj!=INFINITY){
			return k;//����k��ֵ 
		}
	}  
	return ERROR;//�������	  
} 

Status InsertVex(MGraph &G,VertexType v)
//ͼG���ڣ�v��ͼ�ж�������ͬ����
//��ͼG�������¶���v
{
	G.vexs[G.vexnum]=v;
	G.vexnum++;//ͼ�еĶ�������һ��
	return OK; 
 } 
Status DeleteVex(MGraph &G,VertexType v)
//ͼG���ڣ�v��G�е�ĳ������
//ɾ��G�ж���v������صĻ�
{
	int i,j;
	if(!G.vexnum)//���������Ϊ0
		return ERROR;
	for(i=0;i<G.vexnum;i++){
		if(G.vexs[i]==v){//���ڸõ�
		 for(j=0;j<G.vexnum;j++){
		 	G.arcs[i][j].adj=INFINITY;
		 	G.arcs[j][i].adj=INFINITY;//��������i��صĻ�ɾ�� 
		 	G.arcnum-=1;
		 }
		 for(j=i;j<G.vexnum;j++){
		 	G.vexs[j]=G.vexs[j+1];//���ж��������ƶ�������ɾ�����λ�� 
		 }
		 G.vexnum-=1;
		 return OK;//�����ɹ�	
		}
	}
	return ERROR;//���ش��� �����������	 
 } 
Status InsertArc(MGraph &G,VertexType v,VertexType w)
//ͼG���ڣ�v��w��G�е���������
//��ͼ������<v,w>����G������������Գƻ�<w,v>
{
	int i,j,k;
	i=LocateVex(G,v);j=LocateVex(G,w);//���ҳ�v��w��ͼ�е�λ�� 
	if(G.kind==UDG){
		G.arcs[i][j].adj=G.arcs[j][i].adj=1;//����������Ϣ��һ 
		G.arcnum+=1;
		return OK;
	}
	if(G.kind==DG){
		G.arcs[i][j].adj=1;
		G.arcnum+=1;
		return OK;
	} 
	if(G.kind==DN){
		scanf("%d",&k);//����Ȩֵ
		G.arcs[i][j].adj=k;
		G.arcnum+=1;
		return OK; 
	}
	if(G.kind==UDN){
		scanf("%d",&k);//����Ȩֵ
		G.arcs[i][j].adj=k;
		G.arcs[j][i].adj=k;
		G.arcnum+=1;
		return OK;
		
	}
	return ERROR;
}
Status DeleteArc(MGraph &G,VertexType v,VertexType w)
//ͼG���ڣ�v��w��G����������
//��G��ɾ��<v,w>����G������ģ�����ɾ���Գƻ�<w,v>
{
	int i,j;
	if(!G.vexnum) return ERROR;
	i=LocateVex(G,v);j=LocateVex(G,w);//��λ����������ͼ�е�λ�� 
	switch(G.kind){
		case DG:{
			G.arcs[i][j].adj=INFINITY;
			G.arcnum--;
			break;
		}
		case DN:{
			G.arcs[i][j].adj=INFINITY;
			G.arcnum--;
			break;
		}
		case UDG:{
			G.arcs[i][j].adj=G.arcs[j][i].adj=INFINITY;
			G.arcnum--;
			break;
		}
		case UDN:{
			G.arcs[i][j].adj=G.arcs[j][i].adj=INFINITY;
			G.arcnum--;
			break;
		}
		default:return ERROR;
	}
	return OK; 
	}
void VisitFunc(VertexType v){
	printf("%d ",v);
}
void DFS(MGraph G,int v,bool *visited){
	int w; 
	visited[v]=1;
	VisitFunc(G.vexs[v]);//���ʵ�v������
	for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w)){
		if(!visited[w]) DFS(G,w,visited);//��û�з��ʹ��Ķ������DFS 
	} 
}
Status DFSTraverse(MGraph G){
//��ͼ����������ȱ������ڱ��������У���ÿ��������ú���Visitһ�Σ��ҽ�һ��
//һ��Visit����ʧ�ܣ������ʧ��
	int i;
	bool visited[G.vexnum];
	for(i=0;i<G.vexnum;++i){
		visited[i]=0;
	}
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]) DFS(G,i,visited);
	}
}
Status BFSTraverse(MGraph G){
	//���й���������� 
	int i,w,temp,u;
	bool visited[G.vexnum];
	LinkQueue Q;
	InitQueue(Q);//����һ������
	for(i=0;i<G.vexnum;i++) visited[i]=0;
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]){//i��δ������ 
			visited[i]=1;
			VisitFunc(G.vexs[i]);
			EnQueue(Q,i);
			while(!QueueEmpty(Q)){//���鲻Ϊ�� 
				DeQueue(Q,u);
				for(w=FirstAdjVex(G,G.vexs[u]);w>=0;w=NextAdjVex(G,G.vexs[u],G.vexs[w]))
				{
					if(!visited[w]){
						visited[w]=1; VisitFunc(G.vexs[w]);
						EnQueue(Q,w);
					}//oif
				}//while
			} //if
		}
	} 
	
}


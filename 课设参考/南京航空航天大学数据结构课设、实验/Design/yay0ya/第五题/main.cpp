#include"Graph.h"
int main(){
	int n,m;
	fstream file;
	file.open("data.txt",ios::in);
	if(!file.is_open()) 
		{
			cout<<"�޷��򿪸��ļ�\n";
			exit(0);
		}
	MGraph G;
	file>>n;
	file>>m;//nΪ·��������mΪ��·����
	G.vexnum=n;
	G.arcnum=m;
	int road[n]={};
	int t,a,b,c;
	Initarray(G,n);//��ʼ������ 
	for(int i=1;i<=m;i++){
		file>>t;
		file>>a;
		file>>b;
		file>>c;
		G.arcs[a][b].type=t;
		G.arcs[a][b].adj=c;
	}//�������·�йصľ�����յ���ֵ
	road[0]=1;
	findroad(G,road,0);
	miniout(G);

		
 }

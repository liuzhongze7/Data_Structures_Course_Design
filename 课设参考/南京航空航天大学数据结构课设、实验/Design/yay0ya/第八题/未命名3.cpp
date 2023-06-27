//*********************
//*����Ȧ*/
//******************
#include<iostream>
using namespace std;
#include<fstream>
typedef struct group{
	int id;
	int *data;
	int length;
}group,*G;
bool ifind(int M[],int n,int N){
	for(int i=0;i<N;i++){
		if(M[i]==n){
			return 1;
		}
	}
	return 0;
}
int calculatefriend(int N,G g,int id[],int M){//N��ѧ������G��ѧ���γɵ����ţ�id����Ҫ�ĸ�ѧ����ص����ŵĽ���һЩ�������ң�m�������� 
	int i,j,k,l;
	int record=0;
	int member[N]={};//�����洢ѧ�� 
	i=0;
	while(id[i]!=0){
		i++;
	}
	int count=i;
	for(i=0;i<count;i++){//��ѧ����������������м�����count���������� 
		for(j=0;j<M;j++){//M�������� 
			if(g[j].id==id[i]){//�������ţ��ҵ�������� 
				for(k=0;k<g[j].length;k++){//�������е��˽��м�¼�ͱȽ� 
					if(g[j].data[k]&&!ifind(member,g[j].data[k],N)){//���id��i������Ѿ�ӵ��������ѣ��Ͳ��ٽ����������ȥ 
						for(l=0;member[l]!=0;l++)
						;
						member[l]=g[j].data[k];
					}
				} 
			}
		}
	}
	for(i=0;i<N;i++){
		if(member[i]!=0)
			record++;
	}
	return record;
}
int main(){
	int N,M;
	fstream file;
	file.open("data.txt",ios::in);
	file>>N;
	file>>M;
	int i,j,k;
	G g;
	g=new group[M];
	for(int i=0;i<M;i++){
		g[i].id=i+1;
		file>>g[i].length;
		g[i].data=new int[g[i].length];
		for(int j=0;j<g[i].length;j++){
			file>>g[i].data[j];
		} 
	}
/*	for(int i=0;i<M;i++){
		cout<<g[i].length<<" ";
		for(int j=0;j<g[i].length;j++){
			cout<<g[i].data[j]<<" ";
		}
		cout<<endl;
	}
	�����⺯��*/
	int relation[N+1][M]={};//������ϵ������
	for( i=0;i<M;i++){
		for( j=0;j<g[i].length;j++){
			for( k=0;relation[g[i].data[j]][k]!=0;k++)
					;
			relation[g[i].data[j]][k]=g[i].id;		
		
		}
}
	int friendgroup[N+1]={};//���һ������洢
	for(i=1;i<N+1;i++){
		friendgroup[i]=calculatefriend(N,g,relation[i],M);
	}
	int max;
	max=0;
	for(i=0;i<N+1;i++){
		if(friendgroup[i]>max){
			max=friendgroup[i];
		}
	}
	cout<<max; 
	
} 


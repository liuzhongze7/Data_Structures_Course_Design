#include"CTree.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	int n,m;
	//n,m�ֱ��ʾjson���ݵ������Ͳ�ѯ�ĸ���
	void readstring(char obj[],CSTree &p);
	cin>>n;
	cin>>m;
	CSTree T;
	CSNode *point;
	CreateTree(T);
	point=T;
	char object[50]={};
	int i=0;
	getchar();
	for(i=0;i<n;i++){
		cin.getline(object,50,'\n');//�ж�
		readstring(object,point);
		getchar(); 
	}
}
void readstring(char obj[],CSTree &p){
	char zuo='{',you='}';
	if(obj[0]==zuo){
		insertobject(p);
		p=p->firstchild;
	}
	else if(obj[0]==you){
		
	}
}

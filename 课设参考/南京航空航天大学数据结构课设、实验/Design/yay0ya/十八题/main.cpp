#include"BiTree.h" 
#include<fstream>
int main() {
	fstream file;
	file.open("test.txt",ios::in);
	if(!file.is_open()){
		cout<<"�ļ���ʧ��\n";
		return 0; 
	}
	int n,data;//���ڼ�¼������ٸ��ַ���
	file>>n;
	int number[n]={};
	int i;
	for(i=0;i<n;i++){
		file>>number[i];//��i������ 
	} 
	BSTree T;
	T=NULL;
	bool taller;
	bool shorter;
	for(i=0;i<n;i++){
		InsertAVL(T,number[i],taller);
	}
	cout<<"�����������ƽ����\n";
	InOrderTraverse(T);
	cout<<endl;
	cout<<"����������ɾ���Ľ��\n";
	cin>>data;
	DeleteAVL(T,data,shorter);
	cout<<"ɾ���ýڵ���������\n";
	InOrderTraverse(T);
	return 0; 
}

#include"BTree.h"
int main() {
	fstream file;
	file.open("data.txt",ios::in);
	if(!file.is_open())
	{
		cout<<"�ļ���ʧ��\n";
		return 0; 
	}
	BTree T;
	int n;
	file>>n;//����ؼ��ʵĸ���
	int character[n];
	for(int i=0;i<n;i++){
		file>>character[i];
		BTreeInsert(character[i],T);
	}
	BTreeTraverse(T);
	return 0;
	 
}

#include <iostream>
using namespace std;
#include"traverse.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	BiTree T;
	int count=0;
	InitBiTree(T);
	createBiTree(T);
	cout<<"���������\n";
	PostOrderTraverse(T);
	cout<<endl;
	PostOrderTraverse2(T); 
	cout<<"���������\n";
	InOrderTraverse(T);
	cout<<"\n";
	InOrderTraverse2(T);
	cout<<"\n";
	cout<<"���������\n";
	PreOrderTraverse(T);
	cout<<"\n";
	PreOrderTraverse2(T);
	cout<<"\n";
	cout<<"��α�����\n";
	LevelOrderTraverse(T);
	countleaf(T,count);
	cout<<endl;
	cout<<count<<endl; 
	count=Depth(T);
	cout<<count;
}

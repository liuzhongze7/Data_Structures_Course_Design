#include"QuickSort.h"
void selectsort(int l[]){
	int SelectMinKey(int l[],int i);
	for(int i=1;i<20001;i++){
		int j=SelectMinKey(l,i);//��i��ʼ�Ը������е�������ֵ��ѡ��һ����Сֵ���±�
		if(i!=j){
			int temp;
			temp=l[i];
			l[i]=l[j];
			l[j]=temp;//���i��=j  ���н�����ʾ���ڵ�i���������е���Сֵ 
		} 
	}
}//selectsort
int SelectMinKey(int l[],int i){
	int flag=i;
	for(int j=i+1;j<20001;j++){
		if(l[j]<l[flag])
			flag=j;		
	}
	return flag;
} 
void SelecSortRT(){
	int n=20001;
	int L[20001]={};
	char name[10]="5.txt";
	int i=0,j;
	readfile(L,name);
	selectsort(L);
	fstream file;
	file.open("52.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
}
void selectsortLT(int l[]){
	int SelectMaxKey(int l[],int i);
	for(int i=1;i<20001;i++){
		int j=SelectMaxKey(l,i);//��i��ʼ�Ը������е�������ֵ��ѡ��һ����Сֵ���±�
		if(i!=j){
			int temp;
			temp=l[i];
			l[i]=l[j];
			l[j]=temp;//���i��=j  ���н�����ʾ���ڵ�i���������е���Сֵ 
		} 
	}
}//selectsort
int SelectMaxKey(int l[],int i){
	int flag=i;
	for(int j=i+1;j<20001;j++){
		if(l[j]>l[flag])
			flag=j;		
	}
	return flag;
} 
void SelecSortLT(){
	int n=20001;
	int L[20001]={};
	char name[10]="5.txt";
	int i=0,j;
	readfile(L,name);
	selectsortLT(L);
	fstream file;
	file.open("53.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L[i]<<" ";
	}
	file.close();
}

#include<iostream>
using namespace std;
typedef struct sqlist{
	int *data;
	int length;
}sqlist;
void lineup(sqlist &list){
	int n;
	cout<<"��������Ҫ��ĳ���\n";
	cin>>n;
	list.data=new int[n];
	cout<<"��������Ҫ¼���ֵ\n"; 
	for(int i=0;i<n;i++){
		cin>>list.data[i];
	}
	list.length=n;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(list.data[i]>list.data[j]){//���ǰһ���Ⱥ�һ���󡣽���λ�� 
				int temp;
				temp=list.data[i];
				list.data[i]=list.data[j];
				list.data[j]=temp;
			}
		//����ѭ������һ�������в��� 
		}
	}
	cout<<"����������ֵ\n"; 
	for(int i=0;i<n;i++){
		cout<<list.data[i]<<"\n";
	} 
} 

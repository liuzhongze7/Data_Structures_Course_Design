#include<iostream>
using namespace std; 
typedef struct sqlist{
	int *data;
	int length;
}sqlist;
int lineup(sqlist&list){
	int n;
	cout<<"��������Ҫ��ĳ���\n";
	cin>>n;
	list.data=new int[n];
	list.length=n;
	cout<<"��������Ҫ¼���ֵ\n"; 
	for(int i=0;i<n;i++){
		cin>>list.data[i];
	}
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
	return 0;
} 
int main(){
	sqlist a;
	int *p;
	int i;
	int middle;
	int flag=0;
	lineup(a);
	middle=a.data[a.length/2];
	p=a.data;
	for(i=0;i<a.length;i++){
		if(*p==middle)
		flag++;
		p++;
		
	}
	if((a.length-flag)%2==0){
		cout<<"�м�ֵ��"<<middle;
	}
	else
	cout<<"�������м�ֵ"<<"-1";
}

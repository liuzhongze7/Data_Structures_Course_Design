#include"Linklist.h"
int main(){
	LinkList a,b;
	int n,m;
	cout<<"������a��������ֵ�ĸ���\n";
	cin>>n;
	Create(a,n);
	SortLink(a,n); 
	cout<<"������b��������ֵ�ĸ���\n";
	cin>>m;
	Create(b,m);
	SortLink(b,m);
	Intersection(a,n,b,m);
	return 0;
} 

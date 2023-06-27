#include"sqlist.h"
typedef Sqlist HeapType;

int main(){
	HeapType H;
	void HeapSort(HeapType &H);
	InitList_Sq(H);
	int n;
	Sqtype *p;
	p=H.elem;
	cin>>n;
	p++;
	for(int i=0;i<n;i++){
		cin>>*p;
		p++;
	}
	H.length=n;
	HeapSort(H);
	p=H.elem;
	p++;
	for(int i=1;i<n+1;i++){
		cout<<*p<<" ";
		p++;
	}
	return 0;
}
void HeapAdjust(HeapType &H,int s,int m){
	int LT(Sqtype n,Sqtype m);
	Sqtype rc=H.elem[s];//������sΪ�Ѷ�������������棬��Ҷ�����ڵ���н������γ�һ������ 
	for(int j=2*s;j<=m;j*=2){//2*s,�õ���s˫�׵����Ҷ��� 
		if(j<m&&LT(H.elem[j],H.elem[j+1])) ++j;//LT�Ƚ����Һ��ӵĴ�С�� 
		if(!LT(rc,H.elem[j])) break;//�Ƚ�˫�׺����������������Ǹ����ӵ���ֵ��������LT�Ķ����ʾ�γɴ󶥶ѻ���С���� 
		H.elem[s]=H.elem[j]; s=j;//������������ӽڵ��ֵ 
	}
	H.elem[s]=rc;
}
void HeapSort(HeapType &H){
	//��˳�����ж�����
	for(int i=H.length/2;i>0;i--)//H.length/2 �õ����һ���ڽڵ㣻i--������ǰ�ƶ�һ����� 
		HeapAdjust(H,i,H.length);//�Բ����϶������ֵ���������� 
	for(int i=H.length;i>1;--i){// 
		int temp;
		temp=H.elem[1];
		H.elem[1]=H.elem[i];
		H.elem[i]=temp;//���Ѷ���¼�͵�ǰδ�������������Hr�����һ����¼���н��� 
	
		HeapAdjust(H,1,i-1);
	} 
}//HeapSort 
int LT(Sqtype n,Sqtype m){
	if(n>m) return 0;
	return 1;
}

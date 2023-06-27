#include"MergeSort.h" 

void HEAPSORT(){
	void HeapSort(int H[],int n);
	int n=20001;
  	int L1[20001]={};
	char name[10]="7.txt";
	int i=0,j;
	readfile(L1,name);
	HeapSort(L1,n);
		fstream file;
	file.open("72.txt",ios::out);
	for(i=1;i<=20000;i++){
		file<<L1[i]<<" ";
	}
	file.close();
}
void HeapAdjust(int H[],int s,int m){
	int rc=H[s];//������sΪ�Ѷ�������������棬��Ҷ�����ڵ���н������γ�һ������ 
	for(int j=2*s;j<=m;j*=2){//2*s,�õ���s˫�׵����Ҷ��� 
		if(j<m&&LT(H[j],H[j+1])) ++j;//LT�Ƚ����Һ��ӵĴ�С�� 
		if(!LT(rc,H[j])) break;//�Ƚ�˫�׺����������������Ǹ����ӵ���ֵ��������LT�Ķ����ʾ�γɴ󶥶ѻ���С���� 
		H[s]=H[j]; s=j;//������������ӽڵ��ֵ 
	}
	H[s]=rc;
}
void HeapSort(int H[],int n){
	//��˳�����ж�����
	for(int i=n/2;i>0;i--)//H.length/2 �õ����һ���ڽڵ㣻i--������ǰ�ƶ�һ����� 
		HeapAdjust(H,i,n);//�Բ����϶������ֵ���������� 
	for(int i=n;i>1;--i){// 
		int temp;
		temp=H[1];
		H[1]=H[i];
		H[i]=temp;//���Ѷ���¼�͵�ǰδ�������������Hr�����һ����¼���н��� 
	
		HeapAdjust(H,1,i-1);
	} 
}//HeapSort 

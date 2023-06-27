/*
ʵ�ֽ�����ѡ�񡢹鲢�ȼ������㷨��
*/
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

clock_t start,finish;	// ��ʼʱ�䣬����ʱ�� 
double totalTime;		// �ܵ�ʱ�� 

void timeStart() {
	cout<<"\n����ʼ\n";
	start = clock();
}

void timeFinish() {
	finish = clock();
   	totalTime = (double)(finish-start)/CLOCKS_PER_SEC;
   	cout<<"\n�������������ʱ��Ϊ"<<totalTime<<"�룡"<<endl;
}

// ���ò�������
void Reset(int *testNum, int *num, int n) {
	cout<<"\n����\n"; 
	for (int i=0; i<n; i++) {
		testNum[i] = num[i];
		//cout<<testNum[i]<<" ";
	}
	//cout<<endl;
} 

// ��������
void Traverse(int *num, int n) {
	cout<<"\n�������飺\n"; 
	for (int i=0; i<n; i++) {
		cout<<num[i]<<" ";
	}
	cout<<endl;
}

// ð������
void BubbleSort(int *num, int n) {
	for (int i=0; i<n; i++) {
		bool allSort = true;
		for (int j=1; j<n-i; j++) {
			if (num[j] < num[j-1]) {
				int temp = num[j];
				num[j] = num[j-1];
				num[j-1] = temp;
				allSort = false;
			}
		}
		if (allSort) break;
	}
}

// ѡ������
void SelectSort(int *num, int n) {
	for (int i=0; i<n; i++) {
		int min = num[i], pos;
		for (int j=i+1; j<n; j++) {
			if (num[j] < min) {
				min = num[j];
				pos = j;
			}
		}
		num[pos] = num[i];
		num[i] = min;
	}
} 

// �鲢����
void MergerSort(int *num, int n) {
	// �ݹ���ֹ���� 
	if (n == 1) return;
	
	int mid = n/2;
	// ��ǰ�벿�ֹ鲢���� 
	MergerSort(num, mid);
	// �Ժ�벿�ֹ鲢���� 
	MergerSort(num+mid, n-mid);
	
	// ���ź��������ֺϲ���temp���� 
	int *temp = (int*)malloc(sizeof(int) * n);
	int i = 0, j = mid, k = 0;
	while (i<mid && j<n) {
		if (num[i] <= num[j]) {
			temp[k] = num[i];
			i++;
		} else {
			temp[k] = num[j];
			j++;
		}
		k++;
	}
	// iָ��δ���м� 
	while (i<mid) {
		temp[k] = num[i];
		k++;
		i++;
	}
	// jָ��δ����β 
	while (j<n) {
		temp[k] = num[j];
		k++;
		j++;
	}
	
	// ������õ�temp���鸳��num 
	for (int i=0; i<n; i++) num[i] = temp[i]; 
	free(temp);
}

// ��������
void QuickSort(int *num, int n) {
	// �ݹ���ֹ���� 
	if (n <= 1) return;
	
	int i = 0, j = n-1;
	int temp = num[i];	// ��iλ�õ����ȴ�������iλ�������൱�ڡ��ա� 
	while (i<j) {
		while (num[j] >= temp && j>i) j--;
		// �˴�ֱ�ӽ�jλ�ò��ϸ��������iλ�þͿ����ˣ���Ϊiλ�ñ������ǡ��յġ� 
		num[i] = num[j]; 
		while (num[i] <= temp && i<j) i++;
		num[j] = num[i];
	}
	num[i] = temp;
	
	QuickSort(num, i);
	QuickSort(num+i+1, n-i-1);	// �˴������ٰ�posλ�õ�������ȥ�����ˣ��� 
} 

// �������е�ɸѡ�㷨
void HeapAdjust(int *num, int n, int pos) {
	int lchild = 2*pos+1, rchild = 2*pos+2;
	int maxPos;
	while (pos<n && lchild<n) {
		if (num[lchild] >= num[rchild]) maxPos = lchild;
		else if (rchild < n) maxPos = rchild;
		
		if (num[pos] < num[maxPos]) {
			int temp = num[maxPos];
			num[maxPos] = num[pos];
			num[pos] = temp;
			
			pos = maxPos;
			lchild = 2*pos+1, rchild = 2*pos+2;
		}
		else break;
	}
}

// ��������ȫ����������
void HeapSort(int *num, int n) { 
	for (int i=n-1; i>=0; i--) {
		HeapAdjust(num, n, i);
	}

	for (int i=n-1; i>0; i--) {
		int temp = num[0];
		num[0] = num[i];
		num[i] = temp;
		HeapAdjust(num, i, 0);
	}
}

int main() {
	int count = 0, limit = 0;
	cout<<"�������������������ĸ���:\n";
	cin>>count;
	cout<<"��������Щ��������(С�ڵ���ĳ����):\n"; 
	cin>>limit;
	
	cout<<"���ɵ�����������������£�\n";
	int *num = (int*)malloc(sizeof(int) * count);
	int *testNum = (int*)malloc(sizeof(int) * count);
	srand(time(0));
	for (int i=0; i<count; i++) {
		num[i] = rand()%limit;
		testNum[i] = num[i];
		cout<<num[i]<<" ";
	}
	cout<<endl;
	
	
	cout<<"\n============================ð������=================================\n";
	timeStart();
	BubbleSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	
	// ���ò�������
	Reset(testNum, num, count);
	cout<<"\n============================ѡ������=================================\n";
	timeStart();
	SelectSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	
	// ���ò�������
	Reset(testNum, num, count);
	cout<<"\n============================�鲢����=================================\n";
	timeStart(); 
	MergerSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	
	// ���ò�������
	Reset(testNum, num, count);
	cout<<"\n============================��������=================================\n";
	timeStart(); 
	QuickSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	// ���ò�������
	Reset(testNum, num, count);
//	int Num[10] = {2, 8, 3, 3, 5, 1, 9, 8, 0, 6};
//	count = 10;
//	Traverse(Num, count);
	cout<<"\n=============================������=================================\n";
	timeStart(); 
	HeapSort(testNum, count);
	timeFinish();
	//Traverse(testNum, count);
	
	free(num);
	free(testNum);
}

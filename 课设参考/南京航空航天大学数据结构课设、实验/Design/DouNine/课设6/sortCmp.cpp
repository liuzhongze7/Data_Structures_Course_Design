/*
[��������]
���������������10��������ÿ��������20000�������������ʹ��һ�����������򣬵ڶ������������򣩣�
����ֱ�Ӳ�������ϣ������ð�����򡢿�������ѡ�����򡢶����򣬹鲢���򡢻�������8�����򷽷�
�������򣨽��Ϊ��С�����˳�򣩣���ͳ��ÿһ�������㷨�Բ�ͬ�������ķѵ�ʱ�䡣
 [����Ҫ��]
��1�� ԭʼ���ݴ����ļ��У�����ͬ�����Բ�ͬ�㷨���в��ԣ�
��2�� ��Ļ��ʾÿ�������㷨�Բ�ͬ����������ʱ�䣻
*/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<queue>

using namespace std;


// ȫ�ֱ��� 
FILE *fp;
char fileName[10];

clock_t start,finish;	// ��ʼʱ�䣬����ʱ�� 
double totalTime;		// �ܵ�ʱ�� 


// ���ļ� 
void fileOpen(char *method) 
{
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    // else printf("file has been opened\n");
}

// �ر��ļ� 
void fileClose() 
{
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    // else printf("file has been closed\n");
    return;
} 

// ��ʼʱ�� 
void timeStart() 
{
	cout<<"����ʼ\n";
	start = clock();
}

// ����ʱ�� 
void timeFinish() 
{
	finish = clock();
   	totalTime = (double)(finish-start)/CLOCKS_PER_SEC;
   	cout<<"�������������ʱ��Ϊ"<<totalTime<<"�룡\n\n";
}

// ���ò�������
void Reset(int *testNum, int *num, int n) 
{
	//cout<<"\n����\n"; 
	for (int i=0; i<n; i++) 
	{
		testNum[i] = num[i];
		//cout<<testNum[i]<<" ";
	}
	//cout<<endl;
} 

// ��������
void Traverse(int *num, int n) 
{
	cout<<"\n�������飺\n"; 
	for (int i=0; i<n; i++) 
	{
		cout<<num[i]<<" ";
	}
	cout<<endl;
}

// ð������
void BubbleSort(int *num, int n) 
{
	for (int i=0; i<n; i++) 
	{
		bool allSort = true;
		for (int j=1; j<n-i; j++) 
		{
			if (num[j] < num[j-1]) 
			{
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
void SelectSort(int *num, int n) 
{
	for (int i=0; i<n; i++) 
	{
		int min = num[i], pos;
		for (int j=i+1; j<n; j++) 
		{
			if (num[j] < min) 
			{
				min = num[j];
				pos = j;
			}
		}
		num[pos] = num[i];
		num[i] = min;
	}
} 

// �������� 
void InsertSort(int *num, int n, int start, int grep) 
{
	// �Ե�i������ǰ�����ź����������� 
	for (int i=start; i<n; i+=grep) 
	{
		// ��jλ����С��j-1λ����ʱ���������������򲻽��� 
		for (int j=i; j>=0+grep && num[j]<num[j-grep]; j-=grep) 
		{
			int temp = num[j];
			num[j] = num[j-grep];
			num[j-grep] = temp;
		}
	}
}

// �鲢����
void MergerSort(int *num, int n) 
{
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
	while (i<mid && j<n) 
	{
		if (num[i] <= num[j]) 
		{
			temp[k] = num[i];
			i++;
		} else 
		{
			temp[k] = num[j];
			j++;
		}
		k++;
	}
	// iָ��δ���м� 
	while (i<mid) 
	{
		temp[k] = num[i];
		k++;
		i++;
	}
	// jָ��δ����β 
	while (j<n) 
	{
		temp[k] = num[j];
		k++;
		j++;
	}
	
	// ������õ�temp���鸳��num 
	for (int i=0; i<n; i++) num[i] = temp[i]; 
	free(temp);
}

// ϣ������ 
void ShellSort(int *num, int n) 
{
	// ��ÿ��5��������������һ����5���������� ����ʼ��ֱ�Ϊ0,1,2,3,4 
	for (int i=0; i<5; i++) InsertSort(num, n, i, 5);
	// ��ÿ��3���������� 
	for (int i=0; i<3; i++) InsertSort(num, n, i, 3);
	InsertSort(num, n, 0, 1);
} 

// ��������
void QuickSort(int *num, int n) 
{
	// �ݹ���ֹ���� 
	if (n <= 1) return;
	
	int i = 0, j = n-1;
	int temp = num[i];	// ��iλ�õ����ȴ�������iλ�������൱�ڡ��ա� 
	while (i<j) 
	{
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
void HeapAdjust(int *num, int n, int pos) 
{
	int lchild = 2*pos+1, rchild = 2*pos+2;	// ���Ӻ��Һ��ӵ�λ�� 
	int maxPos;
	while (pos<n && lchild<n) 
	{
		// �ҵ�����������Ǹ����� 
		if (num[lchild] >= num[rchild]) maxPos = lchild;
		else if (rchild < n) maxPos = rchild;
		
		// ���ɸѡ��С�ں��������ģ���ɸ��ȥ�������� 
		if (num[pos] < num[maxPos]) 
		{
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
void HeapSort(int *num, int n) 
{ 
	// �ӵ��������ɸѡ������С���� 
	for (int i=n-1; i>=0; i--) 
	{
		HeapAdjust(num, n, i);
	}

	// ������һ�������һ�����ٶԵ�һ��ɸѡ 
	for (int i=n-1; i>0; i--) 
	{
		int temp = num[0];
		num[0] = num[i];
		num[i] = temp;
		HeapAdjust(num, i, 0);
	}
}

// ��������
void RadixSort(int *num, int n, int limit) 
{
	queue<int> radix[10];
	
	// i������ 
	for (int i=1; i<limit; i*=10) 
	{
		for (int j=0; j<n; j++) 
		{
			radix[num[j]/i%10].push(num[j]);
		}
		int j=0;
		for (int k=0; k<10; k++) 
		{
			while (!radix[k].empty()) 
			{
				num[j] = radix[k].front();
				radix[k].pop();
				j++;
			}
		}
	}
}


int main() 
{
	int count = 20000, limit = 0;
	int *num = (int*)malloc(sizeof(int) * count);
	int *testNum = (int*)malloc(sizeof(int) * count);
	
	for (int i=1; i<=10; i++) 
	{
		printf("\n*******************��%d������*******************\n", i);
		sprintf(fileName, "data%d.txt", i);
		fileOpen("r");
		fscanf(fp, "%d%d", &count, &limit);
		for (int j=0; j<count; j++) 
		{
			fscanf(fp, "%d", &num[j]);
			testNum[j] = num[j];
		}
		
		cout<<"===ð������===\n";
		timeStart();
		BubbleSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// ���ò�������
		cout<<"===ѡ������===\n";
		timeStart();
		SelectSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// ���ò�������
		cout<<"===��������===\n";
		timeStart();
		InsertSort(testNum, count, 0, 1);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// ���ò�������
		cout<<"===�鲢����===\n";
		timeStart(); 
		MergerSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// ���ò�������
		cout<<"===ϣ������===\n";
		timeStart(); 
		ShellSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// ���ò�������
		cout<<"===��������===\n";
		timeStart(); 
		QuickSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// ���ò�������
		cout<<"===������===\n";
		timeStart(); 
		HeapSort(testNum, count);
		timeFinish();
		//Traverse(testNum, count);
		
		Reset(testNum, num, count);// ���ò�������
		cout<<"===��������===\n";
		timeStart(); 
		RadixSort(testNum, count, limit);
		timeFinish();
		//Traverse(testNum, count);
		
		fileClose();
	}
	
	free(num);
	free(testNum);
}

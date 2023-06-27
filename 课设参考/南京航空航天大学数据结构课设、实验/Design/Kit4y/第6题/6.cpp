/**
 * �Ŵ�����C++
 *
 * @author Kitty
 * @date 2019/1/8
 */
/*
6�������㷨�Ƚ� ��������������
[��������]
���������������10��������ÿ��������20000�������������ʹ��һ�����������򣬵ڶ������������򣩣�����ֱ�Ӳ�������ϣ������ð�����򡢿�������ѡ�����򡢶����򣬹鲢���򡢻�������8�����򷽷��������򣨽��Ϊ��С�����˳�򣩣���ͳ��ÿһ�������㷨�Բ�ͬ�������ķѵ�ʱ�䡣
 [����Ҫ��]
��1�� ԭʼ���ݴ����ļ��У�����ͬ�����Բ�ͬ�㷨���в��ԣ�
��2�� ��Ļ��ʾÿ�������㷨�Բ�ͬ����������ʱ�䣻*/
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>   
#include<time.h> 
#define N 30000
clock_t start,finish;
using namespace std;
char fileName[10][11]={"data_0.txt","data_1.txt","data_2.txt",
					   "data_3.txt","data_4.txt","data_5.txt",
					   "data_6.txt","data_7.txt","data_8.txt",
					   "data_9.txt"};
/*
 * 1����������
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void insertSort(int *a,int n) 
{
	start=clock();
	int i,j,k;
	for(i=1;i<n;i++)
	{
		//Ϊa[i]��ǰ���a[0...i-1]������������һ�����ʵ�λ��
		for(j=i-1;j>=0;j--)
		{
			if(a[j]<a[i])
				break;
		}
		if(j!=i-1)
		{
			//��a[i]��ĺ���
			int temp=a[i];
			for(k=i-1;k>j;k--)
			a[k+1]=a[k];
			 //��a[i]�ŵ���ȷλ����
			a[k+1]=temp;
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"1����������     "<<Time<<"s\n";
}
/*
 * 2��ϣ������
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void shell_sort(int *a, int n)
{
	start=clock();
	int i,j,gap,temp;
	// gapΪ������ÿ�μ�Ϊԭ����һ�롣
	for(gap=n/2;gap>0;gap/=2)
	{
		// ��gap���飬��ÿһ�鶼ִ��ֱ�Ӳ�������
		for(int i=0;i<gap;i++)
		{
			for(j=i+gap;j<n;j+=gap)
			{
				// ���a[j] < a[j-gap]����Ѱ��a[j]λ�ã������������ݵ�λ�ö����ơ�
				if(a[j-gap]>a[j])
				{
					temp=a[j];
					int k=j-gap;
					while(k>=0&&a[k]>temp)
					{
						a[k+gap]=a[k];
						k-=gap;
					}
					a[k+gap]=temp;
				}
			}
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"2��ϣ�������ʱ�� "<<Time<<"s\n";
}
/*
 * 3��ð������
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void bubbleSort(int *a,int n)
{
	start=clock(); 
	int i,j,temp=0;
	for(i=0;i<n;i++)
	{
		 // ���������ݷ���ĩβ
		for(j=n-i-1;j<n-1;j++)
		{
			//n-i-1����ֱ����0���棬��������Ż� 
			if(a[j]>a[j+1])
			{
				// ����a[j]��a[j+1]
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"3��ð�������ʱ�� "<<Time<<"s\n";
}
/*
 * 4����������
 *
 * ����˵����
 *     a -- �����������
 *     l -- �������߽�(���磬����ʼλ�ÿ�ʼ������l=0)
 *     r -- ������ұ߽�(���磬�������������ĩβ����r=a.length-1)
 */
void quickSort(int *a, int l, int r)
{
    if (l < r)
    {
		int i,j,x;

        i = l;
        j = r;
        x = a[i];
        while (i < j)
        {
            while(i < j && a[j] > x)
				j--; // ���������ҵ�һ��С��x����
            if(i < j)
				{
					a[i]=a[j];
					a[j]=x; 
					i++;
				}
            while(i < j && a[i] < x)
				i++; // ���������ҵ�һ������x����
            if(i < j)
				{
					a[j]=a[i];
					a[i]=x;
					j--;
				}
        }
        a[i] = x;
        quickSort(a, l, i-1); /* �ݹ���� */
        quickSort(a, i+1, r); /* �ݹ���� */
    }
}
/*
 * 5��ѡ������
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void selectSort(int* a, int n)
{
	start=clock(); 
	int i;		// ��������ĩβλ��
	int j;		// ����������ʼλ��
	int min;	// ����������СԪ��λ��

	for(i=0; i<n; i++)
	{
		min=i;

		// �ҳ�"a[i+1] ... a[n]"֮�����СԪ�أ�����ֵ��min��
		for(j=i+1; j<n; j++)
		{
			if(a[j] < a[min])
				min=j;
		}

		// ��min!=i���򽻻� a[i] �� a[min]��
		// ����֮�󣬱�֤��a[0] ... a[i] ֮���Ԫ��������ġ�
		if(min != i)
		{
			int tmp = a[i];
			a[i] = a[min];
			a[min] = tmp;
		}
	}
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"5��ѡ�������ʱ�� "<<Time<<"s\n";
}
/* 
 * 6�������� 
 * 6.1��(���)�ѵ����µ����㷨
 *
 * ע������ʵ�ֵĶ��У���N���ڵ�����ӵ�����ֵ��(2N+1)���Һ��ӵ�������(2N+2)��
 *     ���У�NΪ�����±�����ֵ���������е�1������Ӧ��NΪ0��
 *
 * ����˵����
 *     a -- �����������
 *     start -- ���µ��ڵ����ʼλ��(һ��Ϊ0����ʾ�ӵ�1����ʼ)
 *     end   -- ������Χ(һ��Ϊ���������һ��Ԫ�ص�����)
 */
void maxHeapDown(int* a, int start, int end)
{
    int c = start;			// ��ǰ(current)�ڵ��λ��
    int l = 2*c + 1;		// ��(left)���ӵ�λ��
    int tmp = a[c];			// ��ǰ(current)�ڵ�Ĵ�С
    for (; l <= end; c=l,l=2*l+1)
    {
		// "l"�����ӣ�"l+1"���Һ���
        if ( l < end && a[l] < a[l+1])
            l++;		// ������������ѡ��ϴ��ߣ���m_heap[l+1]
        if (tmp >= a[l])
            break;		// ��������
		else			// ����ֵ
        {
            a[c] = a[l];
            a[l]= tmp;
        }
    }
}
/*
 * 6.2��������(mian)
 *
 * ����˵����
 *     a -- �����������
 *     n -- ����ĳ���
 */
void heapSort(int* a, int n)
{
    int i,tmp;

    // ��(n/2-1) --> 0��α���������֮�󣬵õ�������ʵ������һ��(���)����ѡ�
    for (i = n / 2 - 1; i >= 0; i--)
        maxHeapDown(a, i, n-1);

    // �����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
    for (i = n - 1; i > 0; i--)
    {
        // ����a[0]��a[i]��������a[i]��a[0...i]�����ġ�
		tmp = a[0];
		a[0] = a[i];
		a[i] = tmp;
		// ����a[0...i-1]��ʹ��a[0...i-1]��Ȼ��һ�����ѡ�
		// ������֤a[i-1]��a[0...i-1]�е����ֵ��
        maxHeapDown(a, 0, i-1);
    }
}

/*
 * 7���鲢���� 
 * 7.1����һ�������е�����������������ϲ���һ��
 *
 * ����˵����
 *     a -- ���������������������
 *     start -- ��1�������������ʼ��ַ��
 *     mid   -- ��1����������Ľ�����ַ��Ҳ�ǵ�2�������������ʼ��ַ��
 *     end   -- ��2����������Ľ�����ַ��
 */
void merge(int* a, int start, int mid, int end)
{
    int *tmp = new int[end-start+1];	// tmp�ǻ���2������������ʱ����
    int i = start;			// ��1��������������
    int j = mid + 1;		// ��2��������������
    int k = 0;				// ��ʱ���������

    while(i <= mid && j <= end)
    {
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
    }

    while(i <= mid)
        tmp[k++] = a[i++];

    while(j <= end)
        tmp[k++] = a[j++];

	// ��������Ԫ�أ�ȫ�������ϵ�����a�С�
	for (i = 0; i < k; i++)
		a[start + i] = tmp[i];

	delete[] tmp;
}
/*
 * 7.2���鲢����(main)
 *
 * ����˵����
 *     a -- �����������
 *     start -- �������ʼ��ַ
 *     end -- ����Ľ�����ַ,��ʼΪn-1 
 */
void mergeSort(int* a, int start, int end)
{
    if(a==NULL || start >= end)
        return ;

    int mid = (end + start)/2;
    mergeSort(a, start, mid); // �ݹ�����a[start...mid]
    mergeSort(a, mid+1, end); // �ݹ�����a[mid+1...end]

	// a[start...mid] �� a[mid...end]����������ռ䣬
	// �����������һ������ռ�a[start...end]
    merge(a, start, mid, end);
}
/*
 * 8����������
 */
/*
 * 8.1����ȡ����a�����ֵ
 *
 * ����˵����
 *     a -- ����
 *     n -- ���鳤��
*/
int getMax(int a[], int n)
{
	int i, max;

	max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}
/*
 * 8.2�������鰴��"ĳ��λ��"��������(Ͱ����)
 *
 * ����˵����
 *     a -- ����
 *     n -- ���鳤��
 *     exp -- ָ����������a���ո�ָ����������
 *
 * ���磬��������a={50, 3, 542, 745, 2014, 154, 63, 616}��
 *    (01) ��exp=1��ʾ����"��λ"������a��������
 *    (02) ��exp=10��ʾ����"ʮλ"������a��������
 *    (03) ��exp=100��ʾ����"��λ"������a��������
 *    ...
 */
void countSort(int *a, int n, int exp)
{
    int output[n]; 			// �洢"����������"����ʱ����
    int i, buckets[10] = {0};

	// �����ݳ��ֵĴ����洢��buckets[]��
    for (i = 0; i < n; i++)
        buckets[ (a[i]/exp)%10 ]++;

	// ����buckets[i]��Ŀ�����ø��ĺ��buckets[i]��ֵ���Ǹ�������output[]�е�λ�á�
    for (i = 1; i < 10; i++)
        buckets[i] += buckets[i - 1];

    // �����ݴ洢����ʱ����output[]��
    for (i = n - 1; i >= 0; i--)
    {
        output[buckets[ (a[i]/exp)%10 ] - 1] = a[i];
        buckets[ (a[i]/exp)%10 ]--;
    }

	// ������õ����ݸ�ֵ��a[]
    for (i = 0; i < n; i++)
        a[i] = output[i];
}
/*
 * 8.3����������
 *
 * ����˵����
 *     a -- ����
 *     n -- ���鳤��
 */
void radixSort(int *a, int n)
{
	start=clock(); 
    int exp;	// ָ�����������鰴��λ��������ʱ��exp=1����ʮλ��������ʱ��exp=10��...
    int max = getMax(a, n);	// ����a�е����ֵ

	// �Ӹ�λ��ʼ��������a��"ָ��"��������
    for (exp = 1; max/exp > 0; exp *= 10)
		      countSort(a, n, exp);
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"8�����������ʱ�� "<<Time<<"s\n";
}
/*
 * 9��(����)Ͱ��������
 */ 
/*
 * 9.1����ȡ����a�����ֵ
 *
 * ����˵����
 *     a -- ����
 *     n -- ���鳤��
*/
int getMaxforbucket(int *a, int n)
{
	int i, max;

	max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}
/*
 * 9.2��Ͱ����
 *
 * ����˵����
 *     a -- ����������
 *     n -- ����a�ĳ���
 */
void bucketSort(int* a, int n)
{
	int max=getMaxforbucket(a,n)+1;//��ȡ���ֵ 
	int i, j;
    int *buckets;

    if (a==NULL || n<1 || max<1) //�쳣���� 
        return ;

    // ����һ������Ϊmax������buckets�����ҽ�buckets�е��������ݶ���ʼ��Ϊ0��
    if ((buckets = new int[max])==NULL)
        return ;
    memset(buckets, 0, max*sizeof(int));

	// 1. ����
    for(i = 0; i < n; i++) 
        buckets[a[i]]++; 

	// 2. ����
	for (i = 0, j = 0; i < max; i++) 
		while( (buckets[i]--) >0 )
			a[j++] = i;
	delete[] buckets;
}
/*
 *�������� 
 *�����ƴ����� 
 *�����������10������ÿ��������20000���������?
 *��ʹ��һ�����������򣬵ڶ�������������
 *
 */
void PutData()
{
 
	for(int i=0;i<10;i++)
	{
		if(i==0) //���� 
		{
			FILE *out;
			if((out=fopen(fileName[i],"wb"))==NULL)
    		{
       		 printf("Open error.\n");
       		 return;
    		}
			for(int j=0;j<N;j++)
			{
				putw(j,out);
			}
			fclose(out);
			cout<<fileName[i]<<"���������ɹ���"<<endl;
		}
		else if(i==1) //����
		{
			FILE *out;
			if((out=fopen(fileName[i],"wb"))==NULL)
    		{
       		 printf("Open error.\n");
       		 return;
    		}
			for(int j=0;j<N;j++)
			{
				int num=N-j;
				putw(num,out);
			}
			fclose(out);
			cout<<fileName[i]<<"���������ɹ���"<<endl;
		 } 
		 else{
		 	FILE *out;
			if((out=fopen(fileName[i],"wb"))==NULL)
    		{
       		 printf("Open error.\n");
       		 return;
    		}
    		srand((unsigned)time(0)); //�������ʱ������ 
			for(int j=0;j<N;j++)
			{
				int ran_num=rand()%N; 
				putw(ran_num,out);
			}
			fclose(out);
			cout<<fileName[i]<<"���������ɹ���"<<endl;
			 
		 } 
	}
	cout<<"\n======================================\n"<<endl;
}
/*
 * ����������ļ��ж�ȡ������� 
 *����˵����
 *     name -- ����ȡ�ļ��� 
 *     a --  ��ȡ��ֵ��Ŀ������ 
 */
void GetData(char *name,int * a)
{
	FILE *in;
	if((in=fopen(name,"rb"))==NULL)
    {
       printf("error");
       exit(0);
    }
    int j=0;
    while(!feof(in))
  	{
	a[j]=getw(in);
	j=j+1;
  	}
  	fclose(in);
  	return;
}
int main()
{
	double Time;
	int a[N+1];
	PutData();
	for(int i=0;i<10;i++)
	{
	cout<<"���ļ� "<<fileName[i]<<" ��������ʱ����Ϊ��";
	if(i==0) cout<<"(����)"<<endl; 
	else if(i==1) cout<<"(����)"<<endl; 
	else cout<<endl;
	
	GetData(fileName[i],a);		//ÿ�����������õ����� 
	insertSort(a,N); 
	
	GetData(fileName[i],a);
	shell_sort(a,N); 
	
	GetData(fileName[i],a);
	bubbleSort(a,N); 
	 
	GetData(fileName[i],a);
	start=clock();  
	quickSort(a,0,N-1);
	finish=clock();
	Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"4�����������ʱ�� "<<Time<<"s\n";
	
	GetData(fileName[i],a);
	selectSort(a,N); 
	
	GetData(fileName[i],a);
	start=clock();  
	heapSort(a,N);
	finish=clock();
	Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"6���������ʱ��   "<<Time<<"s\n";
	
	GetData(fileName[i],a);
	start=clock();  
	mergeSort(a,0,N-1);
	finish=clock();
	Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"7���鲢�����ʱ�� "<<Time<<"s\n";
	
	GetData(fileName[i],a);
	radixSort(a,N); 
	
	GetData(fileName[i],a);
	start=clock(); 
	bucketSort(a,N); 
	finish=clock();
	double Time=(double)((finish-start))/CLOCKS_PER_SEC;//����ʱ��
	cout<<"9��Ͱ�����ʱ��   "<<Time<<"s\n";
	cout<<"\n======================================\n"<<endl;
	}
	system("pause");
}

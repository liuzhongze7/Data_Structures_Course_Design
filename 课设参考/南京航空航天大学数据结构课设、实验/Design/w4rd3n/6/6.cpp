#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<time.h> 
#define N 40000

clock_t begin,end;
//���ڼ������������ĵ�ʱ�� 
char fileName[10][7]={"1.txt","2.txt","3.txt","4.txt","5.txt",
					  "6.txt","7.txt","8.txt","9.txt","10.txt"};
//����������
int Data[N];
int reData[N];
//�������� 

void insertSort(int a[],int n)
//�������� 
//aΪ����������
//nΪ���鳤�� 
{
	for(int i = 1;i < n;i++)
	{
		int j;
		for(j = i - 1;j >= 0;j--)
		//�ҵ������λ�� 
		{
			if(a[j] < a[i])
				break;
		}
		
		if(j != i - 1)
		//������������ 
		{
			int temp = a[i];
			
			int k;
			for(k = i - 1;k > j;k--)
			//������λ�ü������Ԫ�������һλ 
			{
				a[k + 1]=a[k];
			}
			
			a[k + 1]=temp;
			//����Ԫ�� 
		}
	}
	
	return;
}

void shellSort(int a[],int n)
//ϣ������ 
//aΪ����������
//nΪ���鳤��
{
	for(int gap = n / 2;gap > 0;gap /= 2)
	//���ò���,ÿ�μ��� 
	{
		for(int i = 0;i < gap;i++)
		//��ÿһ��ʹ�ò������� 
		{
			for(int j = i + gap;j < n;j += gap)
			{
				if(a[j - gap] > a[j])
				{
					int temp = a[j];
					int k = j - gap;
					
					while(k >= 0 && a[k] > temp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					
					a[k + gap] = temp;
				}
			}
		}
	}
	
	return;
}

void maopaoSort(int a[],int n)
//ð������ 
//aΪ����������
//nΪ���鳤��
{
	for(int i = 0;i < n;i++)
	//ÿ��ѭ���ҳ�һ����ֵ����ĩβ 
	{
		for(int j = n - i - 1;j < n - 1;j++)
		{
			if(a[j] > a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	
	return;
}

void quickSort(int a[],int l,int r)
//��������
//aΪ����������
//nΪ���鳤��
{
    if(l < r)
    {
    	return;
    }
    
	int i,j,x;

    i = l;
    j = r;
    x = a[i];
    //�ڱ� 
        
    while(i < j)
    {
        while(i < j && a[j] > x)
        //�ҵ�һ��С��x����
        {
        	j--;
		}
			
        if(i < j)
		{
			a[i] = a[j];
			a[j] = x; 
			i++;
		}
			
        while(i < j && a[i] < x)
        //�ҵ�һ������x����
        {
            i++;
		}
			
        if(i < j)
		{
			a[j] = a[i];
			a[i] = x;
			j--;
		}
    }
        
    a[i] = x;
        
    quickSort(a,l,i - 1);
    quickSort(a,i + 1,r);
    
    return;
}

void selectSort(int a[],int n)
//ѡ������
//aΪ����������
//nΪ���鳤��
{
	int min;
	//����������СԪ��λ��

	for(int i = 0; i<n; i++)
	//������������ 
	{
		min = i;

		for(int j = i + 1;j < n;j++)
		//�ҳ�����������СԪ��
		{
			if(a[j] < a[min])
			{
				min = j;
			}
		}
		if(min != i)
		//������֤������Ԫ���������
		{
			int temp = a[i];
			a[i] = a[min];
			a[min] = temp;
		}
	}
	
	return;
}

void heapDown(int a[],int start,int end)
//�������³����� 
//aΪ����������
//startΪ��ʼλ��
//endΪ������Χ
{
    int l = 2 * start + 1;
	//���ӵ�index 
    int r = l + 1;
    //�Һ��ӵ�index 
    int temp = a[start];
    
    while(1)
    {
        if(l < end && a[l] < a[l + 1])
        //ѡ��ϴ���
        {
        	l++;
        	if(temp >= a[r])
        	//��������
        	{
        		break;
			} 
			else
			//����ֵ
        	{
            	a[start] = a[r];
            	a[r] = temp;
        	}
        	
        	start = r;
        	r = 2 * r + 1;
        	
        	if(r > end)
        	{
        		break;
			}
		}
		else
		{
			if(temp >= a[l])
        	//��������
        	{
        		break;
			} 
			else
			//����ֵ
        	{
            	a[start] = a[l];
            	a[l] = temp;
        	}
        	
        	start = l;
        	l = 2 * l + 1;
        	
        	if(l > end)
        	{
        		break;
			}
		}
    }
    
    return;
}

void heapSort(int a[],int n)
//������
//aΪ����������
//nΪ���鳤��
{
	for(int i = n / 2 - 1;i >= 0; i--)
    //��α����õ�һ���������
    {
    	heapDown(a,i,n - 1);
	}

    for(int i = n - 1;i > 0;i--)
    //�����һ��Ԫ�ؿ�ʼ�����н��е���
    {
		int temp = a[0];
		a[0] = a[i];
		a[i] = temp;
		//����ʹa[i]Ϊ���
		
        heapDown(a, 0, i-1);
        //�ָ�����
    }
    
    return; 
}

void merge(int a[],int start,int mid,int end)
//�ϲ���������
//aΪ����ָ��
//start��mid��mid��endΪ�������������� 
{
    int temp[end - start + 1];
	//��źϲ����Ԫ�� 
    int i = start;
	//��1��������������
    int j = mid + 1;
	//��2��������������
    int k = 0;
	//��ʱ���������

    while(i <= mid && j <= end)
    //�ϲ����� 
    {
		if (a[i] <= a[j])
		{
			temp[k++] = a[i++];
		} 
		else
		{
			temp[k++] = a[j++];
		}
    }

    while(i <= mid)
    {
    	temp[k++] = a[i++];
	}

    while(j <= end)
    {
    	temp[k++] = a[j++];
	}
	//��ʣ�������Ԫ�ط���temp 

	for(i = 0;i < k;i++)
	//��������Ԫ�����ϵ�����a
	{
		a[start + i] = temp[i];
	}
	
	return;
}

void mergeSort(int a[],int start,int end)
//�鲢����
//aΪ�����������
//start��endΪ�������ʼ��ַ�ͽ�����ַ
{
    int mid;
    
    if(start >= end)
    {
    	return;
	}
    
	mid = (start + end) / 2;
    mergeSort(a,start,mid);
    mergeSort(a,mid + 1,end);

    merge(a,start,mid,end);
    
    return;
}

void countSort(int a[],int n,int exp)
//�����鰴��ĳ��λ����Ͱ����
//aΪ����������
//nΪ���鳤��
//expΪָ�� 
{
    int temp[n];
	//�洢������Ԫ�ص�����
	int buckets[10] = {0};

    for(int i = 0; i < n; i++)
    //Ͱ����
	{
		buckets[(a[i] / exp) % 10]++;
	}

    for(int i = 1;i < 10;i++)
    //����buckets[i]Ϊ����temp�е�λ��
    {
    	buckets[i] += buckets[i - 1];
	}

    for(int i = n - 1;i >= 0;i--)
    {
        temp[buckets[(a[i] / exp) % 10] - 1] = a[i];
        buckets[(a[i] / exp) % 10]--;
    }

    for(int i = 0;i < n;i++)
    {
    	a[i] = temp[i];
	}
        
    return;
}

void radixSort(int a[], int n)
//��������
//aΪ����������
//nΪ���鳤��
{
    int max;
	// ����a�е����ֵ
	
	max = a[0];
    for(int i = 1;i < n;i++)
    {
    	if(a[i] > max)
    	{
    		max = a[i];
		}
	}

	// �Ӹ�λ��ʼ��������a��"ָ��"��������
    for(int i = 1;max / i > 0;i *= 10)
    {
    	countSort(a,n,i);
	}
	
	return;
}

void setData()
//����10������ÿ��������20000���������
//��ʹǰ�����������ֱ�Ϊ��������� 
//ʹ�ö����ƴ洢 
{
	FILE * out;
 
	for(int i = 0;i < 5;i++)
	{
		srand(time(0));
		for(int j = 0;j < N;j++)
		{
			Data[j] = rand() % 100000;
			reData[N - j - 1] = Data[j];
		}
		
		out = fopen(fileName[i * 2],"wb");
		
		if(!out)
		{
			printf("Error!!!fopen(%s,\"wb\");\n",fileName[i * 2]);
			system("pause");
			exit(1);
		}
		
		fwrite(Data,sizeof(int),N,out);
		fclose(out);
		
		out = fopen(fileName[i * 2 + 1],"wb");
		
		if(!out)
		{
			printf("Error!!!fopen(%s,\"wb\");\n",fileName[i * 2 + 1]);
			system("pause");
			exit(1);
		}
		
		fwrite(reData,sizeof(int),N,out);
		fclose(out);
	}
	
	return;
}

void getData(char name[],int a[])
//ʹ���ļ��е����ݸ�ֵ����a 
{
	FILE * in;
	
	in = fopen(name,"rb");
	
	if(!in)
    {
       	printf("Error!!!fopen(%s,\"rb\");\n",name);
		system("pause");
		exit(1);
    }
    
    fread(a,sizeof(int),N,in);
    
  	fclose(in);
  	
  	return;
}

int main()
{
	double Time;
	
	setData();
	
	for(int i = 0;i < 10;i++)
	{
		printf("the time of sort %s\n",fileName[i]);
		
		getData(fileName[i],Data);
		begin = clock();
		insertSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("1.insertSort:%lf\n",Time);
		
		getData(fileName[i],Data);
		begin = clock();
		shellSort(Data,N); 
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("2.shellSort:%lf\n",Time);
		
		getData(fileName[i],Data);
		begin = clock();
		maopaoSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("3.maopaoSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock();
		quickSort(Data,0,N - 1);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("4.quickSort:%lf\n",Time);
		
		getData(fileName[i],Data);
		begin = clock();
		selectSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("5.selectSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock();
		heapSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("6.heapSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock();  
		mergeSort(Data,0,N - 1);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("7.mergeSort:%lf\n",Time);
	
		getData(fileName[i],Data);
		begin = clock(); 
		radixSort(Data,N);
		end = clock();
		Time = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("8.radixSort:%lf\n",Time);
	
		printf("-------------------------------------------\n\n");
	}
	
	return 0;
}

#pragma once
#include<iostream>
#include<ctime>
using namespace std;
class Sort 
{
public:
	Sort()                                                                              //��������������
	{
		Random_number = 0;
	}               
	~Sort(){}
	void Initial_interface();                                                           //��ʼ������
	long long int Bubble_sort(int* array1,double& sort_time);                           //����ð��������
	long long int Selection_sort(int* array1, double& sort_time);                       //����ѡ��������
	long long int Direct_insertion_sort(int* array1,double& sort_time);                 //����ֱ�Ӳ���������
	long long int Shell_sort(int* array1, double& sort_time);                           //����ϣ��������
	long long int Quick_sort(int* array1, double& sort_time,int l,int r);               //��������������
	long long int Merge_sort(int* array1, double& sort_time);                           //�����鲢������
	int Radix_sort(int* array1, double& sort_time);                                     //��������������
	long long int Heap_sort(int* array1, double& sort_time);                            //������������
	long long int siftDown(int parent, int* data, int number);
	int maxbit(int* array, int n);
	int Random_number;                               //����������ĸ���
};
void Sort::Initial_interface()
{
	cout << "**                 �����㷨�Ƚ�                    **" << endl;
	cout << "=====================================================" << endl;
	cout << "**                 1.ð������                      **" << endl;
	cout << "**                 2.ѡ������                      **" << endl;
	cout << "**                 3.ֱ�Ӳ�������                  **" << endl;
	cout << "**                 4.ϣ������                      **" << endl;
	cout << "**                 5.��������                      **" << endl;
	cout << "**                 6.������                        **" << endl;
	cout << "**                 7.�鲢����                      **" << endl;
	cout << "**                 8.��������                      **" << endl;
	cout << "**                 9.�˳�����                      **" << endl;
	cout << "=====================================================" << endl;
	cout << endl;
	cout << "�����������������:" << endl;
	cin >> Random_number;
}
long long int Sort::Bubble_sort(int* array1,double&sort_time)
{
	int i, j, temp;                                                     //i,jѭ��������temp�洢������Ԫ��
	long long int  exchange_number = 0;                                 //exchange_numberΪ��������
	int* array;
	clock_t start, stop;
	array = new int[Random_number];
	for (i = 0; i < Random_number; i++)
	{
		array[i] = array1[i];
	}
	start = clock();
	for (i = 1; i < Random_number ; i++)                                //����n-1�˱Ƚ�
	{
		for (j = Random_number-1; j > i - 1; j--)                       //�����Ƚ������ϸ�
		{
			if (array[j] < array[j - 1])                                //���н���
			{
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				exchange_number++;
			}
		}
	}
	stop = clock();
	sort_time = ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
long long int Sort::Selection_sort(int* array1, double& sort_time)
{
	int i, j, m, temp;                                            //i,jѭ��������temp�洢������Ԫ��
	long long int exchange_number = 0;                            //exchange_numberΪ��������
	int* array;
	clock_t start, stop;
	array = new int[Random_number];
	for (i = 0; i < Random_number; i++)
	{
		array[i] = array1[i];
	}
	start = clock();
	for (i = 0; i < Random_number-1; i++)                         //Ѱ����СԪ��������ǰ��
	{
		m = i;
		for (j = i + 1; j < Random_number; j++)
		{
			if (array[j] < array[m])
			{
				m = j;
				if (m != i)                                       //�бȸ�λ��С��Ԫ�أ����н���
				{
					temp = array[i];
					array[i] = array[m];
					array[m] = temp;
					exchange_number++;
				}
			}
		}
	}
	stop = clock();
	sort_time = ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
long long int Sort::Direct_insertion_sort(int* array1,double& sort_time)
{
	int i, j, temp;
	long long int exchange_number = 0;           //i,jѭ��������temp�洢������Ԫ��,exchange_numberΪ��������
	int* array;
	clock_t start, stop;                         //��¼ʱ��
	array = new int[Random_number];
	for (i = 0; i < Random_number; i++)
	{
		array[i] = array1[i];
	}
	start = clock();
	for (i = 1; i < Random_number; i++) 
	{
		j = i;
		temp = array[i];                         //������Ԫ�ظ�ֵ����ʱ����
		while (j > 0 && temp < array[j - 1]) 
		{                                        //��δ�ﵽ����ĵ�һ��Ԫ�ػ��ߴ�����Ԫ��С�ڵ�ǰԪ��
			array[j] = array[j - 1];             //�ͽ���Ԫ�غ���
			j--;                                 //�±��һ�������Ƚ�
			exchange_number++;                   //����������һ
		}
		array[j] = temp;                         //����λ���Ѿ��ҵ�����������
	}
	stop = clock();
	sort_time= ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
long long int Sort::Shell_sort(int* array1, double& sort_time)
{
	int i, j, temp;
	long long int exchange_number = 0;                      //i,jѭ��������temp�洢������Ԫ��,exchange_numberΪ��������
	int gap=0;
	int* array;
	clock_t start, stop;                                                       //��¼ʱ��
	array = new int[Random_number];
	for (i = 0; i < Random_number; i++)
	{
		array[i] = array1[i];
	}
	gap = Random_number;                                                       //������
	start = clock();
	do {	                                                                   //ÿ�μ�С������ֱ��increment = 1
		gap = gap / 3 + 1;
		for (int i = gap; i < Random_number; i++) 
		{	                                                                   //��ÿ�����ֽ���ֱ�Ӳ�������
			if (array[i - gap] > array[i]) 
			{
				temp = array[i];
				j = i - gap;
				do {	                                                       //�ƶ�Ԫ�ز�Ѱ��λ��
					array[j + gap] = array[j];
					j = j-gap;
				} while (j >= 0 && array[j] > temp);
				array[j + gap] = temp;	                                       //����Ԫ��
				exchange_number++;
			}
		}
	} while (gap > 1);
	stop = clock();
	sort_time = ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
long long int Sort::Quick_sort(int* array2, double& sort_time,int l,int r)
{
	long long int exchange_number = 0;                     //exchange_numberΪ��������
	clock_t start, stop;                         //��¼ʱ��
	start = clock();
	if (l < r)
	{
		int i = l, j = r, x = array2[l];
		while (i < j)
		{
			while (i < j && array2[j] >= x)        // ���������ҵ�һ��С��x����
			{
				j--;
			}
			if (i < j)
			{
				array2[i++] = array2[j];
				exchange_number++;
			}
			while (i < j && array2[i] < x)         // ���������ҵ�һ�����ڵ���x����
			{
				i++;
			}
			if (i < j)
			{
				array2[j--] = array2[i];
				exchange_number++;
			}
		}
		array2[i] = x;
		exchange_number= exchange_number+Quick_sort(array2, sort_time,l, i - 1); // �ݹ���� 
		exchange_number= exchange_number+Quick_sort(array2, sort_time, i + 1, r);
	}
	stop = clock();
	sort_time = ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
long long int Sort::Heap_sort(int* array1, double& sort_time)
{
	int i;           //i,jѭ��������temp�洢������Ԫ��
	long long int exchange_number = 0;//exchange_numberΪ��������
	int* array;
	int temp = Random_number;
	clock_t start, stop;                         //��¼ʱ��
	array = new int[Random_number +1];
	for (i = 0; i < Random_number; i++)
	{
		array[i+1] = array1[i];
	}
	start = clock();
	for (int i = Random_number / 2; i > 0; i--)      //����
	{
		exchange_number=siftDown(i,array, Random_number);
	}
	for (i = 0; i < Random_number; i++)
	{
		//cout << array[1]<<" ";                                        //������СԪ��
		array[1] = array[temp];                                //��βԪ�ش����±�Ϊ1��λ��
		temp--;
		exchange_number= exchange_number+siftDown(1, array, temp);                                //�Ӷ������µ���
	}
	stop = clock();
	sort_time = ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
long long int Sort::Merge_sort(int* array1, double& sort_time)
{
	int i;                                        //i,jѭ��������temp�洢������Ԫ��,
	long long int exchange_number = 0;            //exchange_numberΪ��������
	int* array;
	clock_t start, stop;                         //��¼ʱ��
	array = new int[Random_number];
	for (i = 0; i < Random_number; i++)
	{
		array[i] = array1[i];
	}
	start = clock();
	int* a = array;
	int* b = new int[Random_number];
	for (int seg = 1; seg < Random_number; seg += seg) {
		for (int start = 0; start < Random_number; start += seg + seg) {
			int low = start, mid = (start + seg)< Random_number ? (start + seg): Random_number, high = (start + seg + seg)< Random_number ? (start + seg + seg): Random_number;
			int k = low;
			int start1 = low, end1 = mid;
			int start2 = mid, end2 = high;
			while (start1 < end1 && start2 < end2)
			{
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
				exchange_number++;
			}
			while (start1 < end1)
				b[k++] = a[start1++];
			while (start2 < end2)
				b[k++] = a[start2++];
		}
		int* temp = a;
		a = b;
		b = temp;
	}
	if (a != array) {
		for (int i = 0; i < Random_number; i++)
			b[i] = a[i];
		b = a;
	}
	delete[] b;
	stop = clock();
	sort_time = ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
int Sort::Radix_sort(int* array1, double& sort_time)
{
	int i, j,k,exchange_number = 0;            //i,jѭ��������temp�洢������Ԫ��,exchange_numberΪ��������
	int* array;
	clock_t start, stop;                         //��¼ʱ��
	array = new int[Random_number];
	for (i = 0; i < Random_number; i++)
	{
		array[i] = array1[i];
	}
	start = clock();
	int d = maxbit(array, Random_number);
	int* temp = new int[Random_number];
	int* count = new int[10]; //������
	int radix = 1;
	for (i = 1; i <= d; i++) //����d������
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //ÿ�η���ǰ��ռ�����
		for (j = 0; j < Random_number; j++)
		{
			k = (array[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
		for (j = Random_number - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
		{
			k = (array[j] / radix) % 10;
			temp[count[k] - 1] = array[j];
			count[k]--;
		}
		for (j = 0; j < Random_number; j++) //����ʱ��������ݸ��Ƶ�data��
			array[j] = temp[j];
		radix = radix * 10;
	}
	delete[]temp;
	delete[]count;
	stop = clock();
	sort_time = ((double)(stop - start)) / CLK_TCK;
	return exchange_number;
}
long long int Sort::siftDown(int parent ,int *data,int number)              //��parent��ʼ���µ���
{
	int child;
	long long int exchange_time=0;
	int temp = data[parent];                                //����parent�����
	for (; parent * 2 <= number; parent = child)
	{
		child = parent * 2;                               //child���ڼ�¼��С���ӽڵ�
		if (child != number && data[child + 1] < data[child])
		{
			child++;                                      //�Һ��Ӹ�С
		}
		if (data[child] < temp)                           //���Һ�����һ���ȸ��ڵ�С
		{
			data[parent] = data[child];                   //���н���
			exchange_time++;
		}
		else                                              //��û����ֹͣ
		{
			break;
		}
		data[child] = temp;
	}
	return exchange_time;
}
int Sort::maxbit(int* array, int n) //���������������ݵ����λ��
{
	int maxData = array[0];              ///< �����
	/// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
	for (int i = 1; i < n; ++i)
	{
		if (maxData < array[i])
			maxData = array[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		maxData /= 10;
		++d;
	}
	return d;
}

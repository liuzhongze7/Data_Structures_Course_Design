
#include"RadixSort.h"
#include<time.h>
int main() {
	clock_t start_time=clock();
	{
		insertsortRT();
	}
	clock_t  end_time=clock();
	cout<<"ֱ�Ӳ���˳��ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��
	start_time=clock();
	{
		insertsortLT();
	}
	end_time=clock();
	cout<<"ֱ�Ӳ�������ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
	start_time=clock();
	{
		ShellSortRT();
	}
	end_time=clock();
	cout<<"ϣ������˳��ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
	start_time=clock();
	{
		ShellSortLT();
	}
	end_time=clock();
	cout<<"ϣ����������ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
	
		start_time=clock();
	{
		BubbleSortRT();
	}
	end_time=clock();
	cout<<"ð������˳��ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
		start_time=clock();
	{
		BubbleSortLT();
	}
	end_time=clock();
	cout<<"ð����������ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
		start_time=clock();
	{
		QuickSortRT();
	}
	end_time=clock();
	cout<<"��������˳��ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
			start_time=clock();
	{
		QuickSortLT();
	}
	end_time=clock();
	cout<<"������������ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
		
		start_time=clock();
	{
		SelecSortRT();
	}
	end_time=clock();
	cout<<"ѡ������˳��ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
			start_time=clock();
	{
		SelecSortLT();
	}
	end_time=clock();
	cout<<"ѡ����������ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
			start_time=clock();
	{
		MergeSortRT();
	}
	end_time=clock();
	cout<<"�鲢����˳��ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
	start_time=clock();
	{
		MergeSortLT();
	}
	end_time=clock();
	cout<<"�鲢��������ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
	
	start_time=clock();
	{
		HEAPSORT();
	}
	end_time=clock();
	cout<<"����������ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
	
	start_time=clock();
	{
		RadixSort();
	}
	end_time=clock();
	cout<<"��������˳��ʱ����:"<<static_cast<double>(end_time-start_time)/CLOCKS_PER_SEC*1000<<"ms"<<endl;//�������ʱ��  
	
	return 0;
}

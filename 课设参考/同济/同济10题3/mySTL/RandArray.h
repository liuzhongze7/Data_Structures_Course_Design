#pragma once
#include<cstdlib>
#include<time.h>
namespace mySTL
{

	//������arrays���ڲ���number��[min,max]�����ڵ������
	void randomArray(int *arrays, int number, unsigned int seed = 0)
	{
		srand(!seed ? seed : (unsigned int)time(NULL));
		for (int i = 0; i < number; ++i)
			arrays[i] = rand() % number;
	}

	//������arrays�ڲ���number��������
	void ascendArray(int *arrays, int number)
	{
		for (int i = 0; i < number; ++i)
			arrays[i] = i;
	}

	//������arrays�ڲ���number��������
	void descendArray(int *arrays, int number)
	{
		for (int i = 0; i < number; ++i)
			arrays[i] = number - i;
	}

};
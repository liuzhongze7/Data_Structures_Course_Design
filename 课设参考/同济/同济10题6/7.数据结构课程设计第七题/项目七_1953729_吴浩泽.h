#pragma once
#include<iostream>
using namespace std;
template<class T>
class Queue                                       //����ģ���ഴ��
{
public:
	virtual ~Queue() {}                           //����������
	virtual int size()const = 0;                  //����г���
	virtual void In_Queue(T& x) = 0;              //�����
	virtual T Out_Queue() = 0;                    //������
	virtual bool Is_empty()const = 0;             //�ж϶����Ƿ�Ϊ��
};
class outOfRange :public exception                //�Զ����쳣������
{
public:
	const char* what()const throw()
	{
		return "ERROR!OUT OF RANGE.\n";
	}
};
template<class T>
class Priority_Queue :public Queue<T>
{
private:
	int Queue_size;                               //������Ԫ�ظ���
	T* data;                                      //ָ����Ԫ�������ָ��
	int maxsize;                                  //�������������
	void siftDown(int parent);                    //��parentλ�����µ������ȼ�����
	void siftUp(int position);                    //��position��λ�����ϵ������ȼ�����
public:
	Priority_Queue()                              //���캯��
	{
		Queue_size=NULL;                               
		data=NULL;                                     
		maxsize = NULL;
	}
	~Priority_Queue() { delete[]data;}
	bool Is_empty()const { return Queue_size==0; }//�����п�
	int size()const { return Queue_size; }        //����г���
	void buildheap();                             //����
	void In_Queue(T& x);                          //�����
	T Out_Queue();                                //������
};
template<class T>
void Priority_Queue<T>::buildheap()
{
	cin >> maxsize;                               //ȷ�����Ķ���
	Queue_size = maxsize;
	data = new T[maxsize+1];                      //��������
	for (int i = 0; i < Queue_size; i++)          //�������Ԫ��
	{
		cin >> data[i+1];
	}
	for (int i = Queue_size / 2; i > 0; i--)      //����
	{
		siftDown(i);
	}
}
template<class T>
void Priority_Queue<T>::In_Queue(T& x)            //����в���
{
	Queue_size++;                                 //������Ԫ��++
	data[Queue_size] = x;                         //��Ԫ�����β
	siftUp(Queue_size);                           //���ϵ�����Ԫ��λ��
}
template<class T>
void Priority_Queue<T>::siftUp(int position)
{
	T temp = data[position];                      //����positionλ��Ԫ��
	for (; position > 1 && temp < data[position / 2]; position = position / 2)  //�����Ԫ�ر��丸�ڵ�ֵС�����Ͻ��н���
	{
		data[position] = data[position / 2];                                    //������Ԫ��λ��
		data[position] = temp;
	}
}
template<class T>
T Priority_Queue<T>::Out_Queue()
{
	if (Is_empty())                                       //������Ϊ�գ��������쳣
	{
		throw outOfRange();
	}
	T min;
	min = data[1];                                        //������СԪ��
	data[1] = data[Queue_size];                           //��βԪ�ش����±�Ϊ1��λ��
	Queue_size--;                                         
	siftDown(1);                                          //�Ӷ������µ���
	return min;                                           //���ض���Ԫ��
}
template<class T>
void Priority_Queue<T>::siftDown(int parent)              //��parent��ʼ���µ���
{
	int child;
	T temp = data[parent];                                //����parent�����
	for (; parent * 2 <= Queue_size; parent = child)
	{
		child = parent * 2;                               //child���ڼ�¼��С���ӽڵ�
		if (child != Queue_size && data[child + 1] < data[child])
		{
			child++;                                      //�Һ��Ӹ�С
		}
		if (data[child] < temp)                           //���Һ�����һ���ȸ��ڵ�С
		{
			data[parent] = data[child];                   //���н���
		}
		else                                              //��û����ֹͣ
		{
			break;
		}
		data[child] = temp;
	}
}
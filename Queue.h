#pragma once
#include<iostream>
using namespace std;
template<class T>
class Queue                                       //����ģ���ഴ��
{
public:
	virtual void clear() = 0;                     //���������
	virtual int size()const = 0;                  //����г���
	virtual void In_Queue(T& x) = 0;              //�����
	virtual T Out_Queue() = 0;                    //������
	virtual T Read_Queue()const = 0;              //��ȡ��ͷԪ��
	virtual bool Is_empty()const = 0;             //�ж϶����Ƿ�Ϊ��
};
template<class T>
class Link_Queue :public Queue<T>
{
public:
	Link_Queue() { front = NULL; rear = NULL; }   //���캯������ͷ����βָ���ÿ�
	~Link_Queue() { clear(); }                    //���������������
	void clear();                                 //���������
	int size()const;                              //����г���
	void In_Queue(T& x);                          //�����
	T Out_Queue();                                //������
	T Read_Queue()const;                          //��ȡ��ͷԪ��
	bool Is_empty()const;                         //�ж϶����Ƿ�Ϊ��
private:
	struct Link_node                              //���н�㣬���������Լ�ָ��
	{
		T data;
		Link_node* next;
	};
	Link_node* rear, * front;                     //��β����ͷָ��
};
template<class T>
void Link_Queue<T>::clear()                      //��ն���
{
	Link_node* p;
	while (front != NULL)                        //������ͷָ�벻Ϊ�գ������в�Ϊ��ʱ������ͷָ��������ɾ������Ԫ��
	{
		p = front;
		front = front->next;
		delete p;
	}
	rear = NULL;                                //��βָ���ÿ�
}
template<class T>
int Link_Queue<T>::size()const
{
	Link_node* p = front;
	int count = 0;
	while (p != NULL)                           //��ͷָ�벻Ϊ��ʱ���κ��ơ�count++�����м���
	{
		count++;
		p = p->next;
	}
	return count;
}
template<class T>
void Link_Queue<T>::In_Queue(T& x)
{
	Link_node* p = new Link_node;
	if (p == NULL)
	{
		cout << "�洢�������" << endl;      //��鿪���½���Ƿ�ɹ�
		exit(1);
	}
	if (rear == NULL)                          //����˶�������Ԫ������в����һ��Ԫ�ز���
	{
		p->data = x;
		rear = p;
		front = p;
		rear->next = NULL;
	}
	else                                       //�����������Ԫ��������ڶ�β�������
	{
		p->data = x;
		rear->next = p;
		rear = p;
		rear->next = NULL;
	}
}
template<class T>
T Link_Queue<T>::Out_Queue()
{
	Link_node* p=front;
	T x;
	while (front != NULL)                         //�ж϶������Ƿ���Ԫ��
	{
		if (p == NULL)
		{
			cout << "�洢�������" << endl;    //�жϽ�������Ƿ�ɹ�
			exit(1);
		}
		else                                     //����ɹ�����ͷָ������ֵ������ͷָ�����
		{
			p = front;
			x = p->data;
			front = front->next;
			if (front == NULL)                   //ԭ��ֻ��һ��Ԫ�س��Ӻ����Ϊ��
			{
				rear == NULL;                    //�޸Ķ�βָ��
			}
			delete p;
			return x;
		}
	}
}
template<class T>
T Link_Queue<T>::Read_Queue()const
{
	if (front != NULL)                                //�����������Ԫ�أ����ض�ͷԪ�ص�ֵ
	{
		return front->data;
	}
	else
	{
		cout << "��������Ԫ�أ����ɶ�ȡ������Ԫ" << endl;
	}
}
template<class T>
bool Link_Queue<T>::Is_empty()const
{
	if (rear == NULL||front==NULL)       //ͷָ�����βָ��Ϊ�������Ϊ��
	{
		return true;
	}
	else
	{
		return false;
	}
}
class Compare_Queue                            //�Ƚ϶�����
{
private:
	Link_Queue<int>Queue_A;                    //��������int�Ͷ���
	Link_Queue<int>Queue_B;
	Link_Queue<int>Queue_C;
public:
	Compare_Queue() {};                        //���캯��
	~Compare_Queue() {};                       //��������
	void Handling();                           //����ҵ��ʵ�ֺ���
};
void Compare_Queue::Handling()
{
	int sum,number=0,data;                     //�ܵ��Ŷ�����sum�� ��ͬ�˵ı��number��������ʱ�洢����
	int A_size,B_size,C_size;                  //��¼A,B,C���еĳ���
	cin >> sum;
	for (int i = 0; i < sum; i++)              //ѭ�������������Լ���Ա���
	{
		cin >> number;
		if ((number % 2) == 0)                 //��Ա���Ϊż������B����
		{
			Queue_B.In_Queue(number);
		}
		else                                   //��Ա���Ϊ��������A����
		{
			Queue_A.In_Queue(number);
		}
	}
	while ((Queue_A.size() >= 2) && (Queue_B.Is_empty() == false))    //��A���л�����������Ԫ�أ���B���в�Ϊ��ʱ
	{
		data = Queue_A.Out_Queue();                                   //���A�����е�����Ԫ�أ�B�����е�һ��Ԫ��
		Queue_C.In_Queue(data);
		data = Queue_A.Out_Queue();
		Queue_C.In_Queue(data);
		data = Queue_B.Out_Queue();
		Queue_C.In_Queue(data);
	}
	if ((Queue_A.size() < 2) && (Queue_B.Is_empty() == false))        //��A������Ԫ������2��B���в�Ϊ��ʱ
	{
		B_size = Queue_B.size();
		A_size = Queue_A.size();
		for (int i = 0; i < A_size; i++)                              //�Ƚ�A����Ԫ��ȫ��������ٽ�B����Ԫ��ȫ�����
		{
			data = Queue_A.Out_Queue();
			Queue_C.In_Queue(data);
		}
		for (int i = 0; i < B_size; i++)
		{
			data = Queue_B.Out_Queue();
			Queue_C.In_Queue(data);
		}
	}
	if (Queue_B.Is_empty() == true)                                   //���B������Ԫ��Ϊ��
	{
		A_size = Queue_A.size();
		for (int i = 0; i < A_size; i++)                              //��A��Ԫ��ȫ������C��
		{
			data = Queue_A.Out_Queue();
			Queue_C.In_Queue(data);
		}
	}
	if (Queue_C.Is_empty() == false)                                  //���C����Ԫ��
	{
		C_size = Queue_C.size();
		for (int i = 0; i < C_size; i++)                              //��C��Ԫ��ȫ�����
		{
			data=Queue_C.Out_Queue();
			cout << data;
			if (C_size - 1 != i)                                      //��֤C���Ԫ�����һ����������
			{
				cout << " ";
			}
		}
	}
	else                                                              //C����Ԫ��
	{
		cout << "�������Ŷ�" << endl;
	}
}
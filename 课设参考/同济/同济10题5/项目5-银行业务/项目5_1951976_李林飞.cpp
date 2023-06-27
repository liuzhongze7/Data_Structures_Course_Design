/*
* FileName:  BankBusiness.cpp  
* Author:    ���ַ�
* StuNumber: 1951976
* Date:      2020.12.13
*/

#include <iostream>
using namespace std;

/*
������Ϳ��Ժܺõ�ʵ�֣���Ϊ����ϰ��дһ������
*/

/*========================================= ����ģ���� ============================================*/
/*==== ���н���� ===*/
template<class Type>
struct QueueNode
{
	Type data;
	QueueNode<Type>* link;
	QueueNode(QueueNode<Type>* next = NULL):link(next){}
	QueueNode(Type d, QueueNode<Type>* next = NULL):data(d),link(next){}
};

/*==== ����ģ���� ====*/
template<class Type>
class Queue
{
private:
	QueueNode<Type>* front;    // ��ͷ
	QueueNode<Type>* rear;     // ��β
public:
	Queue() :front(NULL), rear(NULL) {}  // ���캯��
	~Queue();                            // ��������
	Type Front();                        // ���ض���Ԫ��
	Type Back();                         // ���ض�βԪ��
	void Push(const Type & item);        // ���
	void Pop();                          // ����
	bool Empty();                        // �п�
	int Size();                          // ����
};

// ��������
template<class Type>
Queue<Type>::~Queue()
{
	QueueNode<Type>* p;
	while (front)
	{
		p = front;
		front = front->link;
		delete p;
	}
}

// ���ض���Ԫ��
template<class Type>
Type Queue<Type>::Front()
{
	return front->data;
}

// ���ض�βԪ��
template<class Type>
Type Queue<Type>::Back()
{
	return rear->data;
}

// ���
template<class Type>
void Queue<Type>::Push(const Type& item)
{
	if (front == NULL)  // �ն���
	{
		front = rear = new QueueNode<Type>(item);
		if (front == NULL) {
			cout << "�ռ����ʧ�ܣ�" << endl;
			exit(1);
		}
	}
	else  // �ǿն���
	{
		rear->link = new QueueNode<Type>(item);
		if (rear->link == NULL) {
			cout << "�ռ����ʧ�ܣ�" << endl;
			exit(1);
		}
		rear = rear->link;    // ����βָ��
	}
}

// ����
template<class Type>
void Queue<Type>::Pop()
{
	if (Empty())
	{
		cerr << "Attempt to pop the empty queue!" << endl;
		exit(1);
	}
	QueueNode<Type>* q = front;
	front = front->link;
	delete q;
}

// �п�
template<class Type>
bool Queue<Type>::Empty()
{
	return front == NULL;
}

// ���㳤��
template<class Type>
int Queue<Type>::Size()
{
	int length = 0;
	QueueNode<Type>* p = front;
	while (p)
	{
		length++;
		p = p->link;
	}
	return length;
}


/*========================================== ������ ==============================================*/
int main()
{
	cout << "********************************\n";
	cout << "**                            **\n";
	cout << "**         ����ҵ��ϵͳ       **\n";
	cout << "**                            **\n";
	cout << "********************************\n\n";

	char tag;
	do
	{
		Queue<int> QEven, QOdd;
		// ���
		cout << "�˿�����Ϊ�� ";
		int n;
		cin >> n;
		while (n < 0)
		{
			cout << "������󣬹˿�����ӦΪ�����������������룺 ";
			cin >> n;
		}

		// ����������
		cout << "�˿ͱ��Ϊ�� ";
		int x;
		while (n--)
		{
			cin >> x;
			while (x < 0)
			{
				cout << "������󣬹˿ͱ��ӦΪ�����������������룺 ";
				cin >> x;
			}

			if (x % 2)
				QOdd.Push(x);
			else
				QEven.Push(x);
		}

		// ����
		if (QOdd.Empty())        // ������û������
			while (!QEven.Empty())
			{
				cout << QEven.Front() << " ";
				QEven.Pop();
			}
		else if (QEven.Empty())  // ������û��ż��
			while (!QOdd.Empty())
			{
				cout << QOdd.Front() << " ";
				QOdd.Pop();
			}
		else                   // �����м�������Ҳ��ż��
		{
			int i;
			cout << "����ҵ��˳��Ϊ�� \n";
			while (!QOdd.Empty())
			{
				int cnt = 2;
				i = 0;
				while (cnt-- && !QOdd.Empty())    //������������
				{
					if (i++) cout << " ";
					cout << QOdd.Front();
					QOdd.Pop();
				}
				if (!QEven.Empty())             //����һ��ż��
				{
					cout << " " << QEven.Front() << " ";
					QEven.Pop();
				}
			}

			// 
			i = 0;
			while (!QEven.Empty())     //�Ѷ����ż������
			{
				if (i++) cout << " ";
				cout << QEven.Front();
				QEven.Pop();
			}

			i = 0;
			while (!QOdd.Empty())      //�Ѷ����ż������
			{
				if (i++) cout << " ";
				cout << QOdd.Front();
				QOdd.Pop();
			}
		}
		cout << endl << endl;
		cout << "�������ԣ� (y or n): ";
		cin >> tag;
	} while (tag == 'y');

	return 0;
}

/*
* FileName: OrderedList.cpp
* Function: ��������������Ľ������������
* Author: ���ַ�
* StuNumber: 1951976
* Date: 2020.12.08
*/


#include <iostream>
using namespace std;

/*================================ ����� ==================================*/
struct ListNode
{
		int data;
		ListNode * link = NULL;
		ListNode():link(NULL){}        // ���캯��
		ListNode(const int & d, ListNode *l = NULL) : data(d), link(l){}  // ���캯��
};


/*=============================== ���������� ==============================*/
class OrderedList
{
private:
	ListNode * first;       // ͷ�ڵ��ʶ��������
	ListNode *rear;         // βָ��     
public:
	OrderedList();          // ���캯��
	~OrderedList();         // ��������

	// ���غ�����+ :�󲢼�  * :�󽻼�  - :��  = ����ֵ 
	OrderedList & operator=(OrderedList & list1);
	void Create();          // ������������
	void Print();           // ��ӡ��������
	friend OrderedList & operator+(OrderedList & list1, OrderedList & list2);  
	friend OrderedList & operator*(OrderedList & list1, OrderedList & list2);
	friend OrderedList & operator-(OrderedList & list1, OrderedList & list2);
};




/*================================ ������ ======================================*/
void Interface();     // ��ʼ�����溯������
int main()
{
	Interface();
	char tag;    // ���Ա�־
	do
	{
		OrderedList S1, S2, S3, S4, S5;
		cout << "������ǽ�������S1����-1��־��β����\n";
		S1.Create();
		cout << "������ǽ�������S2����-1��־��β����\n";
		S2.Create();
		S3 = S1 + S2;
		cout << "������Ĳ���S3��\n";
		S3.Print();
		S4 = S1 * S2;
		cout << "������Ľ���S4��\n";
		S4.Print();
		cout << "������ĲS5��\n";
		S5 = S1 - S2;
		S5.Print();

		cout << "\n�������ԣ�(y or n): ";
		cin >> tag;
	} while (tag == 'y');
	return 0;
}


/*=========================== ��ʼ�����溯�� ===================================*/
void Interface()
{
	cout << "***************************************\n";   //����
	cout << "**                                   **\n";
	cout << "**         �ǽ����������            **\n";
	cout << "**           ֧�ֹ��ܣ�              **\n";
	cout << "**              +���󲢼�            **\n";
	cout << "**              -����            **\n";
	cout << "**              *���󽻼�            **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
}


/*=============================== ������������� =================================*/
// ���캯��
OrderedList::OrderedList()
{
	first = rear = new ListNode;
	first->link = rear->link = NULL;
}

// ��������
OrderedList::~OrderedList()
{
	ListNode * q = nullptr;
	while (first->link)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	delete first;
}

// ��������� = ���� ��ֵ����
OrderedList & OrderedList::operator=(OrderedList & list1)
{
	ListNode* p1 = list1.first->link;   // list1ɨ��ָ��
	ListNode* p = first = new ListNode; // Ŀ������ָ��
	while (p1)
	{
		p->link = new ListNode(p1->data);
		p = p->link;
		p1 = p1->link;
	}
	p->link = NULL;
	rear = p;
	return *this;
}

// ������������
void OrderedList::Create()
{
	int x;     // ��x=-1ʱ��ʾ����
	ListNode* newNode;
	first->link = rear;
	while (1)
	{
		cin >> x;
		if (x != -1)
		{
			newNode = new ListNode(x);
			rear->link = newNode;
			rear = newNode;
		}
		else
		{
			rear->link = NULL;
			break;
		}
	}
}

// �����������
void OrderedList::Print()
{
	ListNode* p = first->link;
	if (p == NULL) 
		cout << "NULL";
	else
		while (p)
		{
			cout << p->data << " ";
			p = p->link;
		}
	cout << endl;
}

// ��������� + ���� �󲢼�
OrderedList & operator+(OrderedList& list1, OrderedList& list2)
{
	if (list1.first->link == NULL)
		return list2;
	if (list2.first->link == NULL)
		return list1;

	ListNode* p1 = list1.first->link;          // list1���������ɨ��ָ��
	ListNode* p2 = list2.first->link;          // list2���������ɨ��ָ��
	static OrderedList ans;
	ListNode* p = ans.first;                  // ��������ɨ��ָ��
	while (p1 && p2)                          // ������������ͬʱɨ�裬С�ļ����µ�������
	{
		if (p1->data == p2->data)
		{
			p->link = new ListNode(p1->data);
			p1 = p1->link;
			p2 = p2->link;
		}
		else if (p1->data < p2->data)
		{
			p->link = new ListNode(p1->data);
			p1 = p1->link;
		}
		else
		{
			p->link = new ListNode(p2->data);
			p2 = p2->link;
		}
		p = p->link;
	}

	// ����δɨ�赽������
	ListNode* pr = p1 != NULL ? p1 : p2;  // prָ����ʣ�������
	while (pr)
	{
		p->link = new ListNode(pr->data);
		pr = pr->link;
		p = p->link;
	}
	p->link = NULL;    // βָ�봦��
	ans.rear = p;
	return ans;
}

// ��������� * ���� �󽻼�
OrderedList& operator*(OrderedList& list1, OrderedList& list2)
{
	if (list1.first->link == NULL || list2.first->link == NULL)
		return list1;

	ListNode* p1 = list1.first->link;          // list1���������ɨ��ָ��
	ListNode* p2 = list2.first->link;          // list2���������ɨ��ָ��
	static OrderedList ans;
	ListNode* p = ans.first;                  // ��������ɨ��ָ��
	while (p1 && p2)                          // ������������ͬʱɨ�裬С�ļ����µ�������
	{
		if (p1->data == p2->data)
		{
			p->link = new ListNode(p1->data);
			p = p->link;
			p1 = p1->link;
			p2 = p2->link;
		}
		else if (p1->data < p2->data)
			p1 = p1->link;
		else
			p2 = p2->link;
	}
	
	p->link = NULL;    // βָ�봦��
	ans.rear = p;
	return ans;
}

// ��������� - ���� ��
OrderedList& operator-(OrderedList& list1, OrderedList& list2)
{
	if (list1.first->link == NULL)
		return list1;
	if (list2.first->link == NULL)
		return list1;

	ListNode* p1 = list1.first->link;          // list1���������ɨ��ָ��
	ListNode* p2 = list2.first->link;          // list2���������ɨ��ָ��
	static OrderedList ans;
	ListNode* p = ans.first;                  // ��������ɨ��ָ��
	while (p1 && p2)                          // ������������ͬʱɨ�裬С�ļ����µ�������
	{
		if (p1->data == p2->data)
		{
			p1 = p1->link;
			p2 = p2->link;
		}
		else if (p1->data < p2->data)
		{
			p->link = new ListNode(p1->data);
			p = p->link;
			p1 = p1->link;
		}
		else
			p2 = p2->link;
	}
	// ����δɨ�赽������
	while (p1)
	{
		p->link = new ListNode(p1->data);
		p1 = p1->link;
		p = p->link;
	}
	p->link = NULL;    // βָ�봦��
	ans.rear = p;
	return ans;
}

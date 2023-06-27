#pragma once
#include<iostream>
using namespace std;
/**********************************************************
                        ջ��ʵ��
***********************************************************/
class outOfRange :public exception                        //ջΪ��ȡԪ�ر���
{
public:
	const char* what()const throw()
	{
		return "ERROR! OUT OF RANGE.\n";
	}
};
template<class T>
class stack
{
public:
	stack() {};                                   //���캯��
	virtual bool Push(const T& x) = 0;            //��Ԫ�ؽ�ջ
	virtual T Get_top() = 0;                      //ջ��Ԫ�س�ջ
	virtual T Read_top() const = 0;                //��ȡջ��Ԫ��
	virtual bool Empty()const = 0;                //�ж�ջ�Ƿ�Ϊ��
	//virtual int Get_size()const = 0;            //����ջ�е�Ԫ�ظ���
};
template<class T>
class Linked_stack :public stack<T>
{
public:
	Linked_stack() :top(NULL) {};           //���캯����ջ��ָ���ÿ�
	~Linked_stack() { Make_empty(); };      //��������,��ջ�����ݶ�����
	bool Push(const T& x);                  //��ջ
	T Get_top();                            //��ջ
	T Read_top()const;                      //��ȡջ��Ԫ��
	bool Empty()const;                      //�ж�ջ�Ƿ��
	void Make_empty();                      //��ջ�ÿ�
private:
	struct Link_node                        //������а���һ�������Լ���һ���ĵ�ַ
	{
		T data;
		Link_node* link;
	};
	Link_node* top;                         //ջ��ָ��
};
template<class T>
bool Linked_stack<T>::Push(const T& x)            //��ջ����
{
	Link_node* p;
	p = new Link_node;
	if (p == NULL)                                //����ʧ��
	{
		exit(1);
		cout << "����ʧ��" << endl;
		return false;
	}
	else                                          //�����µĺ�x�Ľ��
	{
		p->data = x;
		p->link = top;
		top = p;
		return true;
	}
}
template<class T>
T Linked_stack<T>::Get_top()                   //��ջ����
{
	T x;
	if (Empty() == true)                       //�ж�ջ�Ƿ�Ϊ��
	{
		throw outOfRange();
	}
	else                                       //ջ��Ϊ��
	{
		Link_node* p = top;                    //p�ݴ�ջ��Ԫ��
		top = top->link;                       //�ı�topָ��
		x = p->data;                           //��p��ջ������ֵ���
		delete p;                              //���ջ��Ԫ��
		return x;
	}
}
template<class T>
T Linked_stack<T>::Read_top()const             //��ȡջ�����������ı�����ֵ
{
	T x;
	if (Empty() == true)                       //�ж�ջ�Ƿ�Ϊ��
	{
		throw outOfRange();
	}
	else                                       //��Ϊ�ն�ȡջ��Ԫ��
	{
		x = top->data;
		return x;
	}
}
template<class T>
bool Linked_stack<T>::Empty()const         //�ж�ջ�Ƿ�Ϊ��
{
	if (top == NULL)                       //�ж�ջ�Ƿ�Ϊ��
	{
		return true;
	}
	else
	{
		return false;
	}
}
template<class T>
void Linked_stack<T>::Make_empty()         //��ջ�ÿ�
{
	Link_node* p;
	while (top != NULL)                    //ͷָ�벻Ϊ��ʱ�������ƣ�ɾ��ջ��Ԫ�� 
	{
		p = top;
		top = top->link;
		delete p;
	}
}
/************************************************************
                        ���Ľڵ���
************************************************************/
class Node
{
	friend class Family_Tree;                         //personΪ����Ԫ��
public:
	Node();                                           //���캯��
private:
	string name;                                      //�ýڵ�����
	Node* child;                                      //�ýڵ�ĺ��ӽ��ָ��
	Node* brother;                                    //�ýڵ��ֵܽ��ָ��
};
Node::Node()                                          //���캯������ֵ
{
	name = '?';
	child = NULL;
	brother = NULL;
}
/**********************************************************
                      ���׳�Ա��
***********************************************************/
class Family_Tree
{
public:
	void Creat(Family_Tree& L);                       //��������
	Node* Lookup(Node* p, string name);               //����ĳ��
	void Add(Family_Tree& L);                         //��Ӳ��ּ�ͥ��Ա
	void Print(Node* p);                              //��ʾ���ּ�ͥ��Ա
	void Insert(Family_Tree& L);                      //��ӵ�����ͥ��Ա
	void Change_name(Family_Tree& L);                 //���׳�Ա����
	void Delete(Family_Tree& L);                      //ɾ����ͥ��Ա
private:
	Node* root;                                       //���׸��ڵ�
};
void Family_Tree::Creat(Family_Tree& L)               //��������ʵ��
{
	cout << "���������ȵ�������";
	string rootname;                                  //�洢��������
	cin >> rootname;
	Node* p = new Node;                               //�����½��p�ݴ�������Ϣ 
	if (p == NULL)                                    //��׳�Ա���
	{
		exit(1);
		cout << "����ʧ��" << endl;
	}
	p->name = rootname;                               
	L.root = p;                                       //p���ֵ�������׵ĸ��ڵ�root
	cout << "�˼��׵������ǣ�" << p->name;
}
Node* Family_Tree::Lookup(Node* p, string name)       //����ĳ��
{
	Node* t = NULL;   
	Linked_stack<Node*>store;
	while (p || store.Empty() != true)                  //��p��Ϊ�գ�����ջ��Ϊ��ʱ��ʼѭ�����������ұ���
	{
		while (p)                                       //���p��Ϊ�գ�������һ�󵽵�
		{
			if (p->name == name)                        //������ͬ�������ҵ���p���ֵ��ֵ��t
			{
				t = p;
			}
			store.Push(p);                              //��pѹ��ջ��
			p = p->child;
		}
		p = store.Get_top();                            //p��ջ
		p = p->brother;
	}
		return t;
}
void Family_Tree::Add(Family_Tree& L)
{
	cout << "������Ҫ������ͥ���˵�������";
	string parent_name;                                       //�����轨����ͥ�ĳ�Ա
	int m=0, n=0;
	cin >> parent_name;
	Node* s = Lookup(L.root, parent_name);                    //�����е����в��Ҹó�Ա
	if (s)
	{
		Node* r = s;
		cout << "������" << s->name << "�Ķ�Ů������";
		cin >> n;
		m = n;
		cout << "����������" << s->name << "�Ķ�Ů������" << endl;
		while (m)                                             //mΪ������һ������
		{
			string child_name;
			Node* q = new Node;
			if (q == NULL)                                    //��׳�Ա���
			{
				exit(1);
				cout << "����ʧ��" << endl;
			}
			cin >> child_name;
			q->name = child_name;                             //��child_name��Ϊ�½�������
			if (m == n)                                       //���Ϊ�����ĵ�һ����Ů������ڸø��ڵ�����
			{
				s->child = q;
				s = s->child;
			}
			else                                              //������ǽ�����һ����Ů����ڵ�һ����Ů���ұ�
			{
				s->brother = q;
				s = s->brother;
			}
			m--;
		}
		Print(r);                                             //��ʾ���ּ�ͥ��Ա
	}
	else
	{
		cout << "���޴��ˣ����������룺" << endl;             //��δ�鵽���ˣ�����������
		Add(L);
	}
}
void Family_Tree::Print(Node* p)
{
	cout << p->name << "�ĵ�һ��������" << p->child->name<<" ";      //��ӡ��һ����Ů��Ա
	p = p->child;
	while (p->brother)                                                 //��ӡ����Ů���ֵܳ�Ա
	{
		cout << p->brother->name << " ";
		p = p->brother;
	}
	cout << '\n';
}
void Family_Tree::Insert(Family_Tree& L)
{
	cout << "������Ҫ��Ӷ��ӻ�Ů�����˵�������";
	string rootname;
	cin >> rootname;
	Node* s = Lookup(L.root, rootname);
	if (s)
	{
		Node* r = s;
		cout << "������" << s->name << "����Ӷ��ӻ�Ů����������";
		Node* p = new Node;                                             //�����½��
		if (p == NULL)                                                  //��׳�Ա���
		{
			exit(1);
			cout << "����ʧ��" << endl;
		}
		string child_name;
		cin >> child_name;
		p->name = child_name;
		if (!s->child)                                                  //������ڵ����Ů���Ϊ��������������ֱ�ӷ��ڸ��ڵ���ҽڵ�
		{
			s->child = p;
		}
		else                                                            //������ڵ����ڵ㲻Ϊ���������ڵ���ֵܽ����
		{
			s = s->child;
			while (s->brother)
			{
				s = s->brother;
			}
			s->brother = p;
		}
		Print(r);
	}
	else
	{
		cout << "���޴��ˣ����������룡" << endl;
		Insert(L);
	}
}
void Family_Tree::Change_name(Family_Tree& L)
{
	cout << "������Ҫ�����������˵�Ŀǰ������";
	string rootname;
	cin >> rootname;
	Node* s = Lookup(L.root, rootname);
	if (s)
	{
		cout << "��������ĺ��������";
		string name;
		cin >> name;
		s->name = name;
		cout << rootname << "�Ѿ�����Ϊ" << s->name << endl;
	}
	else
	{
		cout << "���޴��ˣ����������룡" << endl;
		Change_name(L);
	}
}
void Family_Tree::Delete(Family_Tree& L)
{
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	string rootname;
	cin >> rootname;
	Node* s = Lookup(L.root, rootname);
	if (s)
	{
		if (s->child)                                             //���rootname������Ů����ɢ����
		{
			cout << "Ҫ��ɢ��ͥ�����ǣ�" << s->name << endl;
			Print(s);
			s->child = NULL;
		}
		else                                                      //���û����Ů�ͻ�δ�м�ͥ
		{
			cout << s->name << "��δ�м�ͥ";
		}
	}
	else
	{
		cout << "���޴��ˣ����������룡" << endl;
		Delete(L);
	}
}

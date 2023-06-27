#pragma once
#include<iostream>
using namespace std;
/************************************************************
                       ����������
*************************************************************/
class Node
{
	friend class Linked_list;
	friend class Electric_Frence;
public:
	Node();
private:
	bool flag;                                               //���ʱ�־
	string start_name;                                       //������������
	string present_name;                                     //��ǰ�ӵ�����
	double weight;                                           //�ߵ�Ȩֵ
	Node* next;                                              //��һ�����������ָ��
};
Node::Node()                                                 //��㸳��ֵ
{
	flag = 0;                                                
	present_name='?';
	weight = 0;
	next = NULL;
}
/************************************************************
					   ������·��
*************************************************************/
class Linked_list
{
	friend class Electric_Frence;
public:
	Linked_list()                                             //���캯������ֵ
	{
		start_name = '?';
		next_name = NULL;
		next_link = NULL;
	}
	void Print(Node* N);                                      //���Prim��С������
	static void Insert(Linked_list* p, string name, double path);    //������֮�����ߣ�p---��ʼ���㣬nameĿ�Ľӵ磬����֮���·��Ȩֵ
	static bool Is_side(Linked_list* p, string name);                //����֮���Ƿ���ڱ�
	static int Statistic(Linked_list& L);                            //ͳ��ĳ����ɵ��������������
	string start_name;                                        //����������
	Node* next_name;                                          //�ɵ���Ľӵ��ָ��
	Linked_list* next_link;                                   //��������ָ��
};
void Linked_list::Print(Node* N)
{
	if (N->next)
	{
		Print(N->next);
		cout << N->start_name << "-(" << N->weight << ")->" << N->present_name << " ";
	}
}
void Linked_list::Insert(Linked_list* p, string name, double path)
{
	if (Is_side(p, name))                                     //������֮����ڱ�
	{
		cout << "������֮���Ѿ��бߣ��޷������±�";
	} 
	else                                                      //�������ڱߣ������±�
	{
		Node* N = new Node;
		N->present_name = name;
		N->weight = path;
		N->next = p->next_name;  
		p->next_name = N;
	}
}                                       
bool Linked_list::Is_side(Linked_list* p, string name)
{
	Node* N = p->next_name;                                   
	while (N)
	{
		if (N->present_name == name)                          //�������֮�����ӵ���name��֤������֮���Ѿ��б�
		{
			return true;
		}
		N = N->next;                                          //����������ѰΪname�Ķ���
	}
	delete N;
	return false;
}
int Linked_list::Statistic(Linked_list& L)
{
	int i = 0;
	Node* N = L.next_name;
	while (N)
	{
		N = N->next;
		i++;
	}
	return i;
}

/************************************************************
					     ������
*************************************************************/
class Electric_Frence
{
	friend class Linked_list;
public:
	void Creat_Pinnacle(Electric_Frence&L);                    //��ʼ������
	void Insert_path(Electric_Frence& L);                      //�ڶ���֮������
	bool Is_point(Electric_Frence& L, string name);            //�ж��Ƿ���ڶ���
	void Change_flag(Electric_Frence& L, string name);         //���ķ��ʱ�־
	int Statistic(Electric_Frence& L);                         //ͳ�����еĶ�����
	Node* Min_path(Electric_Frence L,Linked_list&edge,string name);//ͳ����С·��
	void Min_Tree(Electric_Frence L, Linked_list& edge, string name);//Prim��С������
private:
	Linked_list* head;
};
void Electric_Frence::Creat_Pinnacle(Electric_Frence& L)
{
	cout << "�����붥��ĸ�����" << endl;
	int n;
	cin >> n;
	cout << "��������������������" << endl;
	Linked_list* s = new Linked_list;                          //�½�һ��Linked_list���
	for (int i = 1; i <= n; i++)                               //��������n�����������洢����
	{
		Linked_list* p = new Linked_list;
		string name;
		cin >> name;
		p->start_name = name;
		p->next_link = NULL;
		if (i == 1)                                            //����ǵ�һ�����������L��ͷ����
		{
			L.head = p;
			s = L.head;
		}
		else                                                   //������ǵ�һ����������������
		{
			s->next_link = p;
			s = p;
		}
	}
}
void Electric_Frence::Insert_path(Electric_Frence& L)
{
	cout << "���������������Լ���";
	string name1, name2;
	double path;
	cin >> name1 >> name2 >> path;
	if (name1 != "?" && name2 != "?" && path != 0)                                   //�����������������
	{
		if (Is_point(L, name1) && Is_point(L, name2))                                //����������������
		{
			Linked_list* p = L.head;
			while (p)
			{
				if (p->start_name == name1)                                          //������
				{
					Linked_list::Insert(p, name2, path);
				}
				else if (p->start_name == name2)
				{
					Linked_list::Insert(p, name1, path);
				}
				p = p->next_link;
			}
			delete p;
		}
		else
		{
			cout << "����Ķ��㣬���������룺" << endl;
		}
		Insert_path(L);
	}
}
bool Electric_Frence::Is_point(Electric_Frence& L, string name)
{
	Linked_list* p = L.head;                             //������Ķ���ͷ��ʼ����
	while (p)
	{
		if (p->start_name == name)                       //���p�����ҵ���ͬ�Ķ��㣬������ȷ
		{
			return true;
		}
		p = p->next_link;                                //�ö��㲻����ͬ�Ŀ�ʼѰ����һ��
	}
	delete p;                                            //���ȫ�����㶼����ͬ�����ش���
	return false;
}
void Electric_Frence::Change_flag(Electric_Frence& L, string name)
{
	Linked_list* p = L.head;                                   //��������ͼ������name����falgΪ1��weightΪ-1
	while (p)
	{
		Node* N = p->next_name;
		while (N)
		{
			if (N->present_name == name)
			{
				N->flag = 1;
				N->weight = -1;
				break;
			}
			N = N->next;
		}
		p = p->next_link;
	}
}
int Electric_Frence::Statistic(Electric_Frence& L)
{
	int i = 0;
	Linked_list* p = L.head;
	while (p)
	{
		i++;
		p = p->next_link;
	}
	delete p;
	return i;
}
Node* Electric_Frence::Min_path(Electric_Frence L, Linked_list& edge, string name)
{
	Linked_list* p = L.head;
	while (p->start_name != name)
	{
		p = p->next_link;
	}
	Node* N = p->next_name;
	Node* s = N;
	while (N->flag && N->next)
	{
		N = N->next;
	}
	if (N)
	{
		s = N;
		while (N)
		{
			if (s->weight > N->weight && !N->flag)
			{
				s = N;
			}
			N = N->next;
		}
	}
	return s;
}
void Electric_Frence::Min_Tree(Electric_Frence L, Linked_list& edge, string name)
{
	if (Is_point(L, name))                             //�ж�name�Ƿ����
	{
		Linked_list* p = L.head;
		while (p->start_name != name)                         
		{
			p = p->next_link;
		}
		Node* start = new Node;                        //������һһ���½ڵ�
		start->present_name = name;
		start->start_name = name;
		start->weight = 0;
		start->next = edge.next_name;
		edge.next_name = start;
		Change_flag(L, name);
		while (edge.Statistic(edge) < L.Statistic(L))
		{
			Node* t = edge.next_name;
			Node* s = t;
			while(t)
			{
				if ((Min_path(L, edge, s->present_name)->weight > Min_path(L, edge, t->present_name)->weight) && !Min_path(L, edge, t->present_name)->flag)
				{
					s = t;
				}
				t = t->next;
			}
			Node* N = new Node;
			N->start_name = s->present_name;
			N->present_name = Min_path(L, edge, s->present_name)->present_name;
			N->weight = Min_path(L, edge, s->present_name)->weight;
			N->next = edge.next_name;
			edge.next_name = N;
			Change_flag(L, N->present_name);
		}
	}
	else
	{
		cout << "��������룬���������룺" << endl;
		Min_Tree(L, edge, name);
	}
}

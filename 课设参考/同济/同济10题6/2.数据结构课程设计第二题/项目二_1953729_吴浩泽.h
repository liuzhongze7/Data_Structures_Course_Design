#pragma once
#include<iostream>
using namespace std;
class Link_list;
class Link_node                                                  //����ڵ��࣬���а������ݳ�Աdata�Լ�ָ�����Աnext
{
	friend class Link_list;
private:
	int data;
	Link_node* next;
};
class Link_list                                                 //���������࣬��������Ĵ������ȽϺ��������
{
public:
	Link_list();                                                //���캯��
	~Link_list() {};							                //��������
	int Creat_Link_list();                                      //��������
	void Intersection(Link_list s1,Link_list s2);               //�󽻼�����
	void Display_Link_list(Link_node* head);                    //�������
private: 
	int size;                                                   //��¼����Ĵ�С
	Link_node* head;                                            //�����ͷ���
}s1,s2,s3;
Link_list::Link_list()                                          //���캯������
{
	head = new Link_node;                                       //��ʼ��ͷ���
	size = 0;
	head->data = 0;
	head->next = NULL;
}                                 
int Link_list::Creat_Link_list()                                //��������������
{
	Link_node* ptemp;                           //���嵱ǰ���
	ptemp = head;                                               //Ĭ�ϵ�ǰ���Ϊͷ���
	while (1)
	{
		Link_node* pnew = new Link_node;                        //�¶���һ���½ڵ㣬������ֵ
		if (pnew == NULL)
		{
			cout << "�洢�������" << endl;
			exit(1);
		}
		cin >> pnew->data;
		if (pnew->data > 0)                                     //������������Чʱ���䴢����������
		{
			pnew->next = NULL;
			ptemp->next = pnew;
			ptemp = pnew;
			size++;                                             //�������ݼ�һ
		}
		else                                                    //�������������Ч������½��
		{
			delete pnew;                                        
			return 1;
		}
	}
}
void Link_list::Intersection(Link_list s1,Link_list s2)         //��s1�Լ�s2�������н���
{
	if (s1.size == 0 || s2.size == 0)                           //���s1��s2�������п������NULL
	{
		cout << "NULL" << endl;
	}
	else                                                        //�����о���Ϊ��ʱ���ɽ���s3
	{
		Link_node* ptemp1 ;                                     //��������s1���½��ptemp1
		Link_node* ptemp2 ;                                     //��������s2���½��ptemp2
		Link_node* ptemp3 ;                                     //s3�ĵ�ǰ���
		ptemp1 = s1.head->next;
		ptemp2 = s2.head->next;
		ptemp3 = s3.head;
		while (s1.size!=0 && s2.size != 0)                      //��s1��s2�����ݻ�δ��ʱ����
		{
			if (ptemp1->data == ptemp2->data)                   //�������������ӽ�s3�У����ҽ�ptemp2����ƶ�һ��
			{
				s3.size++;
				Link_node* pnew = new Link_node;
				if (pnew == NULL)
				{
					cout << "�洢�������" << endl;
					exit(1);
				}
				pnew->data = ptemp1->data;
				pnew->next = ptemp3->next;
				ptemp3->next = pnew;
				ptemp3 = pnew;
				ptemp2 = ptemp2->next;
				s2.size--;
			}
			else
			{
				if (ptemp1->data < ptemp2->data)                //���s1�е�ǰ����С���ƶ�ptemp1
				{
					ptemp1 = ptemp1->next;
					s1.size--;
				}
				else
				{
					ptemp2 = ptemp2->next;                      //���s2�е�ǰ����С���ƶ�ptemp2
					s2.size--;
				}
			}
		}
		if (s3.head->next == NULL)                              //���s3�����������NULL
		{
			cout << "NULL";
		}
		else
		{
			Display_Link_list(s3.head);                         //������������������
		}
	}

}
void Link_list::Display_Link_list(Link_node* head)              //������������
{
	Link_node* ptemp;                           
	ptemp=head->next;                                           //��ͷ��ʼ�������
	while (s3.size>0)
	{
		cout << ptemp->data<<" ";
		ptemp = ptemp->next;
		s3.size--;
	}
}

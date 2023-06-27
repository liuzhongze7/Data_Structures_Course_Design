#pragma once
#include<iostream>
#include<string>
using namespace std;
class List;
class Link_node                            //��������࣬�����ڵ��е��������Լ�ָ����
{
	friend class List;                     //��List��Ϊ��Ԫ��
private:
	int tnumber;
	string name;
	string gender;
	int age;
    string post;
	Link_node* next;
};
class List                                 //���������࣬���е��������ɾ���Ȳ���
{
public:
	List();   
	~List() {};
    int CreateLink_list(int n);            //��������Ŀ�����Ϣ
	void Print(Link_node*head);            //��ӡ������Ϣ    
	int Research(int a);                   //�ڱ�������������Ϣ
	int Insert();                          //�ڱ��в��뿼����Ϣ
	int Remove(int a);                     //�ڱ���ɾ��������Ϣ
	int Modify(int a);                     //�ڱ����޸����п�����Ϣ
private:
	Link_node* head;
	int size;
};
List::List()                               //��ʼ��ͷָ�룬Ϊ����һ����ͷ���������̵�
{
	head = new Link_node;
	head->tnumber = NULL;
	head->name =' ';
	head->gender = ' ';
	head->age = NULL;
	head->post = ' ';
	head->next = NULL;
}
int List::CreateLink_list(int n)           //������ʼ������Ϣ
{
	if (n <= 0)                            //���������Ч�ڵ���������0���򴴽�ʧ��
	{
		cout << "error";
		return 0;
	}
	else                                   //����ѧ����Ϣ������
	{
		cout <<"�밴�տ��������������뿼���Ŀ��ţ��������Ա����䣬�Լ��������:" << endl;
		size = n;                          //ѧ������
		Link_node* pnew;                   //���������ڵ�һ��Ϊ��ǰ�ڵ�һ��Ϊ�½����
		Link_node* ptemp;                  
		ptemp = head;                      //��ʼʱ��ǰ�ڵ���ͷ����λ��
		for(int i = 1; i <= n;i++ )
		{
			pnew = new Link_node;          //�����½ڵ�
			if (pnew == NULL)
			{
				cout << "�洢�������" << endl;
				exit(1);
			}
			                               //Ϊ�½�㸳ֵ
			cin >> pnew->tnumber >> pnew->name >> pnew->gender >> pnew->age >> pnew->post;
			pnew->next = NULL;             //Ĭ���½��Ϊ���һ���ڵ�
			ptemp->next = pnew;            //���½����������
			ptemp = pnew;                  //����ǰ�ڵ��Ϊ�´����Ľ��
		}
		pnew = new Link_node;              //���²���Ϊ������������һ������β��㣬������������ɾ������
		if (pnew == NULL)
		{
			cout << "�洢�������" << endl;
			exit(1);
		}
		pnew->tnumber = NULL;
		pnew->name = ' ';
		pnew->gender = ' ';
		pnew->age = NULL;
		pnew->post = ' ';
		pnew->next = NULL;
		ptemp->next = pnew;
		ptemp = pnew;
		Print(head);
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�0Ϊȡ��������" << endl;
		return 1;
	}

}
void List::Print(Link_node*head)           //������ӡ��������ӡ������Ϣ
{
	int N=size;                            
	Link_node* ptemp;                      //���嵱ǰ�ڵ�
	ptemp = head->next;                    //����ͷ��㣬����ѧ����Ϣ�ĵط���ʼ��ӡ
	cout << '\n' << endl;
	while (ptemp->next!= NULL && N >0)     //����������д�ӡ��ֻ��ӡ��Ч���ݣ�
	{
		cout << ptemp->tnumber << "   " << ptemp->name << "    " << ptemp->gender << "       " << ptemp->age << "        " << ptemp->post << endl;
		ptemp = ptemp->next;
		N--;
	}
	cout << "��������Ϊ��" << size<<endl;
}
int List::Insert()
{
	int N = size;
	Link_node* ptemp1 = head;                     //���������½��һ��ָ��ͷ��㣬һ��ָ����Ч������Ԫ����������
	Link_node* ptemp2 = head->next;
	Link_node* pnew = new Link_node;              //�����½��洢Ҫ�����ֵ
	if (pnew == NULL)
	{
		cout << "�洢�������" << endl;
		exit(1);
	}
	cin >> pnew->tnumber >> pnew->name >> pnew->gender >> pnew->age >> pnew->post;
	if (pnew->tnumber <=0)                    //�ж�����ѧ�Ų���Ϊ��
	{
		cout << "���Ų���Ϊ�˵�Ԫ" << endl;
		cout << "������������Ҫ���뿼���Ŀ��ţ��������Ա������Լ���������" << endl;
		Insert();
		return 0;
	}
	else                                          //ѧ�Ų�Ϊ�ս���Ѱ��λ�ò������
	{
		while (N > 0)
		{
			if (pnew->tnumber == ptemp2->tnumber) //�������������ͬ��������
			{
				cout << "���Ų����ظ�" << endl;
				cout << "������������Ҫ���뿼���Ŀ��ţ��������Ա������Լ���������" << endl;
				Insert();
				return 0;
			}
			if (pnew->tnumber < ptemp2->tnumber)  //����ҵ���λ�ñ�Ҫ����Ŀ��Ŵ�����в������
			{
				pnew->next = ptemp2;
				ptemp1->next = pnew;
				size++;
				Print(head);
				return 1;                         //�������
			}
			else
			{
				N--;
				if (N == 0)                           //���¼����߿������嵽���
				{
					pnew->next = ptemp2->next;
					ptemp2->next = pnew;
					size++;
					Print(head);
					return 0;
				}
				ptemp1 = ptemp2;                      //����ǰλ�ò�����Ҫ���������ƶ�
				ptemp2 = ptemp2->next;
			}
			
		}
		return 0;
	}
}
int List::Remove(int a)                                   //ɾ��ѧ�����ݺ���
{
	int N = size;
	Link_node* ptemp1 = head;                             //���嵱ǰλ�ú͵�ǰλ�õ�ǰһ��λ��
	Link_node* ptemp2 = head->next;
	while (N > 0)                                         //���鵥����Ѱ��ѧ�������ͬѧ
	{
		if (ptemp2->tnumber == a)                         //���ҵ�����ϵĽ��в���
		{
			size--;
			cout << "��ɾ���Ŀ�����ϢΪ��" << endl;       //���ɾ����Ϣ
			cout << ptemp2->tnumber << "   " << ptemp2->name << "    " << ptemp2->gender << "       " << ptemp2->age << "        " << ptemp2->post << endl;
			ptemp1->next = ptemp2->next;                  //����ɾ������
			delete ptemp2;
			Print(head);                                  //��ӡɾ�����ѧ����Ϣ
			return 1;
		}
		else                                              //�����ǰ�ڵ㲻������ϵ�
		{
			ptemp1 = ptemp2;                              //�����ƶ�Ѱ�ҷ��ϵĽ��
			ptemp2 = ptemp2->next;
			N--;
		}
	}
	cout << "���޴�ѧ��" << endl;                           //����޴�ѧ����������ԭѧ������
	Print(head);
	return 0;
}
int List::Research(int a)
{
	int N=size;
	Link_node* ptemp = head->next;               //�ӵ�һ����Ч����λ�ÿ�ʼ�������迼��
	while (N > 0)
	{
	if (ptemp->tnumber == a)                     //���������ֱ�ӽ��������ӡ
	{
		cout << ptemp->tnumber << "   " << ptemp->name << "    " << ptemp->gender << "       " << ptemp->age << "        " << ptemp->post << endl;
		return 1;
	}
	ptemp=ptemp->next;                           //��δ�ҵ��Ƶ���һλ�ü�������
	N--;
	}
	cout << "δ�ҵ���ѧ��" << endl;
	return 0;
}
int List::Modify(int a) 
{
	int N = size;
	Link_node* ptemp = head->next;                     //�ӵ�һ����Ч����λ�ÿ�ʼ�������迼��
	while (N > 0)
	{
		if (ptemp->tnumber == a)                       //���������ֱ�ӽ��������ӡ
		{
			cout << "�������޸��Ժ�Ŀ�����Ϣ��" << endl;
			cin >> ptemp->tnumber >> ptemp->name >> ptemp->gender >> ptemp->age >> ptemp->post;
			Print(head);
			return 1;
		}
		ptemp = ptemp->next;                           //��δ�ҵ��Ƶ���һλ�ü�������
		N--;
	}
	cout << "δ�ҵ���ѧ��" << endl;
	return 0;
}

/* 
2 stu1 �� 18 �������ʦ
3 stu2 �� 19 ����ܹ�ʦ
4 stu3 Ů 21 �����ܾ���

0 stu4 Ů 20 �������ʦ
1 stu5 �� 25 ����ܹ�ʦ
*/

#include"��Ŀһ_1953729_�����.h"
using namespace std;
int main()
{
	int n, number, choice = 0;
	List member;
	cout << "�����뽨������ϵͳ��" << endl;
	cout << "�����뿼��������" << endl;
	cin >> n;
	member.CreateLink_list(n);                                  //��������ϵͳ
	while (1)
	{
		cout << '\n' << "��������Ҫ���еĲ���:";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "������������Ҫ���뿼���Ŀ��ţ��������Ա������Լ���������" << endl;
			member.Insert();
			break;
		}
		case 2:
		{
			cout << "��������Ҫɾ���Ŀ������ţ�";
			cin >> number;
			if (number <= 0)                               //����ѧ�Ų���Ϊ�յ����
			{
				cout << "���Ų���Ϊ�˵�Ԫ" << endl;
			}
			else
			{
				member.Remove(number);                        //���ú�������ɾ��
			}
			break;
		}
		case 3:
		{
			cout << "������Ҫ���ҿ����Ŀ��ţ�";
			cin >> number;
			if (number<=0)                               //����ѧ�Ų���Ϊ�յ����
			{
				cout << "���Ų���Ϊ�˵�Ԫ" << endl;
			}
			else
			{
				member.Research(number);                      //���ú�����������
			}
			break;
		}
		case 4:
		{
			cout << "������Ҫ�޸Ŀ����Ŀ��ţ�";
			cin >> number;
			if (number <=0)                               //����ѧ�Ų���Ϊ�յ����
			{
				cout << "���Ų���Ϊ�˵�Ԫ" << endl;
			}
			else
			{
				member.Modify(number);                      //���ú�����������
			}
			break;
		}
		case 0:
		{
			cout << "�����������������������" << endl;
			return 0;
		}
		default:
			cout << "�޴˲��������������룺" << endl;
		}
	}
}
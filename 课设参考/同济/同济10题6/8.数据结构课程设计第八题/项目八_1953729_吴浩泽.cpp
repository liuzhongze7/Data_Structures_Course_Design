#include"��Ŀ��_1953729_�����.h"
using namespace std;
int main()
{
	cout << endl;
	cout << "**                      �������ģ��ϵͳ                    **" << endl;
	cout << "==============================================================" << endl;
	cout << "**                   ��ѡ��Ҫִ�еĲ���:                    **" << endl;
	cout << "**                      A---������������                    **" << endl;
	cout << "**                      B---��ӵ����ı�                    **" << endl;
	cout << "**                      C---������С������                  **" << endl;
	cout << "**                      D---��ʾ��С������                  **" << endl;
	cout << "**                      E---�˳�����                        **" << endl;
	cout << "==============================================================" << endl;
	Electric_Frence L;
	Linked_list edge;
	char ch = ' ';
	while (ch != 'E')
	{
		cout << '\n' << "��ѡ�������";
		cin >> ch;
		switch (ch)
		{
		case'A':
		{
			L.Creat_Pinnacle(L);
			break;
		}
		case'B':
		{
			L.Insert_path(L);
			break;
		}
		case'C':
		{
			cout << "��������ʼ���㣺";
			string name;
			cin >> name;
			L.Min_Tree(L, edge, name);
			cout << "����Prim��С��������\n";
			break;
		}
		case'D':
		{
			cout << "��С�������Ķ��㼰��Ϊ��" << endl;
			cout << endl;
			edge.Print(edge.next_name);
			cout << endl;
			break;
		}
		case'E':break;
		default:
		{
			cout << "���������������ȷ�Ĳ�����" << endl;
			break; 
	 	}
		}
	}
	system("pause");
	return 0;
}
#include"��Ŀ��_1953729_�����.h"
using namespace std;
int main()
{
	cout << endl;
	cout << "**                      ���׹���ϵͳ                        **" << endl;
	cout << "==============================================================" << endl;
	cout << "**                   ��ѡ��Ҫִ�еĲ���:                    **" << endl;
	cout << "**                      A---���Ƽ���                        **" << endl;
	cout << "**                      B---��Ӽ�ͥ��Ա                    **" << endl;
	cout << "**                      C---��ɢ�ֲ���ͥ                    **" << endl;
	cout << "**                      D---���ļ�ͥ��Ա����                **" << endl;
	cout << "**                      E---�˳�����                        **" << endl;
	cout << "==============================================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
	Family_Tree L;
	L.Creat(L);                                       //��������
	char ch=NULL;
	while (ch != 'E')
	{
		cout << '\n' << "��ѡ��Ҫִ�еĲ�����";
		cin >> ch;
		switch (ch)
		{
		case'A':
		{
			L.Add(L);
			break;
		}
		case'B':
		{
			L.Insert(L);
			break;
		}
		case'C':
		{
			L.Delete(L);
			break;
		}
		case'D':
		{
			L.Change_name(L);
			break;
		}
		case'E':
		{
			break;
		}
		default:
			cout << "��������ȷ�Ĳ�����" << endl;
		}
	}
	return 0;
}
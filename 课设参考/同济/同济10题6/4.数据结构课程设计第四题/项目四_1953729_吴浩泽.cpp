#include"��Ŀ��_1953729_�����.h"
using namespace std;
int main()
{
	int number;
	char choice='y';
	char eatendl;
	calculator s;
	while (choice == 'y')
	{
		cout << "�Ƿ�ʼ����(y,n)?";
		choice=getchar();                                 //��ȡy/n
		eatendl = getchar();                              //��ȡy��Ļس�
		if (choice == 'y')
		{
			cout << "��������ʽ" << endl;
			number = s.calculator_number();
			cout << "���ս��Ϊ��" << number << endl;
		}
		else
		{
			return 0;

		}
	}
}
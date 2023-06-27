#pragma once
#include<iostream>
using namespace std; 
struct offsets
{
	int a, b;
	char dir;
}direction[4] = {{0,1,'E'},{0,-1,'W'},{1,0,'S'},{-1,0,'N'}};  //ǰ�������
class maze                                                    //�Թ��࣬�����Թ��Ľ�����Ѱ��·������ӡ
{
public:
	maze();
	void Creat_maze();
	int Find_road(int x,int y);
	void Print_maze();
private:
	char** a;                                                 //a��b��һ����άchar������
	char** b;
	int row;
	int	col;                                                  //�Թ������Լ�����
	int road_number;                                          //·����
};
maze::maze()                                                  //���캯������ֵ
{
	a = NULL;
	b = NULL;
	row = 0;
	col = 0;
	road_number = 0;
}
void maze::Creat_maze()
{
	cout << "��������������������" << endl;
	cin >> row >> col;                                //����������������
	a = new char* [row];                              //��̬������ά����
	b = new char* [row];
	if (a == NULL||b==NULL)                           //����ڴ�
	{
		cout << "�ڴ�������" << endl;
		exit(1);
	}
	for (int i = 0; i < row; i++)
	{
		a[i] = new char[col];
		b[i] = new char[col];
		if (a[i] == NULL||b[i]==NULL)                 //����ڴ�
		{
			cout << "�ڴ�������" << endl;
			exit(1);
		}
	}
	cout << "�����������Թ�����0��ʾ�յأ�#��ʾΧǽ��" << endl;
	cout << "����֤��ֹ�㣨��Χǽ������Ͻ������½ǣ��ǿյ�" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < row; i++)                                //�����Թ����Ϸ����ж�
	{
		for (int j = 0; j < col; j++)
		{
			if (a[i][j] != '0' && a[i][j] != '#')
			{
				cout << "�Թ��ڲ��в���ʶ���ַ������������룺";
				Creat_maze();
			}
			if (i == 1&& j == 1)
			{
				if (a[i][j] != '0')
				{
					cout << "�Թ���ʼ���겻�Ϸ������������룺";
					Creat_maze();
				}
			}
			if (i == row-2 && j == col-2)
			{
				if (a[i][j] != '0')
				{
					cout << "�Թ���ʼ���겻�Ϸ������������룺";
					Creat_maze();
				}
			}
			if (i == 0||j == 0)
			{
				if (a[i][j] != '#')
				{
					cout<< "�Թ�Χǽ���Ϸ������������룺";
					Creat_maze();
				}
			}
			if (i == row-1 || j == col-1)
			{
				if (a[i][j] != '#')
				{
					cout << "�Թ�Χǽ���Ϸ������������룺";
					Creat_maze();
				}
			}
		}
	}
	cout << "���Թ�����ʱΪ��" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}
int maze::Find_road(int x, int y)
{
	int g, h;
	char d;
	a[x][y] = '1';                                //����ǰλ��1
	if ((x == row - 2) &&( y == col - 2))         //�ݹ��ֹ����
	{		
		return 1;
	}
	for (int i = 0; i < 4; i++)                   //���ĸ����������̽�����Ƿ�����
	{
		g = x + direction[i].a;
		h = y + direction[i].b;
		d = direction[i].dir;
		if (a[g][h] == '0')
		{
			if (Find_road(g, h))
			{
				road_number++;                   //�ҵ�����ʱ����
				b[g][h] = road_number;           //��������߳��Թ�·��
				return 1;
			}
		}
	}
	a[x][y] = '0';                               //���û�ҵ�·�����������
	return 0;
}
void maze::Print_maze()                             //��ӡ�����Ժ���Թ�
{
	if (a[1][1] == '0')
	{
		cout << "���Թ��޿ɳ�·��" << endl;
	}
	else
	{
		cout << "�Թ�·�����£�" << endl;           //������Թ���1��ʾ·��
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
		cout << "(1,1)->";
		for (int k = road_number; k > 0; k--)      //�������·������
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (b[i][j] == k)
					{
						cout << "(" << i << "," << j << ")->";
					}
				}
			}
		}
	}
}
/*
10 10
##########
#0##0#000#
#00000#0##
#####0####
#00000000#
##0#0#0#0#
#00#00#00#
#0###0#0##
#00#0#000#
##########
5 5
#####
#000#
#000#
#000#
#####
4 4
####
#0##
#00#
####

*/

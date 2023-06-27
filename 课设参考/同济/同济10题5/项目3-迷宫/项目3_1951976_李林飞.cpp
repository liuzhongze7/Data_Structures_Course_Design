/*
* FileName:   Maze.cpp
* Author:     ���ַ�
* StuNumber:  1951976
* Date:       2020.12.06
*/

#include<iostream>
using namespace std;

/*====================================== ջ��ģ���� ==============================================*/
// �����
template <class Type>
struct Node
{
	Type data;
	Node<Type> * link = NULL;
	Node<Type>(Type x) : data(x) {}
	Node<Type>(Type x, Node<Type>* next = NULL) : data(x), link(next){}
};

// ջ��
template <class Type>
class Stack
{
private:
	Node<Type> * top;                 // ջ��ָ��

public:
	Stack():top(NULL) {};             //  ���캯��
	~Stack();                         // ��������
	void Push(const Type & x);        // ��ջ
	Type Pop();                       // ��ջ
	Type Top() const;                 // ����ջ��Ԫ��
	bool Empty() const { return top == NULL ? true : false; }  // �п�
	int Size() const;                 // ����ջ��Ԫ�ظ���
};

// �������� ���� ����ջ
template<class Type>
Stack<Type>::~Stack()
{
	Node<Type>* q;
	while (top)
	{
		q = top;
		top = top->link;
		delete q;
	}
}

// ��ջ
template<class Type>
void Stack<Type>::Push(const Type& x)
{
	top = new Node<Type>(x, top);
	if (top == NULL) {
		cout << "�ռ����ʧ��!"; exit(1);
	}
}

// ��ջ
template<class Type>
Type Stack<Type>::Pop()
{
	Type x;
	Node<Type>* q = top;
	top = top->link;
	x = q->data;
	delete q;
	return x;
}

// ȡջ��Ԫ��
template<class Type>
Type Stack<Type>::Top() const
{
	return top->data;
}

// ����ջ�Ĵ�С
template<class Type>
int Stack<Type>::Size() const
{
	Node<Type>* p = top;
	int length = 0;
	while(p)
	{
		length++;
		p = p->link;
	}
	return length;
}


/*============================== ������ =========================================*/
struct Point
{
	int row = -1;  // Ĭ��Ϊ-1
	int col = -1;  // Ĭ��Ϊ-1

	Point(const Point & P)
	{
		row = P.row;
		col = P.col;
	}
	Point(int x = -1, int y = -1)
	{
		row = x;
		col = y;
	}
};

ostream& operator<<(ostream& os, Point& p)
{
	os << "(" << p.row << "," << p.col << ")";
	return os;
}

/*================================== �Թ��� ======================================*/
class Maze
{
private:
	int Row;                             // �Թ�����
	int Col;                             // �Թ�����
	int ** maze = NULL;                  // �Թ�����
	Point startP;                        // �Թ���ʼ����
	Point endP;                          // ��ֹ����
	bool ** mark = NULL;                 // ���ʱ�����飺δ������Ϊ0�����ʹ���Ϊ1  
	Point VisitAroundNode(Point point);   //��ȡ����δ�����ʵĽڵ�
	Stack<Point> pointStack;              // �洢·��

public:
	Maze(int row, int col);               // ���캯��
	~Maze();                              // ��������
	void SetStartP(Point p) { startP.row = p.row; startP.col = p.col; } // �����Թ����
	void SetEndP(Point p) { endP.row = p.row; endP.col = p.col; }       // �����Թ�����
	void InitMaze(void* array);           // ��ʼ��·��
    void FindPath();                      // ·������
	void PrintPath();                     // ���·��
};

// ���캯�� ���� ��̬��������ռ�
Maze::Maze(int row, int col)
{
	Row = row;
	Col = col;

	// ��̬�����Թ�����
	maze = new int* [Row];   
	for (int i = 0; i < Row; i++)
		maze[i] = new int[Col];

	// ��̬����������ռ�
	mark = new bool* [Row];
	for (int i = 0; i < Row; i++)
		mark[i] = new bool[Col];
}

// �������� ���� �ͷſռ�
Maze::~Maze()
{
	for (int i = 0; i < Row; i++)
		delete maze[i];
	delete[] maze;

	for (int i = 0; i < Row; i++)
		delete mark[i];
	delete[] mark;
}

// ��ʼ���Թ�����
void Maze::InitMaze(void* array)
{
	//�����������������Ķ�ά���黹ԭΪָ�����飬��֧���±����
	int** maze2d = new int* [Row];
	for (int i = 0; i < Row; ++i)
	{
		maze2d[i] = (int*)array + i * Col;
	}

	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			maze[i][j] = maze2d[i][j];     // ��ʼ���Թ�����
			mark[i][j] = maze2d[i][j];     // ��ʼ��������飬ǽ��1Ĭ��Ϊ�Ѿ����ʣ�ͨ·0Ĭ��δ������
		}
	}
}

// ���ʵ�ǰ�������ܽ��
Point Maze::VisitAroundNode(Point point)
{
	Point resP(-1,-1);
	if (point.row - 1 >= 0 && mark[point.row - 1][point.col] == false) {//�Ͻڵ���������
		resP.row = point.row - 1;
		resP.col = point.col;
		return resP;
	}
	if (point.col + 1 < Col && mark[point.row][point.col + 1] == false) {//�ҽڵ���������
		resP.row = point.row;
		resP.col = point.col + 1;
		return resP;
	}
	if (point.row + 1 < Row && mark[point.row + 1][point.col] == false) {//�½ڵ���������
		resP.row = point.row + 1;
		resP.col = point.col;
		return resP;
	}
	if (point.col - 1 >= 0 && mark[point.row][point.col - 1] == false) {//��ڵ���������
		resP.row = point.row;
		resP.col = point.col - 1;
		return resP;
	}
	return resP;
}


// ·������ ���� DFS�㷨
void Maze::FindPath()
{

	//�����յ����Ϊ���ϰ���㣬�����������
	if (maze[startP.row][startP.col] == 1 || maze[endP.row][endP.col] == 1)
	{
		cout << "�Թ���ʼ����յ��������\n";
		return;
	}

	//�������ջ�������Ϊ����
	pointStack.Push(startP);
	mark[startP.row][startP.col] = true;

	//ջ���ղ���ջ��Ԫ�ز�Ϊ�����ڵ�
	while (pointStack.Empty() == false && (pointStack.Top().row != endP.row || pointStack.Top().col != endP.col))
	{
		Point NotVisitNode = VisitAroundNode(pointStack.Top());
		if (NotVisitNode.row == -1) 
		{     //û��δ�����ʵ����ڽڵ�
			pointStack.Pop();             //���ݵ���һ���ڵ�
			continue;
		}

		//��ջ�����÷��ʱ�־Ϊtrue
		pointStack.Push(NotVisitNode);
		mark[NotVisitNode.row][NotVisitNode.col] = true;
	}
}

// ��ӡ·��
void Maze::PrintPath()
{
	if (pointStack.Empty() == true)
	{
		cout << "����Ч·����\n" << endl;
	}
	else
	{
		Stack<Point> tmpStack;
		cout << "\n�Թ�·��:\n";
		while (pointStack.Empty() == false)
		{
			tmpStack.Push(pointStack.Top());
			pointStack.Pop();
		}

		// �����ʽ���� 
		if (tmpStack.Empty() == false) {
			cout << "(" << tmpStack.Top().row << "," << tmpStack.Top().col << ")";
			tmpStack.Pop();
		}
		while (tmpStack.Empty() == false)
		{
			cout  << " --> " << "(" << tmpStack.Top().row << "," << tmpStack.Top().col << ")";
			tmpStack.Pop();
		} 
	}
	cout << endl  << endl << endl;
}

/*=================================== ������ =====================================================*/
int main()
{
	int Row, Col; // ������
	Point startP; // ���
	Point endP;   // �յ�


	/* === С���Թ� === */
	// �Թ���ͼ���
	int smallmaze[5][5] = {
			{0,0,0,0,0},
			{0,1,0,1,0},
			{0,1,1,0,0},
			{0,1,1,0,1},
			{0,0,0,0,0}
	};
	cout << "С�Թ���ͼ��\n";
	for (int i = 0; i < 5; i++)
		cout << "   " << i << "��";
	cout << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << i << "��" << " ";
		for (int j = 0; j < 5; j++)
		{
			cout << smallmaze[i][j] << "     ";
			if (j == 4) cout << endl << endl;
		}
	}

	
	cout << "����Թ����������������� ";
	cin >> Row >> Col;
	while(Row != 5 || Col != 5)
	{
		cout << "����������������������룺";
		cin >> Row >> Col;
	}

	cout << "���������(���к���)�� ";
	cin >> startP.row >> startP.col;
	cout << "�������յ�(���к���)�� ";
	cin >> endP.row >> endP.col;

	// ��ʼ���Թ�
	Maze map1(Row, Col);       // �Թ�����
	map1.InitMaze(smallmaze);   // ��ʼ���Թ�����
	map1.SetStartP(startP);  // �����Թ����
	map1.SetEndP(endP);    // �����Թ�����
	map1.FindPath();       // ·������
	map1.PrintPath();      // ��ӡ·��




	/* ==== �����Թ� ==== */
	// �Թ���ͼ���
	int bigmaze[10][10] = {
			{0,0,0,0,0,1,0,0,0,0},
			{1,1,0,1,0,0,0,1,0,0},
			{0,1,0,0,0,1,1,0,1,0},
			{0,1,1,1,1,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,0,1},
			{0,0,0,0,0,1,0,0,0,0},
			{1,1,0,1,0,0,0,1,1,1},
			{0,0,0,0,0,1,1,0,1,0},
			{0,0,1,1,1,0,0,0,1,0},
			{1,0,0,0,0,0,1,0,0,0},
	};
	cout << "���Թ���ͼ��\n";
	for (int i = 0; i < 10; i++)
		cout << "   " << i << "��";
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << "��" << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << bigmaze[i][j] << "     ";
			if (j == 9) cout << endl << endl;
		}
	}


	cout << "����Թ����������������� ";
	cin >> Row >> Col;
	while (Row != 10 || Col != 10)
	{
		cout << "����������������������룺";
		cin >> Row >> Col;
	}

	cout << "���������(���к���)�� ";
	cin >> startP.row >> startP.col;
	cout << "�������յ�(���к���)�� ";
	cin >> endP.row >> endP.col;

	// ��ʼ���Թ�
	Maze map2(Row, Col);       // �Թ�����
	map2.InitMaze(bigmaze);   // ��ʼ���Թ�����
	map2.SetStartP(startP);  // �����Թ����
	map2.SetEndP(endP);    // �����Թ�����
	map2.FindPath();       // ·������
	map2.PrintPath();      // ��ӡ·��
	

	/* === ��ڳ������������� ===*/
	// �Թ���ͼ���
	int maze[10][10] = {
			{1,0,0,0,0,1,0,0,0,0},
			{1,1,0,1,0,0,0,1,0,0},
			{0,1,0,0,0,1,1,0,1,0},
			{0,1,1,1,1,0,1,0,0,0},
			{0,0,0,0,0,1,1,1,0,1},
			{0,0,0,0,0,1,0,0,0,0},
			{1,1,0,1,0,0,0,1,1,1},
			{0,0,0,0,0,1,1,0,1,0},
			{0,0,1,1,1,0,0,0,1,0},
			{1,0,0,0,0,0,1,0,0,0},
	};
	cout << "��ڳ������������ԣ�\n";
	cout << "���Թ���ͼ��\n";
	for (int i = 0; i < 10; i++)
		cout << "   " << i << "��";
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << "��" << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << maze[i][j] << "     ";
			if (j == 9) cout << endl << endl;
		}
	}


	cout << "����Թ����������������� ";
	cin >> Row >> Col;
	while (Row != 10 || Col != 10)
	{
		cout << "����������������������룺";
		cin >> Row >> Col;
	}

	cout << "���������(���к���)�� ";
	cin >> startP.row >> startP.col;
	cout << "�������յ�(���к���)�� ";
	cin >> endP.row >> endP.col;
	// ��ʼ���Թ�
	Maze map3(Row, Col);       // �Թ�����
	map3.InitMaze(maze);   // ��ʼ���Թ�����
	map3.SetStartP(startP);  // �����Թ����
	map3.SetEndP(endP);    // �����Թ�����
	map3.FindPath();       // ·������
	map3.PrintPath();      // ��ӡ·��


	/* === ����Ч·������ ==== */
	// �Թ���ͼ���
	int errormaze[10][10] = {
			{0,0,0,0,0,1,0,0,0,0},
			{1,1,0,1,0,0,0,1,0,0},
			{0,1,1,0,0,1,1,0,1,0},
			{0,1,1,1,1,0,1,0,0,0},
			{0,0,0,0,1,1,1,1,0,1},
			{0,0,0,0,0,1,0,0,0,0},
			{1,1,0,1,1,0,1,1,1,1},
			{0,0,0,0,0,1,1,1,1,0},
			{0,0,1,1,1,0,0,0,1,0},
			{1,0,0,0,0,0,1,0,0,0},
	};
	cout << " ����Ч·�����ԣ�\n";
	cout << "��·���Թ���ͼ��\n";
	for (int i = 0; i < 10; i++)
		cout << "   " << i << "��";
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i << "��" << " ";
		for (int j = 0; j < 10; j++)
		{
			cout << errormaze[i][j] << "     ";
			if (j == 9) cout << endl << endl;
		}
	}


	cout << "����Թ����������������� ";
	cin >> Row >> Col;
	while (Row != 10 || Col != 10)
	{
		cout << "����������������������룺";
		cin >> Row >> Col;
	}

	cout << "���������(���к���)�� ";
	cin >> startP.row >> startP.col;
	cout << "�������յ�(���к���)�� ";
	cin >> endP.row >> endP.col;

	// ��ʼ���Թ�
	Maze map4(Row, Col);        // �Թ�����
	map4.InitMaze(errormaze);   // ��ʼ���Թ�����
	map4.SetStartP(startP);    // �����Թ����
	map4.SetEndP(endP);        // �����Թ�����
	map4.FindPath();           // ·������
	map4.PrintPath();          // ��ӡ·��

	system("pause"); // Ϊ�����ɵ�.exe�ļ��鿴���
	return 0;

}

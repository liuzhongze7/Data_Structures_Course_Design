/*11����2���Թ����⣨ѡ������ջ����У�����������������������
[��������]
����ջ����ʵ���Թ�������⡣
[����Ҫ��]
��1�����ļ��ж�ȡ���ݣ�����ģ���Թ���ͼ��������10��10�С�
��2������������ںͳ��ڣ���ʾ����Թ�·�ߡ�
*/
#include"Maze.h" //�������� 
#include"Maze.cpp" //�������� 
#include"Position.h" //��洢 
#include"Stack.h" //�Լ���дһ��ջ 
#include<iostream>
using namespace std;
int main()
{
    Maze maze;
    Stack S;
    Position start;
    Position end;
    start.x = 1;
    start.y = 1;
    end.x = 10;
    end.y = 10;
    InitMaze(maze);
    cout << "ԭ�Թ���" << endl << endl;
    PrintMaze(maze);
    cout  << endl << "********************" << endl;
    cout << "*   ��������㣺   *" << endl;
    cout << "********************" << endl << endl;
    cout << "x:" ;
    cin >> start.x;
    cout << "y:" ;
    cin >> start.y;
    cout  << endl << "********************" << endl;
    cout << "*   �������յ㣺   *" << endl;
    cout << "********************" << endl << endl;
    cout << "x:" ;
    cin >> end.x;
    cout << "y:" ;
    cin >> end.y;
    if(MazePath(maze,start,end,S))
    {
        cout << endl << endl << "�Թ��Ľ⣺(*����·��)" << endl << endl;
        PrintMaze(maze);
    }
    else
    {
        cout << endl << "********************" << endl;
        cout << "*   ���Թ��޽⣡   *" << endl;
        cout << "********************" << endl;
    }
     system("pause");
    return 0;
   
}

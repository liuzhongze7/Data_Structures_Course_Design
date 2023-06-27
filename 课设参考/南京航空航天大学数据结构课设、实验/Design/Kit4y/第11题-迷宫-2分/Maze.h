#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#define RANGE 1002
#include"Position.h"
typedef struct
{
    int m,n;
    int row;
    int col;
    char arr[RANGE][RANGE];
}Maze;

bool InitMaze(Maze &maze,int row,int col);
bool MazePath(Maze &maze,Position start,Position end);//���start������end��һ��·��
void PrintMaze(Maze &maze);


#endif // MAZE_H_INCLUDED

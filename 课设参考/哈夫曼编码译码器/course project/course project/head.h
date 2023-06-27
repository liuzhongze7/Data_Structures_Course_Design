#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include <graphics.h>  // ����ͼ�ο�ͷ�ļ�����ͷ�ļ���������ͼ�λ���������
#include <conio.h>	 // ����ͼ�ο�ͷ�ļ�����ͷ�ļ�����ͼ�λ�������ơ�
#include<math.h>
#include<time.h>

typedef struct node
{
	char info;				//�����ַ�
	int data;				//����Ȩֵ
	char encode[20];		//������������
	node *lchild, *rchild, *next, *parent;
}hufnode;
typedef struct stack
{
	int data[100];
	int top;
}stack_1;

void QuickSort(hufnode y[], int left, int right);//����Ԫ�ؿ�������
hufnode *tolink(hufnode a[], int count);				//������������Ԫ��������������
int readdata(hufnode x[]);							//���ļ���ȡ����
hufnode *insert(hufnode * root, hufnode *s);					//ȡ����С�ڵ㽫�ڵ����
hufnode *creathuff(hufnode * root);								// ���ɹ��������Ĵ�������

void treeencode(hufnode *t, hufnode *h, int count);			//����������
void decode(hufnode tree[]);						//����

void init(stack *s);				//ջ��ʼ��	
void push(stack *s, int  a);		//ѹջ
int pop(stack *s);					//��ջ
void draw(int x, int y, char c);			//�����
void drawdemo(hufnode *s, int x, int y, int temp, int suojian);  //����
void draw_main(hufnode *s);				 //ͼ�λ�����������
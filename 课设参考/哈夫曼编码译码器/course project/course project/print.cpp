/*
---------------------------------------------------------------------------------
���ļ��������б���ͼ�λ��������
---------------------------------------------------------------------------------
*/

#include"head.h"					//������ͷ�ļ�
void  draw_main(hufnode *s)
{
	int a = 1400;
	int b = 0;
	initgraph(1920, 1080);			// ������ͼ���ڣ�SHOWCONSOLE
	setbkcolor(WHITE);			// ���ñ��������ɫ
	cleardevice();						//�������
	setcolor(BLACK);
	drawdemo(s, 860, 20, a, b);				//�ݹ���û��������ļ�
	_getch();						 // ����������ʱ�䡣
	closegraph();					 // �رջ�ͼ����

}


void draw(int x, int y, char c)
{
	circle(x, y, 10); Sleep(100);//��Ȧ����ͣ100ms
	outtextxy(x - 5, y - 7, c);   //���Ԫ��
}

void drawdemo(hufnode *s, int x, int y, int temp, int suojian)  //ǰ������ݹ����ͼ�λ�huffman��
{
	if (s != NULL && s->info != 'J'&&s->info != 'Z') //���������J��Z�ڵ��غ�
		draw(x, y, s->info);
	if (s->lchild != NULL)
	{
		if (s->lchild->info != 'J')
		{
			suojian += 4;//����ֵ����
			line(x - 8, y + 8, x - temp / suojian, y + 50 - 10); outtextxy(x - (8 + temp / suojian) / 2, y + 19, '0'); Sleep(10);//���߲���ͣ10ms
			drawdemo(s->lchild, x - temp / suojian, y + 50, temp, suojian);//�ݹ����������
		}
		else
		{
			line(x - 8, y + 8, x - 25, y + 50 - 10); outtextxy(x - 25, y + 19, '0'); Sleep(10);
			draw(x - 25, y + 50, s->lchild->info);
		}   //ʹJ��Z�ڵ�ָ���
	}
	suojian -= 4;
	if (s->rchild != NULL)
	{
		if (s->rchild->info != 'Z')
		{
			suojian += 4;//����ֵ����
			line(x + 8, y + 8, x + temp / suojian, y + 50 - 10); outtextxy(x + (8 + temp / suojian) / 2, y + 19, '1'); Sleep(10);//���߲���ͣ10ms
			drawdemo(s->rchild, x + temp / suojian, y + 50, temp, suojian);//�ݹ����������
		}
		else
		{
			line(x + 8, y + 8, x + 25, y + 50 - 10); outtextxy(x + 25, y + 19, '1'); Sleep(10);
			draw(x + 25, y + 50, s->rchild->info);
		}   //ʹJ��Z�ڵ�ָ���
	}
	suojian -= 4;
}

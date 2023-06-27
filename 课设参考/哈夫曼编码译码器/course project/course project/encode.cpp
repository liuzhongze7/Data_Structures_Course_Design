/*
---------------------------------------------------------------------------------
���ļ�Ϊ������й������������ļ�
---------------------------------------------------------------------------------
*/


#include"head.h"
hufnode *insert(hufnode * root, hufnode *s)					//ȡ����С�ڵ㴴����
{
	hufnode *p1, *p2;
	if (root == NULL)
		root = s;
	else
	{
		p1 = NULL;
		p2 = root;
		while (p2&&p2->data < s->data)
		{
			p1 = p2;
			p2 = p2->next;
		}
		s->next = p2;
		if (p1 == NULL)
			root = s;
		else
			p1->next = s;
	}
	return root;
}
hufnode *creathuff(hufnode * root)								// ���ɹ��������Ĵ�������
{
	hufnode *s, *rl, *rr,*root1;
	root1 = root;
	while (root&&root->next)
	{
		rl = root;
		rr = root->next;
		root = rr->next;
		s = (hufnode *)malloc(sizeof(hufnode));
		s->parent = NULL;
		rl->parent = s;
		rr->parent = s;
		s->info = NULL;
		s->next = NULL;
		s->data = rl->data + rr->data;
		s->lchild = rl;
		s->rchild = rr;
		//rl->next = rr->next = NULL;
		root = insert(root, s);					
	}
	printf("������ɣ�\n");
	return root;
}
int readdata(hufnode x[])							//���ļ���ȡ����
{
	char ch;
	int fru;
	FILE *fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	int i = 0;
	while (fscanf(fp, "%c %d\n", &ch, &fru) >= 0)
	{
		x[i].info = ch;
		x[i].data = fru;
		i++;
	}
	/*for (int j = 0; j < i; j++)
	{
		printf("%c %d\n", x[j].info, x[j].data);
	}
	printf("��ȡ�ɹ���\n");*/
	return i;
}
void QuickSort(hufnode y[], int left, int right)				//���ṹ�������������
{
	hufnode x;
	int i, j, flag = 1;
	if (left < right)
	{
		i = left;
		j = right;
		x = y[i];
		while (i < j)
		{
			while (i < j&&x.data < y[j].data)
				j--;
			if (i < j)
				y[i++] = y[j];
			while (i < j&&x.data > y[i].data)
				i++;
			if (i < j)
				y[j--] = y[i];
		}
		y[i] = x;
		QuickSort(y, left, i - 1);		//�ݹ�ʵ��
		QuickSort(y, i + 1, right);		//�ݹ�ʵ��
	}
}
hufnode *tolink(hufnode a[], int count)				//������������Ԫ���������������γ���������
{
	node *h = NULL, *q = NULL, *p = NULL;
	int  i;
	for (i = 0; i < count; i++)
	{
		p = (node *)malloc(sizeof(node));
		p->info = a[i].info;
		p->data = a[i].data;
		p->lchild = NULL;
		p->rchild = NULL;
		p->next = NULL;
		if (i == 0)
		{
			h = p; q = p;
		}
		else
		{
			q->next = p; q = p;
		}
	}
	return h;
}

void treeencode(hufnode *t,hufnode *h,int count)
{
	int i = 0,j;
	hufnode *p,*q,*tmp;
	stack s;
	init(&s);
	p = h;
	q = h;
	while(p!=NULL)
	{
		q = p;
		while (q!=t)
		{
			tmp = q;
			q = q->parent;
			if (q->lchild == tmp)
			{
				push(&s, 0);
			}
			if (q->rchild == tmp)
			{
				push(&s, 1);
			}
		}
		j = 0;
		for (j = 0; s.top > 0; j++)
		{
			p->encode[j] = pop(&s);
		}
		p->encode[j] = 2;
		if (p->info != NULL)
		{
			printf("%c ", p->info);
			for (j = 0; p->encode[j] != 2; j++)
			{
				printf("%d", p->encode[j]);
			}
			printf("\n");
		}
		p = p->next;
	}
}
void init(stack *s)					//ջ�ĳ�ʼ�����廯ʵ��
{
	s->top = 0;
}
void push(stack *s, int a)				//ѹջ���廯ʵ��
{
	s->data[s->top++] = a;
}
int pop(stack *s)					//��ջ���廯ʵ��
{
	s->top--;
	return(s->data[s->top]);
}
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef int ELEMTYPE;

//���������ڵ�ṹ��
typedef struct HuffmanTree
{
	ELEMTYPE weight;
	ELEMTYPE id;//����Ȩֵ��ͬ�Ľڵ�
	struct HuffmanTree* lchild;
	struct HuffmanTree* rchild;
}HuffmanNode;

//������������
HuffmanNode* createHuffmanTree(int* T,int n)
{
	int i,j;
	HuffmanNode **temp,*huffmanTree;
	temp =(HuffmanNode**)malloc(n*sizeof(HuffmanNode));

	//������T�е�Ȩֵ��ֵ���ڵ��е�weight
	for(i=0;i<n;i++)
	{
		temp[i]=(HuffmanNode*)malloc(sizeof(HuffmanNode));
		temp[i]->weight =T[i];
		temp[i]->id =i;
		temp[i]->lchild =temp[i]->rchild =NULL;
	}

	//��������������ҪN-1�ϲ�
	for(i=0;i<n-1;i++)
	{
		int small1=-1,small2;//��small1��small2�ֱ���Ϊ��Сֵ�ʹ�Сֵ���±�

		//�Ƚ���С�������±긳ֵ��small1��small2����ӦȨֵδ����С
		for(j=0;j<n;j++)
		{
			if(temp[j]!=NULL&&small1==-1)
			{
				small1=j;
				continue;
			}
			else if(temp[j]!=NULL)
			{
				small2=j;
				break;
			}
		}
		for(j=small2;j<n;j++)//�Ƚ�Ȩֵ��Ų��small1��small2ʹ֮�ֱ��Ϊ��СȨֵ�ʹ�СȨֵ���±�
		{
			if(temp[j]!=NULL)
			{
				if(temp[j]->weight<temp[small1]->weight )
				{
					small2=small1;
					small1=j;
				}
				else if(temp[j]->weight<temp[small2]->weight)
				{
					small2=j;
				}
			}
		}
		huffmanTree=(HuffmanNode*)malloc(sizeof(HuffmanNode));
		huffmanTree->weight =temp[small1]->weight +temp[small2]->weight;
		huffmanTree->lchild =temp[small1];
		huffmanTree->rchild =temp[small2];

		temp[small1]=huffmanTree;
		temp[small2]=NULL;
	}
	free(temp);
	return huffmanTree;
}



//�ݹ����������
void Huffman_code(HuffmanNode* huffmanTree,int depth)
{
	static int code[10];
	if(huffmanTree)
	{
		if(huffmanTree->lchild ==NULL&&huffmanTree->rchild ==NULL)
		{
			printf("ȨֵΪ%d��Ҷ�ӽڵ�Ĺ���������Ϊ",huffmanTree->weight );
			int i;
			for(i=0;i<depth;i++)
			{
				printf("%d",code[i]);
			}
			printf("\n");
		}
		else
		{
			code[depth]=0;
			Huffman_code(huffmanTree->lchild,depth+1);
			code[depth]=1;
			Huffman_code(huffmanTree->rchild,depth+1);
		}
			
	}
}
int main()
{
	int i,n,*arr,WPL,len=0;
	printf("������Ҷ�ڵ�ĸ�����\n");
	while(1)
	{
		scanf("%d",&n);
		if(n>1)break;
		else printf("����������������룺");
	}
	arr=(int*)malloc(n*sizeof(ELEMTYPE));
	printf("������%d��Ҷ�ڵ��Ȩֵ��\n",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	HuffmanTree* huffmanTree=NULL;
	huffmanTree=createHuffmanTree(arr, n);


	printf("�˹���������Ҷ�ڵ�ı���Ϊ��\n");
	Huffman_code(huffmanTree,0);
	return 0;
}

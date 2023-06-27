#include<iostream>
#include<stdlib.h>
#include<string.h> 
#include<fstream>
using namespace std;
typedef int ELEMTYPE;
#define M 20
//���������ڵ�ṹ��
typedef struct HuffmanTree
{
	char character;
	ELEMTYPE weight;
	ELEMTYPE id;//����Ȩֵ��ͬ�Ľڵ�
	struct HuffmanTree* lchild;
	struct HuffmanTree* rchild;
}HuffmanNode;
typedef struct letter{
	char character;
	int number;
	char code[M];
}letter,*let;
//������������
HuffmanNode* createHuffmanTree(letter record[],int n)
{
	int i,j;
	HuffmanNode **temp,*huffmanTree;
	temp =(HuffmanNode**)malloc(n*sizeof(HuffmanNode));

	//������T�е�Ȩֵ��ֵ���ڵ��е�weight
	for(i=0;i<n;i++)
	{
		temp[i]=(HuffmanNode*)malloc(sizeof(HuffmanNode));
		temp[i]->weight =record[i].number;
		temp[i]->id =i;
		temp[i]->lchild =temp[i]->rchild =NULL;
		temp[i]->character=record[i].character;
	
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
void Huffman_code(HuffmanNode* huffmanTree,int depth,letter record[],int n)
{
	static int code[M];
	if(huffmanTree)
	{
		if(huffmanTree->lchild ==NULL&&huffmanTree->rchild ==NULL)
		{
			
			int i;
			int j;
			for(j=0;j<n;j++){
				if(huffmanTree->character==record[j].character){
					break;
				}
			} 
			for(i=0;i<depth;i++)
			{
				record[j].code[i]=code[i];
			}
			record[j].code[i]='\0';
			
		}
		else
		{
			code[depth]='0';
			Huffman_code(huffmanTree->lchild,depth+1,record,n);
			code[depth]='1';
			Huffman_code(huffmanTree->rchild,depth+1,record,n);
		}
			
	}
}
void Huffman_change(letter record[],int n){
	fstream fileout,filein;
	char c;
	int i=0,j=0;
	int count=0;
	fileout.open("code.dat",ios::out|ios::binary);
	filein.open("data.txt",ios::in);
	while(!filein.eof()&&filein>>c){
		for(i=0;i<n;i++){
			if(record[i].character==c){
				for(j=0;j<20&&record[i].code[j]!='\0';j++)
				fileout<<record[i].code[j];
				fileout<<endl;
			}
		}
		count++;
	}
	fileout.close();
	filein.close();
}
void Huffman_return(letter record[],int n){
	fstream filein("code.dat",ios::in|ios::out|ios::binary);
	int i=0;
	char code[M];
	int flag=0;
	while(!filein.eof()&&filein>>code){
		for(i=0;i<n;i++){
			if(!strcmp(record[i].code,code)){
				cout<<record[i].character;
				flag++;
			}
		}
	
	}
	
}
int main()
{
	void fileread(letter record[],int &n);
	int i,n=0,*arr,WPL,len=0;
	letter record[80];
	fileread(record,n);
	HuffmanTree* huffmanTree=NULL;
	arr=(int*)malloc(n*sizeof(ELEMTYPE));
	huffmanTree=createHuffmanTree(record, n);//���й��������Ĵ��� 
	Huffman_code(huffmanTree,0,record,n);//���й��������� 
	Huffman_change(record,n);//�����������е��ַ�ת��Ϊ���������� 
	Huffman_return(record,n);//�ٽ�����������ת��Ϊ�ı��������Ļ�� 
	return 0;
}
void fileread(letter record[],int &n){//�����ַ��Ĵ��ļ���ͳ�ƼӶ�ȡ���� 
	fstream file;
	char c;
	n=0;
	int i=0,j=0;
	int flag=0;
	for(i=0;i<80;i++){
		record[i].character='\0';
		record[i].number=0;
		for(j=0;j<M;j++){
			record[i].code[j]='\0';
		}
	}
	file.open("data.txt",ios::in);
	if(!file.is_open()){
		exit(0);
	}
	while(!file.eof()&&file>>c){
		for( i=0;i<=n;i++){
		if(record[i].character==c){
				record[i].number++;
				break;
			}
		}
		if(i==n+1){
			record[i].character=c;
			record[i].number=1;
			n++;
		}
		flag++;
		
	}
	//cout<<flag;//ͳ���ַ��� 
	file.close();
}

#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string> 
#define INF 0x7fffffff 

using namespace std;

fstream source,Huffman,code,decodes;
//�ļ������� 

typedef struct Node
{
	int key;
	//��Ӧ�ַ� 
	int count;
	//���ִ���
	int p;
	//�����
	int l;
	int r;
	//�����ӽ�� 
}node;

typedef struct Json
{
	int val;
	string key;
}json;
//ӳ�������ַ� 

node counts[256];
//ͳ���ַ����ִ���
int num;
//ͳ�Ƴ��ֵ��ַ��� 
int bitmap[40000];
int length; 
//���ڴ洢������Huffman���룬��ʹ��λ�ĳ���
vector<string> codes;
//���ڴ洢�ַ�����ʽ�ı���
Json test[10000];
//����ͨ��Huffman�����ַ�����������Ӧ�ַ� 

int hash(string p)
{
	int x = 1,y;
	string key = p;
	//���ڴ�����ײ
	 
	for(int i = 0;i < p.size();i++)
	{
		x *= p[i];
		x -= p[i] / 2;
		x %= 10000;
	}
	y = x;
	
	while(test[x].key.size() && !(test[x].key == key))
	//���������ײ���������һλ 
	{
		x++;
		x %= 10000;
		if(x == y)
		{
			cout << "Error hash,memery is out!!!\n";
			exit(0);
		}
		//��ֹ��� 
	}
	
	return x;
}
//hash����

void setBit(int * bit,int i)
{
	bit[i / sizeof(int) / 8] |= 1 << (i % (sizeof(int) * 8));
	
	return;
}
//����ָ����λΪ1 

void clearBit(int * bit,int i)
{
	bit[i / sizeof(int) / 8] &= (1 << (i % (sizeof(int) * 8))) ^ 0xffffffff;
	
	return;
}
//����ָ����λΪ0 

bool getBit(int * bit,int i)
{
	return bit[i / sizeof(int) / 8] & 1 << (i % (sizeof(int) * 8));
}
//���ָ����λ��ֵ 

void Init()
{
	source.open("source.txt",ios::in);
	//��ȡԭʼӢ������ 
	source >> noskipws;
	//�����Կո�ͻ��� 
	
	Huffman.open("Huffman.txt",ios::out);
	//�洢���ַ����ִ����ͱ���
	
	code.open("code.dat",ios::out | ios::binary);
	//�洢��������ʽ�ı���������
	
	decodes.open("decode.txt",ios::out);
	//�洢��������ʽ�ı���������
	
	for(int i = 0;i < 128;i++)
	{
		counts[i].key = i;
	}
	//��ʼ��node�е�keyֵ 
}
//��ʼ���ļ����ͽṹ������ 

void Fini()
{
	source.close();
	Huffman.close();
	code.close();
	decodes.close();
	
	return;
}
//�ر��ļ��� 

void create()
{
	for(int i = 0;i < num - 1;i++)
	{
		int min1 = INF,min2 = INF;
		int a = 0,b = 0,j = 0;
		while(j < 256 && counts[j].count)
		{
			if(!counts[j].p && counts[j].count < min2)
			{
				if(counts[j].count < min1)
				{
					min2 = min1; 
					min1 = counts[j].count;
					b = a;
					a = j;
				}
				else
				{
					min2 = counts[j].count;
					b = j;
				}
			}
			j++;
		} 
		if(j < 256)
		{
			counts[a].p = j;
			counts[b].p = j;
			counts[j].l = a;
			counts[j].r = b;
			counts[j].count = min1 + min2;
			//cout << j << ".  " << "l:" << counts[j].l << ",r:";
			//cout << counts[j].r << ",count:" << counts[j].count <<endl;
		}
	}
	
	return;
}
//����Huffman�� 

void count()
{
	char x;
	
	source >> x;
	while(!source.eof())
	{
		counts[x].count++;
		source >> x;
		//cout << x;
	}
	
	for(int i = 0;i < 128;i++)
	{
		if(counts[i].count)
		{
			num++;
		}
		else
		{
			counts[i].count = INF;
		}
	}
	
	source.close();
	source.open("source.txt",ios::in); 
	source >> noskipws;
	//���´�׼������
	 
	return;
}
//�����ַ����ֵĴ��� 

void encode()
{
	for(int i = 0;i < 128;i++) {
		string temp;
		int j = i;
		int p = counts[i].p;
		while(p) {
			if (counts[p].l == j)temp.insert(0,"0");
			else temp.insert(0,"1");
			j = p;
			p = counts[p].p;
		}
		codes.push_back(temp);
	}
	
	for(int i = 0;i < 128;i++) {
		if(counts[i].count == INF)
		{
			continue;
		}
		//cout << (char)i << ".  " << "val is " << counts[i].count << ", code is " << codes[i] << endl;
		Huffman << setw(10) << counts[i].key;
		Huffman << setw(10) << counts[i].count;
		Huffman << setw(10) << codes[i];
		Huffman << endl;
	}
	Huffman.close();
	Huffman.open("Huffman.txt",ios::in);
	//���´�׼��������ı� 
	
	char x;
	
	source >> x;
	while(!source.eof())
	{
		//cout << "string:" << codes[x] << "\t\tbit:";
		string s = codes[x];
		for(int i = 0;i < s.size();i++)
		{
			if(s[i] == '0')
			{
				clearBit(bitmap,length);
				//cout << getBit(bitmap,length);
				length++;
			}
			else if(s[i] == '1')
			{
				setBit(bitmap,length);
				//cout << getBit(bitmap,length);
				length++;
			}
		}
		//cout << "\t\tchar:" << x << endl;
		source >> x;
	}
	
	code << length << "\n";
	code.write((char *)bitmap,length / 8 + 1);
	
	code.close();
	code.open("code.dat",ios::in | ios::binary);
	//��ȡ��������ʽ�ı���������׼������ 
	
	
	return; 
}
//����Huffman���벢���ַ�����ʽ���棬д��Huffman�ļ���code�ļ� 

void decode()
{
	//cout << length << endl;
	code >> length;
	char pad[100];
	int pad2;
	//cout << length << endl;
	//cout << hex << bitmap[1] << endl;
	code.getline(pad,100);
	code.read((char *)bitmap,length / 8 + 1);
	//cout << hex << bitmap[1] << endl;
	code.clear();
	
	string key;
	int val;
	Huffman >> val;
	while(!Huffman.eof())
	{
		Huffman >> pad2;
		Huffman >> key;
		//cout << key << endl;
		//cout << val << endl;
		test[hash(key)].key = key;
		test[hash(key)].val = val;
		Huffman >> val;
	}
	
	string m;
	char n;
	for(int i = 0;i < length;i++)
	{
		if(getBit(bitmap,i))
		{
			m += '1';
		}
		else
		{
			m += '0';
		}
		if(test[hash(m)].key.size())
		{
			n = test[hash(m)].val;
			//cout << "str:" << m << "\t\tval: " << (char)n << endl; 
			decodes << n;
			m = "";
		}
	}
	
	return;
}
//ͨ��Huffman���������ܱ������ļ� 

int main()
{
	Init();
	
	count();
	create();
	encode();
	decode();
	
	Fini(); 
	
	return 0;
}

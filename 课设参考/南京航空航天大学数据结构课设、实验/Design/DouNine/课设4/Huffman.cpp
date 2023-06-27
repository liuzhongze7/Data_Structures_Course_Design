/*
[��������]
��һƪ������2000�ַ���Ӣ�����£�source.txt����ͳ�Ƹ��ַ����ֵĴ�����
ʵ��Huffman����(code.dat)���Լ��Ա������Ľ���(recode.txt)��
[����Ҫ��]
��1�����ÿ���ַ����ֵĴ����ͱ���,���洢�ļ�(Huffman.txt)��
��2����Huffman�����Ӣ�����±��������浽�ļ���(code.dat)��
	�����������Ƕ�������ʽ����0 1����Ϣ�ñ���λ��ʾ���������ַ���0���͡�1����ʾ��
��3��ʵ�ֽ��빦�ܡ�
*/
#include<cstdio>
#include<cstring>
#include<cstdlib> 
#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

// ���ܳ��ֵ��ַ����� 
#define CharCount 300

// λ���������ݸ�ʽ 
#define dataType unsigned int
#define dataLen 32

// �ַ��ṹ�壬�ַ�Ϊ�ṹ�������±� 
typedef struct 
{
	int count;		// ���ַ����ֵĴ��� 
	dataType code;	// ���ַ��ı���ת���� 
	char codeLen; 	// �����Ʊ���ĳ���
}Char;

// Huffman���Ľ��ṹ�� 
typedef struct 
{
	char ch;
	int weight;
	int parent;
	int lchild, rchild;
}HuffmanTree;


// ȫ�ֱ��� 
FILE *fp;
char fileName[100];


// ���ļ� 
void fileOpen(char *method) 
{
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// �ر��ļ� 
void fileClose() 
{
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
}

// ������������
void CreateHuffmanTree(HuffmanTree * &hTree, int n, int m) 
{
	// ����n-1����������Сֵ 
	for (int i=1; i<=n-1; i++) 
	{
		int fMin = INT_MAX, sMin = INT_MAX-1;	// ��ʼ����һС�͵ڶ�С��Ȩֵ 
		int fMinP = 0, sMinP = 0;            	// Ȩֵ��һС�͵ڶ�С��λ�� 
		int j = 1;
		// ���������Ѿ���Ȩֵ�Ľ�� 
		while (j<m && hTree[j].weight) 
		{
			// ����ý��û��˫�ף���ȨֵС�ڵڶ�С��Ȩֵ 
			if ((!hTree[j].parent) && (hTree[j].weight < sMin)) 
			{
				// �����ȨֵС�ڵ�һ��С��Ȩֵ 
				if (hTree[j].weight < fMin) 
				{
					sMin = fMin;
					sMinP = fMinP; 
					fMin = hTree[j].weight;
					fMinP = j;
				}
				// ����ڵ�һ�͵ڶ�СȨֵ�м� 
				else 
				{
					sMin = hTree[j].weight;
					sMinP = j;
				}
			}
			j++;
		}
		// j���ͣ��û��Ȩֵ���½�����һ�У���������������Ϊ�½��ĺ��� 
		if (j < m) 
		{

			hTree[fMinP].parent = j;
			hTree[sMinP].parent = j;
			
			hTree[j].lchild = fMinP;
			hTree[j].rchild = sMinP;
			hTree[j].weight = fMin + sMin;
		}
	}
	
//	cout<<"�����������ɹ�:\n";
//	for (int i=1; i<m; i++) {
//		cout<<hTree[i].ch<<" "<<hTree[i].weight<<" "<<hTree[i].parent<<" "<<hTree[i].lchild<<" "<<hTree[i].rchild<<endl;
//	}
}

// ����x�������n����λ��ֵΪbo(0,1) 
void SetBit(dataType &x, int n, int bo) 
{
	if (bo) x = x | 1U<<n;
	else x = x & ~(1U<<n);
}

// ��ȡx��n����m(��λ����λ)����λ��ֵ���������������� 
dataType GetBit(dataType x, int n, int m) 
{
	return (x & ~(~0U<<(m-n+1))<<n) >>n;
}

// ��01�ַ�����ʽ�Ķ�����ת�������� 
void getCode(stack<char> hCode, dataType &code, char &codeLen) 
{
	codeLen = hCode.size();
	if (codeLen > dataLen) 
	{
		printf("���ֳ��ޱ��룡��\n");
		return ;
	}
	
	// �ַ�ջ�е�ջ���Ƕ����Ƶĸ�λ 
	int i = codeLen-1;
	code = 0;
	while (!hCode.empty()) 
	{
		char bitCh = hCode.top();
		printf("%c", bitCh);
		SetBit(code, i, bitCh-'0');
		hCode.pop();
		i--;
	}
}

// ������ת�����ַ�����ʽ��01������
stack<char> setCode(dataType code, char codeLen) 
{
	// ջ���Ǹ�λ 
	stack<char> hCode;
	int i = 0;
	while (i < codeLen) 
	{
		hCode.push(GetBit(code, i, i) + '0');
		i++;
	}
	return hCode; 
}

// ���������� 
void HuffmanEnCode(HuffmanTree *hTree, int n, int m, Char *chs) 
{
	
	vector< stack<char> > hCodes;	// ���Huffman�������Ķ�̬���� 
	stack<char> temp;
	// ����1��n��λ�ã��ӽ�㿪ʼ��˫�� 
	for (int i=1; i<=n; i++) 
	{
		//cout<<i<<endl;
		int son = i;
		int parent = hTree[son].parent;	// �ҵ�˫��
		// ��˫�ײ�Ϊ�գ���û�е�ͷ 
		while (parent) 
		{
			// ����ý����˫�׵����� 
			if (hTree[parent].lchild == son) temp.push('0');
			// ������Һ��� 
			else temp.push('1');
			// �ҵ���һ�����Ӱְ� 
			son = parent;
			parent = hTree[son].parent;
		}
		hCodes.push_back(temp);
		while (!temp.empty()) temp.pop();
	}
	
	printf("\n--------Huffman������---------\n");
	// ����hCodes��ά���� 
	for (int i=0; i<hCodes.size(); i++) 
	{
		printf("�ַ���%c---Ȩ�أ�%d---���룺", hTree[i+1].ch, hTree[i+1].weight);	// hCodes��0λ�ö�ӦhTree�е�1λ�� 
		getCode(hCodes[i], chs[hTree[i+1].ch].code, chs[hTree[i+1].ch].codeLen);
		printf("--->%d(len:%d)\n", chs[hTree[i+1].ch].code, chs[hTree[i+1].ch].codeLen);
	}
	printf("\n"); 
}

// ���������� 
char HuffmanDeCode(HuffmanTree *hTree, int n, int m, stack<char> hCode) 
{
	
	char ch, top;
	int pos = m-1;
	while (!hCode.empty()) 
	{
		top = hCode.top();
		//cout<<top<<"---"<<pos<<endl;
		hCode.pop();
		if (top == '0') pos = hTree[pos].lchild;
		else pos = hTree[pos].rchild;
	}
	// ������Ӳ�Ϊ��(0)
	if (hTree[pos].lchild || hTree[pos].rchild) return 0;
	return hTree[pos].ch;
}


int main() 
{
	
	Char chs[CharCount];	// ASCII�������256���ַ� 
	for (int i=0; i<CharCount; i++) 
	{
		chs[i].count = 0;
	}
	
	// ��ȡ�ı��ļ�����ͳ���ַ����ִ��� 
	strcpy(fileName, "source.txt");
	fileOpen("r");
	char source[100000];		// �ı� 
	int count = 0;			// �ı����� 
	int n = 0;				// �ж��ٸ��ַ� 
	while (!feof(fp)) 
	{
		fscanf(fp, "%c", &source[count]);
		printf("%c", source[count]);
		if (chs[source[count]].count == 0) n++;
		chs[source[count]].count++;
		count++;
	}
	fileClose();
	
	// ��ʼ��Huffman�����Ա� 
	int m = 2*n;	// huffman�� ���ݽṹ(���Ա�) �ĳ��ȣ����ж��ٸ����(2n-1��)
	HuffmanTree *hTree = (HuffmanTree*)malloc(sizeof(HuffmanTree) * m);
	for (int i=1; i<m; i++) 
	{
		hTree[i].weight = hTree[i].parent = hTree[i].lchild = hTree[i].rchild = 0;
	}
	// ��Huffman�����Ա���1��nλ�ø�ֵ 
	int j = 1;		
	for (int i=0; i<CharCount; i++) 
	{
		if (chs[i].count) 
		{
			hTree[j].parent = hTree[j].lchild = hTree[j].rchild = 0;
			hTree[j].weight = chs[i].count;
			hTree[j].ch = i; 
			j++;
		}
	}
	
	CreateHuffmanTree(hTree, n, m);		// ��Huffman��
	HuffmanEnCode(hTree, n, m, chs);	// Huffman���� 

	
	// ���ַ����ִ����Ͷ�Ӧ�Ķ����Ʊ��뱣�浽�ļ� 
	strcpy(fileName, "Huffman.txt");
	fileOpen("w");
	stack<char> hCode;
	for (int i=0; i<CharCount; i++) 
	{
		if (chs[i].count) 
		{
			//printf("�ַ���%c---Ȩ�أ�%d---���룺%d(len:%d)\n", i, chs[i].count, chs[i].code, chs[i].codeLen);
			fprintf(fp, "�ַ���%c---���ִ�����%d---�����Ʊ��룺", i, chs[i].count);
			stack<char> hCode = setCode(chs[i].code, chs[i].codeLen);
			while (!hCode.empty()) 
			{
				fprintf(fp, "%c", hCode.top());
				hCode.pop();
			}
			fprintf(fp, "\n");
		}
	}
	fileClose();
	
	
	// ���ı����б��벢������������ļ� 
	strcpy(fileName, "code.dat");
	fileOpen("wb");
	queue<Char> q;	// ����
	for (int i=0; i<count; ) 
	{
		int lenSum = 0;
		// ȡ����ַ������Ƕ����Ʊ��볤�ȼ�����С��dataType���ݶ����Ʊ��볤�� 
		while (1) 
		{
			lenSum += chs[source[i]].codeLen;
			if (lenSum > dataLen) break;
			q.push(chs[source[i]]);
			i++;
		}
		
		// �������ַ������Ķ��������ݣ���dataType���ݵĸ�λ��ʼ��� 
		dataType data = 0;
		int pos = dataLen-1; 	// posָ��Ҫ�����ļ���dataType���ݸ�λ 
		while (!q.empty()) 
		{
			Char temp = q.front();
			q.pop();
			int j = temp.codeLen-1, bo = 0;		// j���ַ������Ķ����Ƶĸ�λ
			// j�����β�������ַ������Ʊ���ȫ������dataType������ 
			while (j>=0) 
			{
				bo = GetBit(temp.code, j, j);	// ��ȡ��λ�õĶ�������
				SetBit(data, pos, bo);			// ����dataType��posλ�õĶ�������
				j--;
				pos--;
			}
		}
		fwrite(&data, sizeof(dataType), 1, fp);
	}
	fileClose();


	// ��ȡ�������ļ������н��� 
	strcpy(fileName, "code.dat");
	fileOpen("rb");
	char recode[10000];
	int i = 0;
	dataType data;
	// ÿ�δ��ļ��ж�ȡһ��dataType�������͵����� 
	while (fread(&data, sizeof(dataType), 1, fp)) 
	{
		// �Ӹ����ݵĸ�λ��ʼ 
		int pos = dataLen-1, j = 0;
		while (pos-j >= 0) 
		{
			dataType temp = GetBit(data, pos-j, pos);// GetBit�Ǵӵ�λ����λ��ȡ���������� 
			// ͨ��setCode��������ת����01�ַ�������ͨ��HuffmanDeCode���Ҹö����ƶ�Ӧ���ַ� 
			char res = HuffmanDeCode(hTree, n, m, setCode(temp, j+1));
			// ��������ַ���Ϊ����˵���ҵ��ˣ���� 
			if (res) 
			{
				recode[i] = res;
				i++;
				printf("%c", res); 
				pos -= (j+1);	// pos-(j+1)��ָ����һ�������ƶ�Ӧ���ַ����� 
				j = 0;
				continue;
			}
			j++;
		}
	}
	fileClose();
	
	
	// ��������д�뵽�ı� 
	strcpy(fileName, "recode.txt");
	fileOpen("w");
	for (int i=0; i<count; i++) 
	{
		fprintf(fp, "%c", recode[i]);
	}
	fileClose();
	
	
	free(hTree);
}

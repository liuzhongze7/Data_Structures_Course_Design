/*
[��������]
����JSON (JavaScript Object Notation) ��һ�������������ݽ�����ʽ��
	��������������ṹ�������ݡ�JSON ��ʽ�еĻ�����Ԫ��ֵ (value)��
	���ڼ򻯵�Ŀ�ı���ֻ�漰 2 �����͵�ֵ��
����* �ַ��� (string)���ַ�������˫���� " ��������һ���ַ�������Ϊ�գ���
		����ַ����������г���˫���� "����˫����ǰ��ӷ�б�ܣ�Ҳ������ \" ��ʾ��
		������ַ�б�� \������������б�� \\ ��ʾ��
		��б�ܺ��治�ܳ��� " �� \ ������ַ������磺""��"hello"��"\"\\"��
����* ���� (object)��������һ���ֵ�Ե����򼯺ϣ�����Ϊ�գ���
		��ֵ�Ա�ʾ��������ԣ�������������ֵ�����Ե����ݡ�
		������������ { ��ʼ���һ����� } ��������ֵ��֮���Զ��� , �ָ���
		һ����ֵ�Եļ���ֵ֮����ð�� : �ָ������������ַ�����
		ͬһ���������м�ֵ�Եļ���������������ͬ��ֵ�������ַ�����Ҳ��������һ������
		���磺
		{}��{"foo": "bar"}��{"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}��
���������ַ����ڲ���λ�ã�����λ�ö����Բ���һ�������ո�ʹ�� JSON �ĳ��ָ������ۣ�
	Ҳ������һЩ�ط����У�����Ӱ������ʾ���������ݡ�
	���磬������������һ�� JSON ����Ҳ����д��������ʽ��
����{
����"Mon": "weekday",
����"Tue": "weekday",
����"Sun": "weekend"
����}
��������һ�� JSON ��ʽ���������ݣ��Լ����ɲ�ѯ����̷�����Щ��ѯ�Ľ����
�����ʽ
������һ�������������� n �� m���ֱ��ʾ JSON ���ݵ������Ͳ�ѯ�ĸ�����
���������� n �У�����һ�� JSON ���ݣ���֤������һ���Ϸ��� JSON ����
���������� m �У�ÿ������һ����ѯ������Ҫ��ѯ����������
	Ҫ�󷵻ض�Ӧ���Ե����ݡ���Ҫ֧�ֶ���ѯ�������������֮����С���� . ���ӡ�
	��֤��ѯ�ĸ�ʽ���ǺϷ��ġ�
[����Ҫ��]
�����ʽ
�������������ÿһ����ѯ����˳�������ѯ�����ÿ�����ռһ�С�
���������ѯ�����һ���ַ���������� STRING <string>������ <string> ���ַ�����ֵ���м���һ���ո�ָ���
���������ѯ�����һ����������� OBJECT������Ҫ�����������ݡ�
���������ѯ��������ڣ������ NOTEXIST��
��������
10 5
{
	"firstName": "John",
	"lastName": "Smith",
	"address": {
		"streetAddress": "2ndStreet",
		"city": "NewYork",
		"state": "NY"
	},
	"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
�������
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
[����Ҫ��] 
��1��Ҫ����ı��ļ������룻
��2������Ŀ��ʵ����һ����ͨ��������ÿ�����ĺ��������̶������ܵ�������n�������������
	���Կ���ʹ�ú����ֵܱ�ʾ���Ƚ��б�ʾ�ʹ洢��
��3���ϸ���Ҫ������������ʽ�������ݵ����롢�����ѵ��CSP�����еĸ�ʽ�������������ȷ�ԣ���
��4��ѡ����ʹ��ͼ�ν��棨���ַ���ʽ���ڳɵ����νṹ���ο�Linux�µ�tree�����
	����״��ʽ��ʾ�����JSON��ʽ���ݡ�
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<windows.h>

using namespace std; 

typedef struct TNode 
{
	char key[100];
	char value[100];
	TNode *child;
	TNode *brother;
}*Tree;

// ȫ�ֱ��� 
FILE *fp;
char fileName[] = "json3.txt";


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

// �������
void TraverseTree(Tree tree) 
{
	if (tree) 
	{
		printf("%s:%s\n", tree->key, tree->value);
		TraverseTree(tree->brother);
		TraverseTree(tree->child);
	}
}

// ����
void DestroyTree(Tree &tree) 
{
	if (tree) 
	{
		DestroyTree(tree->brother);
		DestroyTree(tree->child);
		free(tree);
	}
}

// �ַ���������
void HandleStr(char *source, int start, int end, char *dist) 
{
	//printf("before handle: %s  start: %d---%c  end: %d---%c\n", source, start, source[start], end, source[end]);
	int i = start+1;
	int j = 0;
	while (i != end) 
	{
		if (source[i] == '\\') i++;
		dist[j] = source[i];
		i++;
		j++;
	}
	dist[j] = '\0';
	//printf("after handle : %s\n", dist);
}

// ����Ƿ��������ַ�(����)�������������¶�ȡ�ַ��� 
void Check(char* &str, int &pos) 
{
	if (pos >= strlen(str)) 
	{
		fscanf(fp, "%s", str);
		pos = 0;
	}
}

// �����������ݹ� 
void CreateTree(Tree &tree, char *str, int &i) 
{
	
	TNode *preNode = tree, *node;
	bool flag = false;	// �ж��Ƿ�Ϊ���ڵ� 
	i++;				// i++�ܹ�'{' 
	Check(str, i);
	
	while (str[i] != '}') 
	{
		node = (TNode*)malloc(sizeof(TNode));
		
		//printf("ǰһ��======%s\n", str);
		if (str[i] == '"') 
		{
			int j = i;
			while (str[j] != ':' && j < strlen(str)) j++;
			HandleStr(str, i, j-1, node->key);
			i = j;
			Check(str, i);
		}
		i++;
		Check(str, i);
		
		//printf("��һ��=====%s\n", str);
		if (str[i] == '{') 
		{
			strcpy(node->value, "object");
			CreateTree(node->child, str, i);	// ֵ��һ��������ݹ���� 
		}
		else if (str[i] == '"') 
		{
			node->child = NULL; 
			int j = i;
			while (str[j] != ',' && str[j] != '}' && j < strlen(str)) j++;
			HandleStr(str, i, j-1, node->value);
			i = j;
			Check(str, i);
		}
		
		// ��Ϊ��һ������򽫽��ָ�븳��treeָ�� 
		if (!flag) 
		{
			tree = node;
			flag = true;
		}
		// ���ǵ�һ����㣬���ϸ������ֵ�ָ��ǰ��� 
		else preNode->brother = node;
		preNode = node;
		
		// ���������һ��û��','����� 
		if (str[i] == '}') break;
		i++;
		Check(str, i);
	}
	node->brother = NULL;
	i++;	// ʹָ��ָ��'}'����һ���������ڶ�������������� 
}
 
// ��valueֵ
char* FindValue(Tree tree, char *str) 
{
	int i = 0;
	char key[1000];
	while (str[i]!='.' && i<strlen(str)) 
{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	
	TNode *node = tree;
	while (node) 
	{
		if (strcmp(node->key, key) == 0) 
		{
			if (str[i] == '.') 
			{
				int j = 0;
				char nextStr[1000];
				i++;
				while (i<strlen(str)) 
				{
					nextStr[j] = str[i];
					i++;
					j++;
				}
				nextStr[j] = '\0';
				return FindValue(node->child, nextStr);
			}
			else return node->value;
		}
		node = node->brother;
	}
	return NULL;
} 

// ��ʾ�� 
void ShowTree(Tree tree, int tab) 
{	
	TNode *node = tree;
	while (node) 
	{
		for (int i=0; i<tab; i++) printf("|  ");
		printf("|--%s", node->key);
		if (node->child) 
		{
			printf("\n");
			ShowTree(node->child, tab+1);
		}
		else printf(":%s\n", node->value);
		node = node->brother;
	}
} 


int main() 
{
	fileOpen("r");
	
	int n = 0, m = 0;
	fscanf(fp, "%d%d", &n, &m);
	
	Tree tree = NULL;
	char strLine[10000];
	fscanf(fp, "%s", strLine);
	int start = 0;
	CreateTree(tree, strLine, start);	// 1λ�ÿ�ʼ���Կ�ʼ��'{'
	
	system("cls");	// ���� 
	//TraverseTree(tree);
	printf("+\n");
	ShowTree(tree, 0);
	printf("\n\n�����������");
	getchar();
	system("cls");
	
	// ��ȡ�������� 
	for (int i=0; i<m; i++) 
	{
		fscanf(fp, "%s", strLine);
		char *ret = FindValue(tree, strLine);
		char value[1000];
		if (!ret) sprintf(value, "NOTEXIST");
		else if (strcmp(ret, "object") == 0) sprintf(value, "OBJECT");
		else sprintf(value, "STRING %s", ret);
		printf("%s\n", value);
	}
	
	DestroyTree(tree);
	fileClose();
}

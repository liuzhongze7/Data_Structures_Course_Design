/*
[��������]
���ü����ṹ������һ��΢�͵����ֵ䡣
[����Ҫ��]
ʵ�����ʵļ��룬���ʵĲ��ҡ�ɾ�����޸ĵȲ�����
*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;

typedef struct TNode
{
	char type;	// typeֵ��1��ʾ�ǵ��ʽ�β��0���ʾ����
	char *meaning;	// ���Ľ��� 
	char ch;
	TNode *child;
	TNode *brother;
}*Tree;

// ȫ�ֱ��� 
FILE *fp;
char fileName[] = "testWord.txt";


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

// ��ʾ�� 
void ShowTree(Tree tree, int tab) 
{	
	TNode *node = tree;
	while (node) 
	{
		for (int i=0; i<tab; i++) printf("|  ");
		printf("|--%c(%d)\n", node->ch, node->type);
		if (node->child) 
		{
			ShowTree(node->child, tab+1);
		}
		node = node->brother;
	}
}

// ��ʾ������ 
void ShowWordTree(Tree tree, char *word, int tab) 
{
	if (!tree) return;
	
	TNode *node = tree;
	char nextWord[100];
	strcpy(nextWord, word);
	int next = strlen(nextWord);
	while (node) 
	{
		nextWord[next] = node->ch;
		nextWord[next+1] = '\0';
		
		for (int i=0; i<tab; i++) printf("|  ");
		if (node->type) printf("|--%c(%s  %s)\n", node->ch, nextWord, node->meaning);
		else printf("|--%c\n", node->ch);
		
		ShowWordTree(node->child, nextWord, tab+1);
		node = node->brother;
	}
}

// ���ӵ���
void AddWord(Tree &tree, char *word, char *meaning) 
{
	if (strlen(word) == 0) return;
	//printf("%s  %s\n", word, meaning);
	
	char ch = word[0];
	char nextWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	
	// �����Ϊ�գ����� 
	if (!tree) 
	{
		tree = (TNode*)malloc(sizeof(TNode));
		tree->child = NULL;
		tree->brother = NULL;
		tree->ch = ch;
		tree->type = 0;
	}
	
	// ���ֵ�����ƥ�� 
	TNode *node = tree, *pre = NULL;
	while (node && node->ch <= ch) 
	{
		if (node->ch == ch) 
		{
			if (strlen(word) == 1) {
				node->type = 1;
				node->meaning = meaning;
			}
			AddWord(node->child, nextWord, meaning);
			return;
		}
		pre = node;
		node = node->brother;
	}
	
	// ����ֵ�û�ҵ�ƥ��ģ����½���� 
	TNode *newNode = (TNode*)malloc(sizeof(TNode));
	newNode->child = NULL;
	newNode->ch = ch;
	newNode->type = 0; 
	newNode->brother = node;
	
	if (!pre) tree = newNode;
	else pre->brother = newNode;
	
	if (strlen(word) == 1) {
		newNode->type = 1;
		newNode->meaning = meaning;
	}
	AddWord(newNode->child, nextWord, meaning);
} 

// ɾ������ 
void DeleteWord(Tree &tree, char *word) 
{
	if (strlen(word) == 0) return;
	
	char ch = word[0];
	char nextWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	
	TNode *node = tree, *pre = NULL;
	while (node) 
	{
		if (node->ch == ch) 
		{
			// �Ƚ����ַ�֮����ַ�ɾȥ 
			DeleteWord(node->child, nextWord);
			if (node->type) free(node->meaning);
			// ɾ����ǰ�ַ� 
			if (pre) 
			{
				pre->brother = node->brother;
				free(node);
			}
			else 
			{
				tree = node->brother;
				free(node);
			}
		}
		pre = node;
		node = node->brother;
	}
}

// ���ҵ��ʣ����ڷ���true�������ڷ���false 
Tree FindWord(Tree tree, char *word) 
{
	char ch = word[0];
	char nextWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	
	TNode *node = tree;
	while (node) 
	{
		if (node->ch == ch) 
		{
			if (strlen(word) == 1) 
			{
				return node;
			}
			else return FindWord(node->child, nextWord);
		}
		node = node->brother;
	}
	
	return NULL;
}

// �޸ĵ��� 
void ModifyWord(Tree &tree, char *word, char *newWord, char *meaning) 
{
	//printf("----%s %s----\n", word, newWord);
	
	char ch = word[0], newCh = newWord[0];
	char nextWord[100], nextNewWord[100];
	for (int i=0; i<strlen(word); i++) nextWord[i] = word[i+1];
	for (int i=0; i<strlen(newWord); i++) nextNewWord[i] = newWord[i+1];
	
	TNode *node = tree;
	while (node) 
	{
		//printf("%c %c\n", node->ch, ch);
		if (node->ch == ch) 
		{
			if (ch != newCh) 
			{
				node->ch = newCh;
			}
			if (strlen(newWord) == 1) 
			{
				node->type = 1;
				node->meaning = meaning;
				DeleteWord(node->child, nextWord);
			}
			else if (strlen(word) == 1) 
			{
				node->type = 0;
				AddWord(node->child, nextNewWord, meaning);
			}
			else ModifyWord(node->child, nextWord, nextNewWord, meaning);
		}
		node = node->brother;
	}
}

// ��ȫ����
void CompleteWord(Tree tree, char *word) 
{
	if (!tree) return;
	
	TNode *node = tree;
	char nextWord[100];
	strcpy(nextWord, word);
	int next = strlen(nextWord);
	while (node) 
	{
		nextWord[next] = node->ch;
		nextWord[next+1] = '\0';
		
		if (node->type) 
		{
			printf("-->%s  %s\n", nextWord, node->meaning);
		}
		CompleteWord(node->child, nextWord);
		node = node->brother;
	}
} 

// ��ʼ����
void CreateTree(Tree &tree) 
{
	char word[100];
	while (!feof(fp)) 
	{
		char *meaning = (char*)malloc(sizeof(char) * 100);
		fscanf(fp, "%s", word);
		fgets(meaning, 99, fp);
		//ȥ����ȡһ�еĻس�
		if (meaning[strlen(meaning)-1] == 10) {
			meaning[strlen(meaning)-1] = '\0';
		}
		//printf("%s  %s\n", word, meaning);
		AddWord(tree, word, meaning);
		//ShowWordTree(tree, "", 0);
	}
} 

// ����
void DestroyTree(Tree &tree) 
{
	if (tree) 
	{
		DestroyTree(tree->brother);
		DestroyTree(tree->child);
		if (tree->type) free(tree->meaning);
		free(tree);
	}
}

// ��ʾѡ��
void choose() 
{
	system("cls");
	printf("\n|---------------------------|\n");
	printf("|0.�˳�                     |\n");
	printf("|1.���ӵ���                 |\n");
	printf("|2.ɾ������                 |\n");
	printf("|3.�޸ĵ���                 |\n");
	printf("|4.���ҵ���                 |\n");
	printf("|5.��ʾ������               |\n");
	printf("|---------------------------|\n");
	printf("\n���������ѡ��(0-5):\n");
}


int main() 
{
	fileOpen("r");
	
	Tree tree = NULL;
	CreateTree(tree);
	
	int n = 0;
	choose();
	scanf("%d", &n);
	while (n) 
	{
		if (n <= 0 || n > 5) 
		{
			printf("error! try again\n");
			printf("\n���������ѡ��(0-5):\n");
			scanf("%d", &n);
			continue;
		}
		
		char word[100];
		switch (n) 
		{
			// ���ӵ��� 
			case 1: 
			{
				printf("��������Ҫ���ӵĵ��ʣ�\n");
				scanf("%s", word);
				char *meaning = (char*)malloc(sizeof(char) * 100);
				printf("�����������ӵ��ʵ���˼��\n");
				scanf("%s", meaning);
				AddWord(tree, word, meaning);
				printf("���ӳɹ���"); 
				break;
			}
			// ɾ������ 
			case 2: 
			{
				printf("��������Ҫɾ���ĵ��ʣ�\n");
				scanf("%s", word);
				DeleteWord(tree, word);
				printf("ɾ���ɹ���");
				break;
			}
			// �޸ĵ��� 
			case 3: 
			{
				printf("��������Ҫ�޸ĵĵ��ʣ�\n");
				scanf("%s", word);
				if (!FindWord(tree, word)) 
				{
					printf("no this word\n");
					break;
				}
				char newWord[100];
				printf("�������޸ĺ�ĵ��ʣ�\n");
				scanf("%s", newWord);
				char *meaning = (char*)malloc(sizeof(char) * 100);
				printf("���������޸ĺ󵥴ʵ���˼��\n");
				scanf("%s", meaning);
				ModifyWord(tree, word, newWord, meaning);
				printf("�޸ĳɹ���");
				break;
			}
			// ���ҵ��� 
			case 4: 
			{
				printf("��������Ҫ���ҵĵ��ʣ�\n");
				scanf("%s", word);
				Tree node = FindWord(tree, word);
				if (node && node->type) printf("find this word\n");
				else 
				{
					printf("no find this word\n");
					if (node) 
					{
						printf("\ni guess you want to find these words:\n\n");
						CompleteWord(node->child, word);
					}
				}
				break;
			}
			// ��ʾ������ 
			case 5: 
			{
				printf("*\n");
				ShowWordTree(tree, "", 0);
				break;
			}
		}
		
		printf("\n");
		system("pause");
		choose();
		scanf("%d", &n);
	}
	
	DestroyTree(tree);
	fileClose();
}

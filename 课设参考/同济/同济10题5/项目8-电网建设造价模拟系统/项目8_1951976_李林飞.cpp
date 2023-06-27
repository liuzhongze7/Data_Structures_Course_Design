/*
* FileName:  MinimunCostTree.cpp
* Function:  ��С��������Prim�㷨�����·��
* Author:    ���ַ�
* StuNumber: 1951976
* Date:      2020.12.14
*/

#include <iostream>
#include <string.h>

using namespace std;


/* �߽�� */
struct EdgeNode
{
	int weight;
	char start;
	char end;
	EdgeNode(){}        // ���캯��
	EdgeNode(char s, char e, int w)
	{
		start = s;
		end = e;
		weight = w;
	}
};


/* ͼ�� */
class Graph
{
private:
	int VerticesNum = 0;                     // ������
	int EdgesNum = 0;                        // ����
	int** EdgeMatrix = NULL;                 // �ڽӾ���ͼ�Ĺ�ϵ�洢����
	char * VerticesList = NULL;              // ������ַ������������±����Ӧ  
	const int MaxWeight = INT_MAX;           // �������ֵ�������������
	EdgeNode *MiniSpanTree;                  // ��С���������洢��

	int IndexVertices(char nodeName);        // ͨ���������Ѱ�Ҷ�Ӧ���±�
	void AddNode();                          // ������������
	void AddEdge();                          // ��ӵ����ı�
	void CreateMiniSpanningTree();           // ������С������
	void PrintTree();                        // ��ʾ��С������
	void Destroy();                          // �˳�����ɾ��ͼ

public:          
	void Switch(char choice);                // ѡ���������
};

// ����ѡ��
void Graph::Switch(char choice)
{
	switch (choice)
	{
	case 'A': AddNode(); break;
	case 'B': AddEdge(); break;
	case 'C': CreateMiniSpanningTree(); break;
	case 'D': PrintTree(); break;
	case 'E': Destroy(); break;
	}
}

// �����ַ��������ڽӾ����е��±�
int Graph::IndexVertices(char nodeName)
{
	for (int i = 0; i < VerticesNum; i++)
		if (VerticesList[i] == nodeName)
			return i;
	return -1;
}


// ������㣬Ϊ���������������ַ��������ֶ�Ӧ
void Graph::AddNode()
{
	cout << "�����붥��ĸ����� ";
	int nodeNum;
	cin >> nodeNum;

	while (nodeNum < 2)                 // ��ⶥ������ĺϷ���
	{
		cout << "������Ӧ���������Ҵ���2�����������룺 ";
		cin >> nodeNum;
	}

	VerticesNum = nodeNum;
	VerticesList = new char[VerticesNum + 3];
	cout << "���������������ƣ�\n";
	for (int i = 0; i < VerticesNum; i++)
		cin >> VerticesList[i];              // �洢��㣬�����±����ַ�һһ��Ӧ�Ĺ�ϵ
}

// �����
void Graph::AddEdge()
{
	if (VerticesNum == 0)
	{
		cout << "�޶��㣬�����߹�ϵ���봴�����㣺\n";
		Switch('A');
	}

	// ��̬�����ά����-- �ڽӾ���
	EdgeMatrix = new int* [VerticesNum];
	for (int i = 0; i < VerticesNum; i++)
		EdgeMatrix[i] = new int[VerticesNum];

	for (int i = 0; i < VerticesNum; i++)     // �ڽӾ����ʼ��
		for (int j = 0; j < VerticesNum; j++)
			EdgeMatrix[i][j] = (i == j) ? 0 : MaxWeight;

	char start, end;        // �ߵ������յ�
	int weight;            // �ߵ�Ȩֵ
	int v1, v2;            // �ڽӾ�����������
	while (1)
	{
		cout << "�������������㼰�ߣ�����������0 0 0���� ";
		cin >> start >> end >> weight;
		if (start == '?' || end == '?' || weight == 0)
			break;
		v1 = IndexVertices(start);
		v2 = IndexVertices(end);

		while (v1 == -1 || v2 == -1)             // �ߺϷ��Լ��
		{
			if(v1 == -1)
				cout << "�������" << start << "��㲻���ڣ�\n";
			else if(v2 == -1)
				cout << "�������" << end << "��㲻���ڣ�\n";
			else if(v1 == -1 && v2 == -1)
				cout << "�������" << start << "��" << end << "��㲻���ڣ�\n";

			cout << "�����������������㼰��(����������0 0 0)�� ";
			cin >> start >> end >> weight;
			v1 = IndexVertices(start);
			v2 = IndexVertices(end);
		}

		if (EdgeMatrix[v1][v2] != MaxWeight && EdgeMatrix[v1][v2] > 0)
			cout << "���ظ�����߹�ϵ���˱���Ϣ�������ԣ���������룺\n";

		if (v1 > -1 && v1 < VerticesNum && v2 > -1 && v2 < VerticesNum
			&& EdgeMatrix[v1][v2] == MaxWeight)           // ��������
		{
			EdgeMatrix[v1][v2] = EdgeMatrix[v2][v1] = weight;
			EdgesNum++;                                   // ������1
		}
	}
}

// ������С������
void Graph::CreateMiniSpanningTree()
{
	if (VerticesNum == 0)
	{
		cout << "�޶���ͱ߹�ϵ���޷�������С���������봴������ͱ߹�ϵ��\n";
		Switch('A');
		Switch('B');
	}
	else if (EdgeMatrix == NULL)
	{
		cout << "û�б߹�ϵ���޷�������С������������ӱ߹�ϵ��\n";
		Switch('B');
	}

	int* lowcost = new int[VerticesNum];
	int* nearVex = new int[VerticesNum];

	
	
	cout << "��������С����������ʼ���㣺 ";
	char tagStart;     // ��ʼ��
	cin >> tagStart;
    
	while (IndexVertices(tagStart) == -1)     // ��ʼ�������
	{
		cout << "���������ʼ���㲻���ڣ����������룺";
		cin >> tagStart;
	}

	int startU = IndexVertices(tagStart);   // ��ʼ�����
	lowcost[startU] = 0;
	for (int i = 0; i < VerticesNum; i++) 
	{
		if (i != startU)
		{
			lowcost[i] = EdgeMatrix[startU][i];  // ��ʼ���㵽���ߵĴ���
			nearVex[i] = startU;                 // ��̴�Ȩ·��
		}
	}

	nearVex[startU] = -1;      // ����startU�ӵ����������㼯��
	int count = 0;             // ����
	MiniSpanTree = new EdgeNode[VerticesNum - 1];

	for(int i = 1; i < VerticesNum; i++)
	{
		int min = MaxWeight;
		int v = startU;
		for(int j = 0; j < VerticesNum; j++)
			if (nearVex[j] != -1 && lowcost[j] < min)
			{
				v = j;
				min = lowcost[j];
			}

		if (v != startU)
		{
			EdgeNode e(VerticesList[nearVex[v]], VerticesList[v], lowcost[v]);
			MiniSpanTree[count++] = e;    // ѡ���߼���������
			nearVex[v] = -1;    
			for(int k = 0; k < VerticesNum; k++)
				if (nearVex[k] != -1 && EdgeMatrix[v][k] < lowcost[k])
				{
					lowcost[k] = EdgeMatrix[v][k];
					nearVex[k] = v;
				}
		}
	}
	cout << "����Prim��С��������\n";
}

// ��ӡ��С������
void Graph::PrintTree()
{
	if (VerticesNum == 0)
	{
		cout << "�޶���ͱ߹�ϵ�������ݿɴ�ӡ���봴����С��������\n";
		Switch('A');
		Switch('B');
		Switch('C');
	}
	else if (EdgeMatrix == NULL)
	{
		cout << "û�б߹�ϵ���޷�������С�������� ����ӱ߹�ϵ��\n";
		Switch('B');
		Switch('C');
	}
	else if (MiniSpanTree == NULL)
	{
		cout << "δ������С�������������ݿɴ�ӡ���봴����С��������\n";
		Switch('C');
	}

	cout << "��С�������Ķ��㼰��Ϊ��\n";
	for (int i = 0; i < VerticesNum - 1; i++)
		cout << MiniSpanTree[i].start << " --<" 
			 << MiniSpanTree[i].weight << ">--> "
			 << MiniSpanTree[i].end << "     ";
	cout << endl;
	
}

// �ͷſռ�
void Graph::Destroy()
{
	for (int i = 0; i < VerticesNum; i++)
		delete[] EdgeMatrix[i];
	delete[] EdgeMatrix;

	delete [] VerticesList;                 // ������ַ������������±����Ӧ  
	delete [] MiniSpanTree;                 // ��С������
	exit(1);
}

// ��ʼ������
void Interface()
{
	cout << "***********************************************\n";   
	cout << "**                                           **\n";
	cout << "**              �������ģ��ϵͳ             **\n";
	cout << "**                                           **\n";
	cout << "***********************************************\n";
	cout << "**              A --- ������������           **\n";
	cout << "**              B --- ��ӵ����ı�           **\n";
	cout << "**              C --- ������С������         **\n";
	cout << "**              D --- ��ʾ��С������         **\n";
	cout << "**              E --- �˳�����               **\n";
	cout << "**                                           **\n";
	cout << "***********************************************\n\n";
}


/*============================================= ������ ========================================*/
int main()
{
	Interface();
	char choice;
	Graph netCost;
	while (1)
	{
		cout << "\n��ѡ������� ";
		cin >> choice;

		while (choice < 'A' || choice > 'E')     // ��������
		{
			cout << "������������ڣ����������룺 ";
			cin >> choice;
		}

		netCost.Switch(choice);
	}
	return 0;
}

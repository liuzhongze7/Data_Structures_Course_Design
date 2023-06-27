/*
* FileName: OptimalBinaryTree.cpp
* Function: �������Ŷ�Ԫ����������ǰ׺����
* Author: ���ַ�
* StuNumber: 1951976
* Date: 2020.12.07
*/

#include <iostream>
using namespace std;

/******* Huffman����� ******/
struct HuffmanNode
{
	int weight;                         // �洢Ȩֵ
	HuffmanNode* leftChild;            // ����
	HuffmanNode* rightChild;           // �Һ���
	HuffmanNode* parent;               // �����
};


/****** ����������С�� ******/
class MinHeap
{
private:
	const int DefaultSize = 100;         // �������
	HuffmanNode* heap;                  // ��̬����洢��С��
	int CurrentSize;                     // ��ǰ�����
	void ShiftUp(int start);             // ���ϵ���
	void ShiftDown(int start, int m);    // ���µ���
public:
	MinHeap();                           // ���캯��
	~MinHeap();                          // ��������
	void Insert(HuffmanNode* current);  // ����
	HuffmanNode* getMin();              // ��ȡ��С���
};

// ���캯��
MinHeap::MinHeap()
{
	heap = new HuffmanNode[DefaultSize]; // �����ѿռ�
	CurrentSize = 0;
}

// ��������
MinHeap::~MinHeap()
{
	delete[] heap; // �ͷſռ�
}

// ����
void MinHeap::Insert(HuffmanNode* current)
{
	if (CurrentSize == DefaultSize)
	{
		cout << "������" << endl;
		return;
	}
	// ��current�����ݸ��Ƶ�������ĩβ��
	heap[CurrentSize] = *current;
	// ���ϵ�����
	ShiftUp(CurrentSize);
	CurrentSize++;
}

// ��ȡ��С��㲢�ڶ���ɾ���ý��
HuffmanNode* MinHeap::getMin()
{
	if (CurrentSize == 0)
		return NULL;

	HuffmanNode* newNode = new HuffmanNode();
	if (newNode == NULL)
	{
		cerr << "�洢�ռ����ʧ�ܣ�" << endl;
		exit(1);
	}

	*newNode = heap[0];              // ����С�������ݸ��Ƹ�newNode
	heap[0] = heap[CurrentSize - 1]; // �����һ��Ԫ���
	CurrentSize--;
	ShiftDown(0, CurrentSize - 1);   // ��0λ�ÿ�ʼ���µ���
	return newNode;
}

// ���ϵ���
void MinHeap::ShiftUp(int start) {
	// ��start��ʼ��ֱ��0���ߵ�ǰֵ����˫�׽���ֵʱ��������
	int j = start, i = (j - 1) / 2; // i��j��˫��

	HuffmanNode temp = heap[j];
	while (j > 0) 
	{
		if (heap[i].weight <= temp.weight)
			break;
		else 
		{
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

// ���µ���
void MinHeap::ShiftDown(int start, int m) {
	int i = start, j = 2 * i + 1;    // j��i������Ů

	HuffmanNode temp = heap[i];
	while (j <= m) {
		if (j < m && heap[j].weight > heap[j + 1].weight)
			j++;                     // ѡ������Ů�н�С��
		if (temp.weight <= heap[j].weight)
			break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}


/****** �������� ******/
class HuffmanTree
{
private:
	HuffmanNode* root;                                  // �����
	int total;                                          // ������
	void Destroy(HuffmanNode* current);                 // ���ٹ�������
	void PreOrder(HuffmanNode* current); // ǰ�����Huffman��
public:
	HuffmanTree() { root = new HuffmanNode; root = NULL; }            // ���캯��
	~HuffmanTree() { Destroy(root); }                    // ��������
	void Create(int w[], int n);                         // ������������
	void Merge(HuffmanNode* first, HuffmanNode* second, HuffmanNode* parent); // �ϲ�      
	int MiniCost();                                      // ������С���ѣ�����Ҷ�ӽ���ֵ֮��
};

// ���ٹ�������
void HuffmanTree::Destroy(HuffmanNode* current)
{
	if (current != NULL)      // ��Ϊ��
	{ 
		Destroy(current->leftChild);  // �ݹ�����������
		Destroy(current->rightChild); // �ݹ�����������
		delete current;               // �ͷſռ�
		current = NULL;               // �ͷź��ָ�븳ֵNULL����Լ���ʹ��
	}
}

// ������������
void HuffmanTree::Create(int w[], int n) {
	int i;
	MinHeap hp; // ʹ����С�Ѵ��ɭ��
	HuffmanNode* first, * second, * parent = NULL;
	HuffmanNode* work = new HuffmanNode();

	if (work == NULL)
	{
		cerr << "�洢�ռ����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (i = 0; i < n; i++)
	{
		work->weight = w[i];
		work->leftChild = work->rightChild = work->parent = NULL;
		hp.Insert(work); // ���뵽��С����
	}

	if (n == 1)
	{
		root = new HuffmanNode;
		root->weight = w[0];
		return;
	}
	
	for (i = 0; i < n - 1; i++)
	{ // ��n-1�ˣ��γ�Huffman��
		first = hp.getMin(); // ��ȡȨֵ��С����
		second = hp.getMin(); // ��ȡȨֵ��С����
		parent = new HuffmanNode();
		if (parent == NULL)
		{
			cerr << "�洢�ռ����ʧ�ܣ�" << endl;
			exit(1);
		}
		Merge(first, second, parent); // �ϲ�
		if(parent)
			hp.Insert(parent); // ���²��뵽��С����
	}
	root = parent; // �����
}
// �ϲ�
void HuffmanTree::Merge(HuffmanNode* first, HuffmanNode* second, HuffmanNode* parent)
{
	parent->leftChild = first; // ������
	parent->rightChild = second; // ������
	parent->weight = first->weight + second->weight; // �����Ȩֵ
	first->parent = second->parent = parent; // ��ָ��
}

// ǰ�����������С����
void HuffmanTree::PreOrder(HuffmanNode* current)
{
	if (current->leftChild == NULL && current->rightChild == NULL)
		return;
	else
		total += current->weight;

	PreOrder(current->leftChild);
	PreOrder(current->rightChild);

}

int HuffmanTree::MiniCost()
{
	PreOrder(root);
	return total;
}

/******* ������ ******/
int a[10005];
int main()
{
	cout << "******************************************\n";
	cout << "**                                      **\n";
	cout << "**              ��������ϵͳ            **\n";
	cout << "**                                      **\n";
	cout << "******************************************\n\n";

	char flag;
	do {
		cout << "������ľͷ�Ŀ���(N <= 10^4)�� ";
		int N;
		cin >> N;
		while (N <= 0)   // N <= 0
		{
			cout << "����ӦΪ�����������������룺 ";
			cin >> N;
		}

		cout << "������ÿ��ľͷ�ĳ��ȣ� ";
		for (int i = 0; i < N; i++)
		{
			cin >> a[i];
			if (a[i] <= 0)
			{
				cout << "ľ�鳤��ӦΪ�����������Ѿ�û�л����ˣ�\n";
				exit(1);
			}
		}
		
		int cost;
		if (N == 1)
			cost = 0;
		else
		{
			HuffmanTree tree;
			tree.Create(a, N);
			cost = tree.MiniCost();
		}
		cout << "��С����Ϊ�� " << cost << endl;

		cout << "\n�������ԣ���y or another char��: ";
		cin >> flag;
	} while (flag == 'y');

	cout << "��ӭ�ٴ�ʹ�ã�" << endl;

	return 0;
}

/*
����N��Ȩֵ��1-100������������������������
8
5 29 7 8 14 23 3 11
*/
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<stack>
using namespace std;

typedef struct {
	int weight;
	int parent;
	int lchild, rchild;
}HuffmanTree;

// ������������
void CreateHuffmanTree(HuffmanTree * &hTree, int n, int m) {
	// ����n-1����������Сֵ 
	for (int i=1; i<=n-1; i++) {
		int fMin = INT_MAX, sMin = INT_MAX-1;	// ��ʼ����һС�͵ڶ�С��Ȩֵ 
		int fMinP = 0, sMinP = 0;            	// Ȩֵ��һС�͵ڶ�С��λ�� 
		int j = 1;
		// ���������Ѿ���Ȩֵ�Ľ�� 
		while (j<m && hTree[j].weight) {
			// ����ý��û��˫�ף���ȨֵС�ڵڶ�С��Ȩֵ 
			if ((!hTree[j].parent) && (hTree[j].weight < sMin)) {
				// �����ȨֵС�ڵ�һ��С��Ȩֵ 
				if (hTree[j].weight < fMin) {
					sMin = fMin;
					sMinP = fMinP; 
					fMin = hTree[j].weight;
					fMinP = j;
				}
				// ����ڵ�һ�͵ڶ�СȨֵ�м� 
				else {
					sMin = hTree[j].weight;
					sMinP = j;
				}
			}
			j++;
		}
		// j���ͣ��û��Ȩֵ���½�����һ�У���������������Ϊ�½��ĺ��� 
		if (j < m) {

			hTree[fMinP].parent = j;
			hTree[sMinP].parent = j;
			
			hTree[j].lchild = fMinP;
			hTree[j].rchild = sMinP;
			hTree[j].weight = fMin + sMin;
		}
	}
	
	cout<<"�����������ɹ�:\n";
	for (int i=1; i<m; i++) {
		cout<<hTree[i].weight<<" "<<hTree[i].parent<<" "<<hTree[i].lchild<<" "<<hTree[i].rchild<<endl;
	}
}


// ��ʾ���������� 
void ShowHuffmanCoding(HuffmanTree *hTree, int n, int m) {
	vector< stack<char> > hCode;
	stack<char> temp;
	// �ӽ�㿪ʼ��˫�� 
	for (int i=1; i<=n; i++) {
		cout<<i<<endl;
		int j = i;
		int parent = hTree[i].parent;	// �ҵ�˫��
		// ��˫�ײ�Ϊ�գ���û�е�ͷ 
		while (parent) {
			// ����ý����˫�׵����� 
			if (hTree[parent].lchild == j) temp.push('0');
			// ������Һ��� 
			else temp.push('1');
			j = parent;
			parent = hTree[j].parent;
		}
		hCode.push_back(temp);
		while (!temp.empty()) temp.pop();
	}
	
	for (int i=0; i<n; i++) {
		cout<<"��"<<i+1<<"������ȨֵΪ��"<<hTree[i+1].weight<<"������Ϊ��";
		while (!hCode[i].empty()) {
			cout<<hCode[i].top();
			hCode[i].pop();
		}
		cout<<endl;
	}
}


int main() {
	printf("������Ҫ�����Ȩֵ�ĸ���:");
	int n = 0;
	scanf("%d", &n);
	
	// ��ʼ�������������Ա� 
	int m = 2 * n;
	HuffmanTree *hTree = (HuffmanTree*)malloc(sizeof(HuffmanTree) * m);
	for (int i=1; i<m; i++) {
		hTree[i].weight = hTree[i].parent = hTree[i].lchild = hTree[i].rchild = 0;
	}
	
	printf("����������Ȩֵ��\n");
	for (int i=1; i<=n; i++) {
		scanf("%d", &hTree[i].weight);
	}
	
	CreateHuffmanTree(hTree, n, m);
	ShowHuffmanCoding(hTree, n, m);
	
	free(hTree);
}

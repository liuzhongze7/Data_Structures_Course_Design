/*
��д�㷨�ж��������Ƿ�Ϊ��ȫ������
ͼ��
	   A
	 B  C
   D  E   F
	G  H    J
   I  K L 
*/
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<queue>
#include<stack>

using namespace std;


typedef struct BTNode {
	char data;
	BTNode *lchild, *rchild;
}BTNode, *BiTree;


// ����+���� ������
void CreateBiTree(BiTree &bTree, string preOrder, string inOrder) {
	bTree = (BTNode*)malloc(sizeof(BTNode));
	bTree->data = preOrder[0];
	
	int pos = inOrder.find(preOrder[0]);
	string inOrderL = inOrder.substr(0, pos);
	string inOrderR = inOrder.substr(pos + 1, inOrder.length() - 1);
	string preOrderL = preOrder.substr(1, inOrderL.length());
	string preOrderR = preOrder.substr(inOrderL.length() + 1, preOrder.length() - 1);
	
	int isEmptyL = 0, isEmptyR = 0;		// �����ж����ҽ���Ƿ�Ϊ�յı�־λ 
	if (inOrderL.empty()) {
		bTree->lchild = NULL;
		isEmptyL = 1;
	}
	if (inOrderR.empty()) {
		bTree->rchild = NULL; 
		isEmptyR = 1;
	}
	if (!isEmptyL) {
		// cout<<preOrderL<<endl<<inOrderL<<endl;
		CreateBiTree(bTree->lchild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		// cout<<preOrderR<<endl<<inOrderR<<endl;
		CreateBiTree(bTree->rchild, preOrderR, inOrderR);
	}	
}


// ����������ݹ�
void PreOrderTraverse(BiTree bTree, int tab) {
	if (bTree) {
		for (int i=0; i<tab; i++) cout<<"  ";
		cout<<bTree->data<<endl;
		PreOrderTraverse(bTree->lchild, tab+1);
		PreOrderTraverse(bTree->rchild, tab+1);
	} 
}


// ����������ݹ� 
void InOrderTraverse(BiTree bTree, int tab) {
	if (bTree) {
		InOrderTraverse(bTree->lchild, tab+1);
		for (int i=0; i<tab; i++) cout<<"  ";
		cout<<bTree->data<<endl;
		InOrderTraverse(bTree->rchild, tab+1);
	} 
}


// ����������ȣ��ݹ� 
int BiTreeDepth(BiTree bTree) {
	if (bTree) {
		int lchildDepth = 0;
		if (bTree->lchild) lchildDepth = BiTreeDepth(bTree->lchild);
		int rchildDepth = 0;
		if (bTree->rchild) rchildDepth = BiTreeDepth(bTree->rchild);
		return lchildDepth > rchildDepth ? lchildDepth+1 : rchildDepth+1;
	}
	return 0;
}


// ������
void DestoryBiTree(BiTree &bTree) {
	if (!bTree) {
		cout<<"����Ϊ�գ�";
		return; 
	}
	
	cout<<"��ʼ��������\n";
	// ��������ֻ�ܽ������ָ�봫��ȥ����ΪfreeҪ�������ָ�� 
	stack<BiTree> s;
	s.push(bTree);
	bTree = NULL; 
	BiTree temp;
	
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<"���٣�"<<temp->data<<endl;
		if (temp->rchild) s.push(temp->rchild);
		if (temp->lchild) s.push(temp->lchild);
		free(temp);
	}
	cout<<"����������\n";
}


// �ж��Ƿ�Ϊ��ȫ������
void IsCompleteBiTree(BiTree bTree, string preOrder) {
	int depth = BiTreeDepth(bTree);
	int count = preOrder.length();
	cout<<"�������Ϊ��"<<depth<<endl;
	cout<<"���Ľ����Ϊ��"<<count<<endl;
	
	// ��ѧ�ж� 
	if (count < pow((double)2, (double)depth-1)) {
		cout<<"���Ľ���� n < 2^(depth-1)��������ȫ������\n"; 
		return;
	}
	else {
		queue<BiTree> q;
		q.push(bTree);
		
		// ������ 
		BiTree limit = (BTNode*)malloc(sizeof(BTNode) * 1);
		limit->data = ' ';
		limit->lchild = limit->rchild = NULL;
		q.push(limit);
		
		int d = 0, node = 0;  // ������Ⱥͽ���� 
		BiTree top, next;
		while (1) {
			top = q.front();
			q.pop();
			node++;
			
			// ���q.pop()����һ��Ԫ�غ����Ϊ�գ�˵�������������һ�е����һ����� 
			if (q.empty()) break;
			else next = q.front();
			
			// ����õ����ǽ�� 
			if (top->data == ' ') {
				q.push(top);// ������Żض����� 
				d++;		// ��ȼ�һ 
				node--;		// ����һ����Ϊ������ǽ��
				// �����d�н���ʱ��d�����ܵ����һ�У�������������  n = 2^d - 1 ��������ȫ������ 
				if (pow((double)2, (double)d) - 1 != node) {
					cout<<"�ɵ�"<<d<<"�п��Կ���������������ȫ������"<<endl;
					return; 
				}
			}
			// �����ж����һ�У���� ����Ϊ�յ��Һ��Ӳ��� �� �Һ��ӿյ���һ��������Ӳ��� 
			else if ((top->lchild == NULL && top->rchild != NULL) 
					|| (top->rchild == NULL && next->lchild != NULL)) { 
				cout<<"����������ȫ������"<<endl;
				return;
			}
			else {
				if (top->lchild) q.push(top->lchild);
				if (top->rchild) q.push(top->rchild);
			}
		}
	}
	cout<<"��������ȫ������\n";
}


int main() {

	// ��һ���� 
	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n����+�������ɹ�\n\n";
	
	// �ݹ�ʵ�� 
	cout<<"���������\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"���������\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// ����Ƿ�Ϊ������ 
	IsCompleteBiTree(bTree, preOrder);
	
	DestoryBiTree(bTree);
	
	
	// �ڶ����� 
	preOrder = "ABDHEJCFG";
	inOrder = "HDBJEAFCG";
		
	bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n����+�������ɹ�\n\n";
	
	// �ݹ�ʵ�� 
	cout<<"���������\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"���������\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// ����Ƿ�Ϊ������ 
	IsCompleteBiTree(bTree, preOrder);
	
	DestoryBiTree(bTree);
	
	// �������� 
	preOrder = "ABDHIEJCF";
	inOrder = "HDIBJEAFC";
		
	bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n����+�������ɹ�\n\n";
	
	// �ݹ�ʵ�� 
	cout<<"���������\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"���������\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// ����Ƿ�Ϊ������ 
	IsCompleteBiTree(bTree, preOrder);
	
	DestoryBiTree(bTree);
}

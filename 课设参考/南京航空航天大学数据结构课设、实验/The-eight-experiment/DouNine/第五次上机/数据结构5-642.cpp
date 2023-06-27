#include<iostream>
#include<stdlib.h>
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
		cout<<preOrderL<<endl<<inOrderL<<endl;
		CreateBiTree(bTree->lchild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		cout<<preOrderR<<endl<<inOrderR<<endl;
		CreateBiTree(bTree->rchild, preOrderR, inOrderR);
	}	
}


// ����������ǵݹ�
void preOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"����Ϊ�գ�";
		return;
	}
	
	cout<<"�ǵݹ����������";
	stack<BTNode> s;
	s.push(*bTree); 
	BTNode temp; 
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<temp.data;
		if (temp.rchild) s.push(*temp.rchild);
		if (temp.lchild) s.push(*temp.lchild);
	}
	cout<<endl;
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
	cout<<"����������"<<endl;
}


// ��������Ҷ����
int leafSum(BiTree bTree) {
	int sum = 0;
	if (!bTree->lchild && !bTree->rchild) {
		return 1;
	}
	else {
		if (bTree->lchild) sum += leafSum(bTree->lchild);
		if (bTree->rchild) sum += leafSum(bTree->rchild);
	}
	return sum;
} 

 
int main() {

	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n�����ɹ�\n\n";
	
	preOrderTraverseOther(bTree);
	cout<<endl;
	
	cout<<"Ҷ�Ӹ���Ϊ��"<<leafSum(bTree)<<endl<<endl; 
	
	// ������ 
	DestoryBiTree(bTree);
} 

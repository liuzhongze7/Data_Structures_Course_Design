/*
���㺢���ֵ�����Ҷ���� 
*/
/*
���ʵ�֣���һ���Ժ���-�ֵ������ʾ�����������ĸ߶ȡ�
*/
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>

using namespace std;

typedef struct CSTNode {
	char data;
	CSTNode *firstChild;
	CSTNode *nextSibling; 
}CSTNode, *CSTree;


// ����+���� ������
void CreateCSTree(CSTree &csTree, string preOrder, string inOrder) {
	csTree = (CSTNode*)malloc(sizeof(CSTNode));
	csTree->data = preOrder[0];
	
	int pos = inOrder.find(preOrder[0]);
	string inOrderL = inOrder.substr(0, pos);
	string inOrderR = inOrder.substr(pos + 1, inOrder.length() - 1);
	string preOrderL = preOrder.substr(1, inOrderL.length());
	string preOrderR = preOrder.substr(inOrderL.length() + 1, preOrder.length() - 1);
	
	int isEmptyL = 0, isEmptyR = 0;		// �����ж����ҽ���Ƿ�Ϊ�յı�־λ 
	if (inOrderL.empty()) {
		csTree->firstChild = NULL;
		isEmptyL = 1;
	}
	if (inOrderR.empty()) {
		csTree->nextSibling = NULL; 
		isEmptyR = 1;
	}
	if (!isEmptyL) {
		cout<<preOrderL<<endl<<inOrderL<<endl;
		CreateCSTree(csTree->firstChild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		cout<<preOrderR<<endl<<inOrderR<<endl;
		CreateCSTree(csTree->nextSibling, preOrderR, inOrderR);
	}	
}


// ����������ݹ�
void PreOrderTraverse(CSTree csTree) {
	if (csTree) {
		cout<<csTree->data;
		PreOrderTraverse(csTree->firstChild);
		PreOrderTraverse(csTree->nextSibling);
	} 
}


// ������
void DestroyCSTree(CSTree &csTree) {
	if (!csTree) {
		cout<<"����Ϊ�գ�";
		return; 
	}
	
	cout<<"��ʼ��������\n";
	// ��������ֻ�ܽ������ָ�봫��ȥ����ΪfreeҪ�������ָ�� 
	stack<CSTree> s;
	s.push(csTree);
	csTree = NULL; 
	CSTree temp;
	
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<"���٣�"<<temp->data<<endl;
		if (temp->nextSibling) s.push(temp->nextSibling);
		if (temp->firstChild) s.push(temp->firstChild);
		free(temp);
	}
	cout<<"����������";
}


// ������Ҷ���� 
int GetTreeLeaves(CSTree csTree) {
	if (!csTree) {
		cout<<"����Ϊ�գ�";
		return 0;
	}
	
	//cout<<"ok\n"; 
	stack<CSTree> s;
	s.push(csTree);
	CSTree top;
	int leaves = 0;
	while (!s.empty()) {
		//cout<<leaves<<endl;
		top = s.top();
		s.pop();
		if (!top->firstChild && !top->nextSibling) leaves++;
		else {
			if (top->firstChild) s.push(top->firstChild);
			if (top->nextSibling) s.push(top->nextSibling);
		}
	}
	
	return leaves;
} 


int main() {
	string preOrder = "ABFCGJHIKDE";
	string inOrder = "FBJGHKICDEA";
		
	CSTree csTree;
	CreateCSTree(csTree, preOrder, inOrder);
	cout<<"\n�����ɹ�\n\n";
	
	cout<<"����ݹ��������\n";
	PreOrderTraverse(csTree);
	cout<<endl<<endl;
	
	int leaves = GetTreeLeaves(csTree);
	cout<<"����Ҷ����Ϊ��"<<leaves<<endl<<endl;
	
	cout<<"������\n";
	DestroyCSTree(csTree);
}

/* 
���ʵ����P121  ADT BinaryTree ��������20�����ö�������ṹʵ�֣�
ͼ��
	   A
	 B  C
   D  E   F
	G  H    J
   I  K L 
*/
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
	
	bool isEmptyL = false, isEmptyR = false;		// �����ж����ҽ���Ƿ�Ϊ�յı�־λ 
	if (inOrderL.empty()) {
		bTree->lchild = NULL;
		isEmptyL = true;
	}
	if (inOrderR.empty()) {
		bTree->rchild = NULL; 
		isEmptyR = true;
	}
	if (!isEmptyL) {
		CreateBiTree(bTree->lchild, preOrderL, inOrderL);
	}
	if (!isEmptyR) {
		CreateBiTree(bTree->rchild, preOrderR, inOrderR);
	}	
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
	cout<<"����������\n\n";
}


// �ж����Ƿ�Ϊ�� 
bool BiTreeEmpty(BiTree bTree) {
	if (bTree) return false;
	else return true;
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


// �������ĸ� 
char Root(BiTree bTree) {
	return bTree->data;
}


// ���ؽ�� bTNode ��ֵ
char Value(BiTree bTree, const BTNode* bTNode) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp == bTNode) {
			return temp->data;
		}
		if (temp->lchild) s.push(temp->lchild);
		if (temp->rchild) s.push(temp->rchild);
	}
	return '\0';
}
 

// ����� bTNode ��ֵΪvalue
bool Assign(BiTree bTree, BTNode *bTNode, char value) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp == bTNode) {
			temp->data = value;
			return true;
		}
		if (temp->lchild) s.push(temp->lchild);
		if (temp->rchild) s.push(temp->rchild);
	}
	return false;
}


// ���ؽ�� bTNode ��˫��
BTNode* Parent(BiTree bTree, BTNode *bTNode) {
	if (bTree == bTNode) return NULL;
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			if (temp->lchild == bTNode) return temp;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			if (temp->rchild == bTNode) return temp;
			s.push(temp->rchild);
		}
	}
	return NULL;
}
 

// ���ؽ�� bTNode ������
BTNode* LeftChild(BiTree bTree, BTNode *bTNode) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			if (temp == bTNode) return temp->lchild;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			s.push(temp->rchild);
		}
	}
	return NULL;
} 


// ���ؽ�� bTNode ������
BTNode* RightChild(BiTree bTree, BTNode *bTNode) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			if (temp == bTNode) return temp->rchild;
			s.push(temp->rchild);
		}
	}
	return NULL;
} 


// ���ؽ�� bTNode �����ֵ� 
BTNode* LeftSibling(BiTree bTree, BTNode *bTNode) {
	if (bTree == bTNode) return NULL; 
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			if (temp->rchild == bTNode && temp->lchild) return temp->lchild;
			s.push(temp->rchild);
		}
	}
	return NULL;
}


// ���ؽ�� bTNode �����ֵ�
BTNode* RightSibling(BiTree bTree, BTNode *bTNode) {
	if (bTree == bTNode) return NULL; 
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			if (temp->lchild == bTNode && temp->rchild) return temp->rchild;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			s.push(temp->rchild);
		}
	}
	return NULL;
}


// ����insertBTree���뵽��BTree��bTNode���������(condition=0��1)������ 
bool InsertChild(BiTree bTree, const BTNode *bTNode, int condition, BiTree insertBTree) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp, tempLChild = NULL, tempRChild = NULL;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->lchild) {
			tempLChild = temp->lchild;
			s.push(temp->lchild);
		}
		if (temp->rchild) {
			tempRChild = temp->rchild;
			s.push(temp->rchild);
		}
		if (temp == bTNode) {
			if (temp->lchild && temp->rchild) return false;
			if (condition) {
				temp->rchild = insertBTree;
				insertBTree->rchild = tempRChild;
			}
			else {
				temp->lchild = insertBTree;
				insertBTree->rchild = tempLChild;
			}
			return true; 
		}
	}
	return false;
}


// ɾ��BTNode�������������(condition=0��1)
bool DeleteChild(BiTree bTree, BTNode *bTNode, int condition) {
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp, tempChild;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp == bTNode) {
			if (condition) {
				DestoryBiTree(temp->rchild);
			}
			else {
				DestoryBiTree(temp->lchild);
			}
			return true;
		}
		if (temp->lchild) s.push(temp->lchild);
		if (temp->rchild) s.push(temp->rchild);
	}
	return false;
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


// ����������ݹ� 
void PostOrderTraverse(BiTree bTree, int tab) {
	if(bTree) {
		PostOrderTraverse(bTree->lchild, tab+1);
		PostOrderTraverse(bTree->rchild, tab+1);
		for (int i=0; i<tab; i++) cout<<"  ";
		cout<<bTree->data<<endl;
	} 
}


// ��α������ǵݹ� 
void LevelOrderTraverse(BiTree bTree) {
	if (!bTree) {
		cout<<"����Ϊ�գ�";
		return; 
	}
	
	cout<<"��α�����";
	queue<BiTree> q;
	q.push(bTree);
	BiTree temp;
	while (!q.empty()) {
		temp = q.front();
		cout<<temp->data;
		if (temp->lchild) q.push(temp->lchild);
		if (temp->rchild) q.push(temp->rchild);
		q.pop();
	}
	cout<<endl;
} 


int main() {

	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n�����ɹ�\n\n";
	
	// �ݹ�ʵ�� 
	cout<<"���������\n";
	PreOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"���������\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	cout<<"���������\n";
	PostOrderTraverse(bTree, 0);
	cout<<endl<<endl;
	
	// ����������� 
	cout<<"������ȣ�"<<BiTreeDepth(bTree);
	cout<<endl<<endl;
	
	// ��α���
	LevelOrderTraverse(bTree);
	cout<<endl;
	
	// ���Ի�ȡֵ 
	BTNode *bTNode = bTree->lchild->rchild->rchild;
	cout<<"���Խ���ֵΪ��"<<Value(bTree,  bTNode)<<endl;
	cout<<"�޸Ĳ��Խ���ֵΪX\n";
	Assign(bTree, bTNode, 'X');
	cout<<"���Խ���ֵΪ��"<<Value(bTree,  bTNode)<<endl;
	cout<<"���Խ���˫��ֵΪ��"<<Value(bTree, Parent(bTree,  bTNode))<<endl;
	cout<<"���Խ�������ֵΪ��"<<Value(bTree, LeftChild(bTree,  bTNode))<<endl;
	cout<<"���Խ����Һ���ֵΪ��"<<Value(bTree, RightChild(bTree,  bTNode))<<endl;
	cout<<"���Խ������ֵ�ֵΪ��"<<Value(bTree, LeftSibling(bTree,  bTNode))<<endl;
	cout<<"���Խ������ֵ�ֵΪ��"<<Value(bTree, RightSibling(bTree,  bTNode))<<endl<<endl;
	
	cout<<"���������\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// ���Բ����ɾ��
	preOrder = "QYZ";
	inOrder = "ZYQ";
	BiTree insertBTree;
	CreateBiTree(insertBTree, preOrder, inOrder);
	cout<<"\n���������ɹ�\n\n";
	
	cout<<"���������������\n";
	InOrderTraverse(insertBTree, 0);
	cout<<endl;
	
	bTNode = bTree->lchild->rchild->lchild;
	InsertChild(bTree, bTNode, 0, insertBTree);
	
	cout<<"�����������������\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	DeleteChild(bTree, bTNode, 0);
	cout<<"ɾ���������������\n";
	InOrderTraverse(bTree, 0);
	cout<<endl;
	
	// ������ 
	DestoryBiTree(bTree);
}

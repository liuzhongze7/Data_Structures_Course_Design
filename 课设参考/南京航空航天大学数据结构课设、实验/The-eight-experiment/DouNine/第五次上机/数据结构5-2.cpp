/* 
ʵ�ֶ��������������򡢺���������õݹ�ͷǵݹ鷽����ʵ�ֲ�α�����
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


// ����������ݹ�
void preOrderTraverse(BiTree bTree) {
	if (bTree) {
		cout<<bTree->data;
		preOrderTraverse(bTree->lchild);
		preOrderTraverse(bTree->rchild);
	} 
}


// ����������ǵݹ�
void preOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"����Ϊ�գ�";
		return;
	}
	cout<<"�ǵݹ����������";
	stack<BiTree> s;
	s.push(bTree); 
	BiTree temp; 
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		cout<<temp->data;
		if (temp->rchild) s.push(temp->rchild);
		if (temp->lchild) s.push(temp->lchild);
	}
	cout<<endl;
}


// ����������ݹ� 
void inOrderTraverse(BiTree bTree) {
	if (bTree) {
		inOrderTraverse(bTree->lchild);
		cout<<bTree->data;
		inOrderTraverse(bTree->rchild);
	} 
}


// ����������ǵݹ飬�����㷨 
void inOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"����Ϊ�գ�";
		return; 
	} 
	
	cout<<"�ǵݹ����������";
	stack<BTNode> s;
	s.push(*bTree);
	BTNode temp, dataBTree;
	dataBTree.lchild = dataBTree.rchild = NULL;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
			
		if (!temp.lchild && !temp.rchild) cout<<temp.data;
		else {
			dataBTree.data = temp.data;
			
			if (temp.rchild) s.push(*temp.rchild);
			s.push(dataBTree);
			if (temp.lchild) s.push(*temp.lchild);
		}
	}
	cout<<endl;
}


//// ����������ǵݹ飬�ú���ǵݹ�ķ���ʧ�� 
//void inOrderTraverseOther(BiTree bTree) {
//	if (!bTree) {
//		cout<<"����Ϊ�գ�";
//		return; 
//	} 
//	
//	cout<<"�ǵݹ����������";
//	stack<BiTree> s;
//	s.push(bTree);
//	BiTree temp = NULL, top = NULL;
//	while (!s.empty()) {
//		stack<BiTree> t(s);
//		cout<<"\nstack:";
//		while (!t.empty()) {
//			cout<<t.top()->data;
//			t.pop();
//		}
//		cout<<endl;
//		
//		top = s.top();
//		s.pop();		
//			
//		if ((!top->lchild && !top->rchild) || top->lchild == temp) {
//			cout<<top->data;
//			temp = top;
//		}
//		else {			
//			if (top->rchild) s.push(top->rchild);
//			s.push(top);
//			if (top->lchild) s.push(top->lchild);
//		}
//	}
//	cout<<endl;
//}


// ����������ݹ� 
void postOrderTraverse(BiTree bTree) {
	if(bTree) {
		postOrderTraverse(bTree->lchild);
		postOrderTraverse(bTree->rchild);
		cout<<bTree->data;
	} 
}


//// ����������ǵݹ飬�����㷨 
//void postOrderTraverseOther(BiTree bTree) {
//	if (!bTree) {
//		cout<<"����Ϊ�գ�";
//		return; 
//	}
//	
//	cout<<"�ǵݹ���������";
//	stack<BTNode> s;
//	s.push(*bTree);
//	BTNode temp, dataBTree;
//	dataBTree.lchild = dataBTree.rchild = NULL;
//	while (!s.empty()) {
//		temp = s.top();
//		s.pop();
//			
//		if (!temp.lchild && !temp.rchild) cout<<temp.data;
//		else {
//			dataBTree.data = temp.data;
//			
//			s.push(dataBTree);
//			if (temp.rchild) s.push(*temp.rchild);
//			if (temp.lchild) s.push(*temp.lchild);
//		}
//	}
//	cout<<endl;
//}


// ����������ǵݹ�
void postOrderTraverseOther(BiTree bTree) {
	if (!bTree) {
		cout<<"����Ϊ�գ�";
		return; 
	}
	
	cout<<"�ǵݹ���������";
	stack<BiTree> s;
	s.push(bTree);
	BiTree temp = NULL, top = NULL;	// ����ָ��ջ����topָ�룬��ָ����һ������ڵ��tempָ�� 
	while (!s.empty()) {
		top = s.top();		//  ��ȡջ����BiTreeָ�� 
		
		// �� ��ָ��ָ�����һ��Ҷ�ӽڵ� ���� �ýڵ������Һ����Ѿ����
		if ((!top->lchild && !top->rchild) || top->rchild == temp || top->lchild == temp) {
			cout<<top->data;		// ����ýڵ��е�ֵ 
			temp = top;				// ������ڵ�ָ��ָ��ýڵ� 
			s.pop();				// ������Ԫ�� 
		}
		else {
			if (top->rchild) s.push(top->rchild);
			if (top->lchild) s.push(top->lchild);
		}
	}
	cout<<endl;
}


// ��α���
void levelOrderTraverse(BiTree bTree) {
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
	cout<<"����������";
}


int main() {

	string preOrder = "ABDEGIHKLCFJ";
	string inOrder = "DBIGEKHLACFJ";
		
	BiTree bTree;
	CreateBiTree(bTree, preOrder, inOrder);
	cout<<"\n�����ɹ�\n\n";
	
	// �ݹ�ʵ�� 
	cout<<"���������";
	preOrderTraverse(bTree);
	cout<<endl;
	
	cout<<"���������";
	inOrderTraverse(bTree);
	cout<<endl;
	
	cout<<"���������";
	postOrderTraverse(bTree);
	cout<<endl<<endl;
	
	// �ǵݹ�ʵ�� 
	preOrderTraverseOther(bTree);
	inOrderTraverseOther(bTree);
	postOrderTraverseOther(bTree);
	cout<<endl;
	
	// ��α���
	levelOrderTraverse(bTree);
	cout<<endl;
	
	// ������ 
	DestoryBiTree(bTree);
} 

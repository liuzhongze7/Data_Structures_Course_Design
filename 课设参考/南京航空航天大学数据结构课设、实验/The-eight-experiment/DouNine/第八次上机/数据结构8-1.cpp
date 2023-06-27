/*
ʵ�ֶ����������Ĳ����ɾ����
10
100 24 3 45 12  53 37 78 61 90
*/
#include<iostream>
#include<cstdlib>
#include<queue>

using namespace std;

typedef struct BTNode {
	int data;
	BTNode *lchild, *rchild;
}BTNode, *BiTree;


// ������
void InsertBTree(BiTree &bTree, int data) {
	cout<<"������ֵ��"<<data<<endl;
	BTNode *p = bTree, *temp;
	while (1) {
		if (data < p->data) {
			if (p->lchild) p = p->lchild;
			else {
				temp = (BTNode*)malloc(sizeof(BTNode));
				temp->data = data;
				temp->lchild = temp->rchild = NULL;
				p->lchild = temp;
				break; 
			}
		} 
		else if (data > p->data) {
			if (p->rchild) p = p->rchild;
			else {
				temp = (BTNode*)malloc(sizeof(BTNode));
				temp->data = data;
				temp->lchild = temp->rchild = NULL;
				p->rchild = temp;
				break;
			}
		} 
		else break;
	}
	cout<<"����ɹ�\n";
}


// ɾ�����
int DeleteBTree(BiTree &bTree, int data) {
	BTNode *cur, *pre;
	cur = pre = bTree;
	while (1) {
		// �����ǰָ��ָ��ս�㣬��ôû�ҵ����ֵ
		if (!cur) break;
		// ����ҵ������ֵ
		if (cur->data == data) {
			// ���ɾȥ�Ľ��û�к��� 
			if (!cur->lchild && !cur->rchild) {
				// ���ɾ�ĵ��Ǹ� 
				if (bTree->data == data) bTree = NULL;
				
				if (pre->lchild == cur) pre->lchild = NULL;
				else pre->rchild = NULL;
			}
			// ���ɾȥ�Ľ������������ 
			else if (cur->lchild && cur->rchild) {
				// �ҵ��Ըý������Ϊ���ڵ�������е����ֵ����С�ڸ�ֵ�����е����ֵ�� 
				BTNode *cur2, *pre2;
				pre2 = cur;		// per2�˴�һ��Ҫ����cur������cur->lchild�������Deleteʱ�ܹؼ� 
				cur2 = cur->lchild;
				while (cur2->rchild) {
					pre2 = cur2;
					cur2 = pre2->rchild;
				}
				// pre2���ܵ���cur2����Ȼ�������Ҫɾ�ĵ�Ϊ���ڵ�����ʱ���Ͳ��ܽ���һ�����ĸú���ָ����ΪNULL 
				int tempData = DeleteBTree(pre2, cur2->data);	
				
				// ���ҵ������ֵ���ȡ��Ҫɾ������λ�� 
				BTNode *temp = (BTNode*)malloc(sizeof(BTNode));
				temp->data = tempData;
				temp->lchild = cur->lchild;
				temp->rchild = cur->rchild;
				
				// ���������Ҫɾ���Ľ���Ǹ�
				if (bTree->data == data) bTree = temp;
				if (pre->lchild == cur) pre->lchild = temp;
				else pre->rchild = temp;
			}
			// ���һ��������ý��ֻ��һ������ 
			else {
				// �ҵ���Ϊ�յĺ��� 
				BTNode *temp;
				if (cur->lchild) temp = cur->lchild;
				else if (cur->rchild) temp = cur->rchild;
				// ���ú���ȡ���������λ�� 
				// Ҫɾ���Ľ��Ϊ��ʱ
				if (bTree->data == data) {
					bTree = temp;
				}
				if (pre->lchild == cur) pre->lchild = temp;
				else pre->rchild = temp;
			}
			break;
		}
		else if (cur->data > data) {
			pre = cur;
			cur = cur->lchild;
		} 
		else if (cur->data < data) {
			pre = cur;
			cur = cur->rchild;
		}
	}
	int temp = cur->data;
	free(cur);
	cout<<"ɾ���ɹ���ɾ����ֵΪ��"<<temp<<endl; 
	return temp;
}
 

// ������������ 
void CreateBTree(BiTree &bTree) {
	cout<<"������Ҫ�½������ĸ�����\n";
	int n = 0;
	cin>>n;
	cout<<"����������ÿ������\n";
	bTree = (BTNode*)malloc(sizeof(BTNode));
	cin>>bTree->data;
	bTree->lchild = NULL;
	bTree->rchild = NULL;
	int data = 0;
	for (int i=0; i<n-1; i++) {
		cin>>data;
		InsertBTree(bTree, data);
	}
}


// ���ٶ��������� 
void DestoryBTree(BiTree &bTree) {
	if (bTree) {
		DestoryBTree(bTree->lchild);
		DestoryBTree(bTree->rchild);
		free(bTree);
	}
}


// ���������������������˳���������
void InOrderBTree(BiTree bTree) {
	if (bTree) {
		InOrderBTree(bTree->lchild);
		cout<<bTree->data<<"  ";
		InOrderBTree(bTree->rchild);
	}
}


// ��α������ǵݹ� 
void LevelOrderTraverse(BiTree bTree) {
	if (!bTree) {
		cout<<"����Ϊ�գ�";
		return; 
	}
	
	cout<<"\n��α�����";
	queue<BiTree> q;
	q.push(bTree);
	BiTree temp;
	while (!q.empty()) {
		temp = q.front();
		cout<<temp->data<<" ";
		if (temp->lchild) q.push(temp->lchild);
		if (temp->rchild) q.push(temp->rchild);
		q.pop();
	}
	cout<<endl;
} 


int main() {
	BiTree bTree;
	CreateBTree(bTree);
	cout<<"\n���������˳�������\n";
	InOrderBTree(bTree);
	LevelOrderTraverse(bTree);
	cout<<"\n������Ҫɾ�������ݣ�\n";
	int data;
	cin>>data;
	DeleteBTree(bTree, data);
	//if (bTree) cout<<"ɾ��ʧ��"<<bTree<<"\n";
	cout<<"\n���������˳�������\n";
	InOrderBTree(bTree);
	LevelOrderTraverse(bTree);
	DestoryBTree(bTree);
}




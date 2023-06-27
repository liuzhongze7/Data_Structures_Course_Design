/*
��д���������㷨
6 8

0 1
0 2
0 3
2 1
2 4
3 4
5 3
5 4
*/
#include<iostream>
#include<stdlib.h>
#include<vector>

using namespace std;

typedef struct VNode {
	int data;
	VNode* next;
}VNode, *VList;

// ����ͼ����ӱ��ʾ�� 
typedef struct {
	int vexnum, arcnum;
	VList* vexList;
}ALGraph;

void CreateALGraph(ALGraph &G) {
	cout<<"�����붥�����ͱ���:\n";
	cin>>G.vexnum>>G.arcnum;
	
	// ��ʼ����ӱ� 
	G.vexList = (VList*)malloc(sizeof(VList) * G.vexnum);
	for (int i=0; i<G.vexnum; i++) {
		VNode* temp = (VNode*)malloc(sizeof(VNode));
		temp->data = i;
		temp->next = NULL;
		G.vexList[i] = temp;
	}
	
	cout<<"��ÿ���ߵ�ʼ�㡢�յ�(0~n-1):\n";
	for (int i=0; i<G.arcnum; i++) {
		int x = 0, y = 0;
		VNode* temp = (VNode*)malloc(sizeof(VNode));
		cin>>x>>y;
		temp->data = y;
		temp->next = NULL;
		temp->next = G.vexList[x]->next;
		G.vexList[x]->next = temp;
	}
}

void DestroyALGraph(ALGraph &G) {
	for (int i=0; i<G.vexnum; i++) {
		VNode *p = G.vexList[i], *temp;
		while (p) {
			temp = p;
			p = p->next;
			free(temp);
		}
	}
	cout<<"\nDestroy Success!\n";
}

void TraverseALGraph(ALGraph G) {
	cout<<"��ӱ�ı������£�\n";
	for (int i=0; i<G.vexnum; i++) {
		VNode * p = G.vexList[i];
		while (p) {
			cout<<p->data<<" ";
			p = p->next;
		}
		cout<<endl;
	}
}

int main() {
	ALGraph G;
	CreateALGraph(G);
	TraverseALGraph(G);
	
	int inCount[G.vexnum];
	for (int i=0; i<G.vexnum; i++) {
		inCount[i] = 0;
	}
	for (int i=0; i<G.vexnum; i++) {
		VNode * p = G.vexList[i]->next;
		while (p) {
			inCount[p->data]++;
			p = p->next;
		}
	} 
	
//	for (int i=0; i<G.vexnum; i++) {
//		cout<<inCount[i]<<"--";
//	}
//	cout<<endl;
	
	vector<int> res;
	while (1) {
		bool noZero = true;
		for (int i=0; i<G.vexnum; i++) {
			if (inCount[i] == 0) {
				//cout<<"===="<<i<<endl;
				inCount[i]--;
				noZero = false;
				res.push_back(i);
				VNode * p = G.vexList[i]->next;
				while (p) {
					inCount[p->data]--;
					p = p->next;
				}
			}
		}
		if (noZero) break;
	}
	if (res.size() < G.vexnum) {
		cout<<"�л���\n";
		getchar();
		return 0;
	}
	
	cout<<"�������������£�\n";
	for (int i=0; i<G.vexnum; i++) {
		cout<<res[i]<<"--";
	}
	
	DestroyALGraph(G);
	return 0;
} 

/*
���ʵ����P156  ADT Graph ��������13�������ڽӾ���洢�ṹʵ�֣�
1.����ͼ
2.������
3.����ͼ
4.������
��ȷ��ͼ�����ͣ�
3
������ͼ�Ķ������ͱ�����5 7
����������������ֵ(�ַ���)��a b c d e
���������������ͼ�и��ߵ��������ڵ㣺
0 1
0 3
0 4
1 2
1 3
2 4
3 4

������ͼ�Ķ������ͱ�����8 9
0 1
0 2
1 3
1 4
3 7
4 7
2 5
2 6
5 6

����ͨͼ 
������ͼ�Ķ������ͱ�����8 8
0 1
1 3
1 4
3 7
4 7
2 5
2 6
5 6
*/
#include<iostream>
#include<stdlib.h>
#include<stack>
#include<queue>
using namespace std;


// ͼ������{����ͼ��������(��Ȩͼ)������ͼ�� ������}
typedef enum {DG, DN, UDG, UDN} GraphKind;	


// ��(��ʹ��) 
typedef struct ArcCell {
	int adj;	// ������Ȩͼ����1��0��ʾ������񣻶��ڴ�Ȩͼ����ΪȨֵ�� 
	int *info;	// �ñ߶�Ӧ����Ϣ 
}ArcCell, AdjMatrix[20][20];


// ͼ 
typedef struct {
	char *vexs;			// ����ֵ������ 
	int vexNum, arcNum;  		// ͼ�Ķ������ͱ���
	int **arcs;	// �ߵľ��� 
	GraphKind kind;				// ͼ������ 
}MGraph;


// ��������ͼ 
void CreateDG(MGraph &G) {
	cout<<"���������������ͼ�и��ߵ�ʼ�㡢�յ㣺\n";
	
	int x, y;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y;
		if (x == y) {
			cout<<"���ܳ��ֻ���\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = 1;
	}
}


// ����������
void CreateDN(MGraph &G) {
	cout<<"������������������и��ߵ�ʼ�㡢�յ��Ȩֵ��\n";
	
	int x, y, weight;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y>>weight;
		if (x == y) {
			cout<<"���ܳ��ֻ���\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		}
		if (weight == 0) {
			cout<<"Ȩ�ز���Ϊ0��\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = weight;
	}
}
 

// ��������ͼ 
void CreateUDG(MGraph &G) {
	cout<<"���������������ͼ�и��ߵ��������ڵ㣺\n";
	
	int x, y;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y;
		if (x == y) {
			cout<<"���ܳ��ֻ���\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = 1;
		G.arcs[y][x] = 1;
	}
}


// ����������
void CreateUDN(MGraph &G) {
	cout<<"������������������и��ߵ��������ڵ��Ȩֵ��\n";
	
	int x, y, weight;
	for (int i=0; i<G.arcNum; i++) {
		cin>>x>>y>>weight;
		if (x == y) {
			cout<<"���ܳ��ֻ���\n";
			i--;
			continue;
		} 
		if (x == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		} 
		if (y == G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		}
		if (weight == 0) {
			cout<<"Ȩ�ز���Ϊ0��\n";
			i--;
			continue;
		} 
		G.arcs[x][y] = weight;
		G.arcs[y][x] = weight;
	}
}


// ����ͼG
void CreateGraph(MGraph &G) {
	int choose;
	cout<<"1.����ͼ\n2.������\n3.����ͼ\n4.������\n��ȷ��ͼ�����ͣ�\n";
	cin>>choose;
	
	cout<<"������ͼ�Ķ������ͱ�����";
	cin>>G.vexNum>>G.arcNum;
	
	// ��̬��ʼ��ͼ����ÿһ���ߵ�ֵ��Ϊ0
	G.arcs = (int**)malloc(sizeof(int*) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) {
		G.arcs[i] = (int*)malloc(sizeof(int) * G.vexNum);
		for (int j=0; j<G.vexNum; j++) {
			G.arcs[i][j] = 0;		// ��0��ʾ�������߲����� 
		}
	}
	
	// ��ʼ������ֵ 
	G.vexs = (char*)malloc(sizeof(char) * G.vexNum);
	cout<<"����������������ֵ(�ַ���)��"; 
	for (int i=0; i<G.vexNum; i++) {
		cin>>G.vexs[i];
	}
	
	switch(choose) {
		case 1: {
			G.kind = DG;
			CreateDG(G);
			break;
		}
		case 2: {
			G.kind = DN;
			CreateDN(G);
			break;
		}
		case 3: {
			G.kind = UDG;
			CreateUDG(G);
			break;
		}
		case 4: {
			G.kind = UDN;
			CreateUDN(G);
			break;
		}
	}
}


// ����ͼ
void DestroyGraph(MGraph &G) {
	cout<<"\n����ͼ\n";
	free(G.vexs);
	for (int i=0; i<G.vexNum; i++) {
		free(G.arcs[i]);
	}
	free(G.arcs);
	G.vexNum = G.arcNum = 0;
} 


// ���ض���λ��
int LocateVex(MGraph &G, char value) {
	for (int i=0; i<G.vexNum; i++) {
		if (G.vexs[i] == value) {
			return i;
		}
	}
	return -1; 
}


// ���ض����ֵ
char GetVex(MGraph &G, int v) {
	return G.vexs[v];
} 
 

// ���ö����ֵ
void PutVex(MGraph &G, int v, char value) {
	G.vexs[v] = value;
}
 

// ����v�ĵ�һ���ڽӶ���
int FisrtAdjVex(MGraph G, int v) {
	for (int j=0; j<G.vexNum; j++) {
		if (!G.arcs[v][j]) return j;
	}
	return -1;
}


// ����v�����Ӷ���w�����һ������
int NextAdjVex(MGraph G, int v, int w) {
	// �ӵ�v�е�w��λ�ÿ�ʼ��������һ������ 
	for (int j=w; j<G.vexNum; j++) {
		if (!G.arcs[v][j]) return j;
	}
	return -1;
}


// ��������
void InsertVex(MGraph &G, char value) {
	
	G.vexNum++;
	
	// ��������������ռ䣬�������¶���ֵ 
	G.vexs = (char*)realloc(G.vexs, sizeof(char) * G.vexNum);
	G.vexs[G.vexNum-1] = value;
	
	// ��������ͼ�ռ䣬���±ߵ�ֵ��Ϊ0 
	G.arcs = (int**)realloc(G.arcs, sizeof(int*) * G.vexNum);
	//cout<<"ok\n";
	for (int i=0; i<G.vexNum-1; i++) {
		//cout<<i<<endl;
		G.arcs[i] = (int*)realloc(G.arcs[i], sizeof(int) * G.vexNum);
		//cout<<"ok   "<<G.vexNum-1<<"\n";
		G.arcs[i][G.vexNum-1] = 0;
		//cout<<"ok\n";
	}
	//cout<<"ok\n";
	G.arcs[G.vexNum-1] = (int*)malloc(sizeof(int) * G.vexNum);
	for (int j=0; j<G.vexNum; j++) {
		//cout<<"  "<<j<<endl;
		G.arcs[G.vexNum-1][j] = 0;
	}
	
	cout<<"\n��������ɹ�!\n";
}
 
 
// ɾ������
void DeleteVex(MGraph &G, char value) {
	
	int v = LocateVex(G, value);
	if (v == -1) {
		cout<<"������";
		return;
	}
	// �ڶ���������ɾȥ��ֵ�����ڱ�ͼ��ɾȥ���� 
	for (int i=v+1; i<G.vexNum; i++) {
		G.vexs[i-1] = G.vexs[i];
		G.arcs[i-1] = G.arcs[i];
	}
	
	// �ڱ�ͼ��ɾȥ���� 
	for (int i=0; i<G.vexNum-1; i++) {
		for (int j=v+1; j<G.vexNum; j++) {
			G.arcs[i][j-1] = G.arcs[i][j];
		}
	}
	
	G.vexNum--;
	
	// �������붥�������ռ䣬�������¶���ֵ 
	G.vexs = (char*)realloc(G.vexs, sizeof(char) * G.vexNum);
	
	// ��������ͼ�ռ䣬���±ߵ�ֵ��Ϊ0 
	G.arcs = (int**)realloc(G.arcs, sizeof(int*) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) {
		G.arcs[i] = (int*)realloc(G.arcs[i], sizeof(int) * G.vexNum);
	}
	
	cout<<"\nɾ������ɹ�!\n";
}


// ������ 
void InsertArc(MGraph &G, char valueV, char valueW) {
	int v = LocateVex(G, valueV), w = LocateVex(G, valueW);
	if (G.kind == DG) {
		G.arcs[v][w] = 1;
	} 
	else if (G.kind == DN) {
		cout<<"�����������ߵ�Ȩ�أ�";
		int weight = 0;
		cin>>weight;
		G.arcs[v][w] = weight;
	}
	else if (G.kind == UDG) {
		G.arcs[v][w] = 1;
		G.arcs[w][v] = 1;
	}
	else if (G.kind == UDN) {
		cout<<"�����������ߵ�Ȩ�أ�";
		int weight = 0;
		cin>>weight;
		G.arcs[v][w] = weight;
		G.arcs[w][v] = weight;
	}
	cout<<"\n�����߳ɹ�!\n";
}


// ɾ����
void DeleteArc(MGraph &G, char valueV, char valueW) {
	int v = LocateVex(G, valueV), w = LocateVex(G, valueW);
	if (G.kind == DG || G.kind == DN) {
		G.arcs[v][w] = 0;
	}
	else if (G.kind == UDG || G.kind == UDN) {
		G.arcs[v][w] = 0;
		G.arcs[w][v] = 0;
	}
	cout<<"\nɾ���߳ɹ�!\n";
}


// ������ȱ���
void DFSTraverse(MGraph G) {
	bool *vexsCheck = (bool*)malloc(sizeof(bool) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) vexsCheck[i] = false;
	
	cout<<"\n������ȱ�����";
	stack<int> s;
	for (int i=0; i<G.vexNum; i++) {
		if (!vexsCheck[i]) {
			cout<<"  "<<GetVex(G, i);
			s.push(i);
			vexsCheck[i] = true;
			int top;
			while (!s.empty()) {
				top = s.top();
				// ����õ�δ�߹������ 
				if (!vexsCheck[top]) cout<<"--"<<GetVex(G, top);	
				vexsCheck[top] = true;
				int j;		
				// �����ý�������ڽӽڵ� 
				for (j=0; j<G.vexNum; j++) {
					if (j != top && G.arcs[top][j] && !vexsCheck[j]) {
						s.push(j);
						break;
					}
				}
				// ����õ������ڽӵ㶼�߹����򵯳��õ� 
				if (j == G.vexNum) s.pop();
			}
		}
	}
	free(vexsCheck);
}


//// ��λ�ú����߹�������λ��(��λ�ô�0�����) 
//typedef struct {
//	int v;
//	int col;
//}vexNode;

//// ������ȱ�������·�� 
//void DFSTraverse(MGraph G) {
//	int *vexsCheck = (int*)malloc(sizeof(int) * (G.vexNum+1));
//	for (int i=0; i<G.vexNum+1; i++) vexsCheck[i] = 0;
//	
//	vexNode start;
//	stack<vexNode> s;
//	for (int i=0; i<G.vexNum; i++) {
//		cout<<"ok\n"; 
//		if (!vexsCheck[i]) {
//			start.col = 0;
//			start.v = i;
//			s.push(start);
//			vexsCheck[start.v] = 1;
//			vexsCheck[G.vexNum]++;
//			vexNode top, temp;
//			while (!s.empty()) {
//				top = s.top();
//				vexsCheck[top.v] = 0;
//				// ������Ԫ���Ѿ��߹� 
//				if (vexsCheck[G.vexNum] == G.vexNum) {
//					// ���ջ 
//					stack<vexNode> tempS(s);
//					cout<<"stack: ";
//					while (!tempS.empty()) {
//						temp = tempS.top();
//						tempS.pop();
//						cout<<GetVex(G, temp.v)<<"<--";
//					}
//					cout<<endl;
//					
//					s.pop();
//					vexsCheck[G.vexNum]--; 
//					continue;
//				}
//				
//				s.pop();
//				vexsCheck[G.vexNum]--;
//				for (top.col+=1; top.col<G.vexNum; top.col++) {
//					if (top.col != top.v && G.arcs[top.v][top.col] && !vexsCheck[top.col]) {
//						// cout<<G.arcs[top.v][top.col]<<" "<<top.col<<endl;
//						temp.v = top.col;
//						temp.col = 0;
//						s.push(top);
//						vexsCheck[top.v] = 1;
//						s.push(temp);
//						vexsCheck[temp.v] = 1;
//						vexsCheck[G.vexNum] += 2; 
//						
//						break;
//					}
//				}
//			}
//		}
//	}
//	free(vexsCheck);
//}


// ������ȱ���
void BFSTraverse(MGraph G) {
	bool *vexsCheck = (bool*)malloc(sizeof(bool) * G.vexNum);
	for (int i=0; i<G.vexNum; i++) vexsCheck[i] = false;
	
	cout<<"\n������ȱ�����";
	queue<int> q;
	// forѭ��������δ�����ĵ㣬��Ϊ���ж����ͨ��֧����� 
	for (int i=0; i<G.vexNum; i++) {
		if (!vexsCheck[i]) {
			q.push(i);
			vexsCheck[i] = true;
			int front;
			while (!q.empty()) {
				front = q.front();
				cout<<GetVex(G, front)<<"--";
				q.pop();
				for (int j=0; j<G.vexNum; j++) {
					if (front != j && !vexsCheck[j]) {
						q.push(j);
						vexsCheck[j] = true;
					}
				}
			}
		}
	}
}


// ��ͨ���� 
void Traverse(MGraph G) {
	cout<<"\n���������ı������£�\n";
	for (int i=0; i<G.vexNum; i++) {
		cout<<G.vexs[i]<<" ";
	}
	cout<<"\nͼ�ľ���������£�\n";
	for (int i=0; i<G.vexNum; i++) {
		for (int j=0; j<G.vexNum; j++) {
			cout<<G.arcs[i][j]<<" ";
		}
		cout<<endl;
	}
} 


int main() {
	MGraph G;
	CreateGraph(G);
	Traverse(G);
	
	cout<<"������Ҫ�����Ķ����ֵ��";
	char ch;
	cin>>ch;
	InsertVex(G, ch);
	Traverse(G);
	cout<<"������Ҫɾ���Ķ��㣺";
	cin>>ch;
	DeleteVex(G, ch);
	Traverse(G);
	
	cout<<"������Ҫ����ıߵ���������ֵ��";
	char chV, chW;
	cin>>chV>>chW;
	InsertArc(G, chV, chW);
	cout<<"������Ҫɾ���ıߵ���������ֵ��";
	cin>>chV>>chW;
	DeleteArc(G, chV, chW);
	Traverse(G);
	
	DFSTraverse(G);
	BFSTraverse(G);
	DestroyGraph(G); 
}






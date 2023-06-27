/*
�ؼ�·��
6 8

1 2 3
1 3 2
2 4 2
2 5 3
3 4 4
3 6 3
4 6 2
5 6 1
*/
#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;


// ����ͼ 
typedef struct {
	char *vexs;				// ����ֵ������ 
	int vexNum, arcNum;  	// ͼ�Ķ������ͱ���
	int **arcs;				// �ߵľ��� 
}MGraph;


// ·��
typedef struct {
	int from, to;
	int weight;
}Arc; 

 
// ����ͼ 
void CreateMGraph(MGraph &G) {
	cout<<"�����붥�����ͱ���:\n";
	cin>>G.vexNum>>G.arcNum;
	
	// ��̬��ʼ��ͼ����ÿһ���ߵ�ֵ��Ϊ0
	G.arcs = (int**)malloc(sizeof(int*) * (G.vexNum+1));
	for (int i=0; i<=G.vexNum; i++) {
		G.arcs[i] = (int*)malloc(sizeof(int) * (G.vexNum+1));
		for (int j=0; j<=G.vexNum; j++) {
			G.arcs[i][j] = 0;		// ��0��ʾ�������߲����� 
		}
	}

	cout<<"������������������и���(1-n)��ʼ�㡢�յ��Ȩֵ��\n";
	
	int x, y, weight;
	for (int i=1; i<=G.arcNum; i++) {
		cin>>x>>y>>weight;
		if (x == y) {
			cout<<"���ܳ��ֻ���\n";
			i--;
			continue;
		} 
		if (x > G.vexNum) {
			cout<<"�����ڸõ㣡\n";
			i--;
			continue;
		} 
		if (y > G.vexNum) {
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


// ����ͼ
void DestroyGraph(MGraph &G) {
	cout<<"\n����ͼ\n";
	for (int i=0; i<=G.vexNum; i++) {
		free(G.arcs[i]);
	}
	free(G.arcs);
	G.vexNum = G.arcNum = 0;
} 


// ����ͼ 
void Traverse(MGraph G) {
	cout<<"\nͼ�ľ���������£�\n";
	for (int i=1; i<=G.vexNum; i++) {
		for (int j=1; j<=G.vexNum; j++) {
			cout<<G.arcs[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
} 


// �������� 
vector<int> TopoSort(MGraph &G) {
	int *inCount = (int*)malloc(sizeof(int) * (G.vexNum+1));	// ����һ����¼ÿ�������ֵ������ 
	// ��ʼ�����ֵ���� 
	for (int i=0; i<=G.vexNum; i++) {
		inCount[i] = 0;
	}	
	// ��ÿ�������� 
	for (int i=1; i<=G.vexNum; i++) {
		for (int j=1; j<=G.vexNum; j++) {
			// ���i��jλ�ò�Ϊ�㣬��˵��i->j��j�����ȼ�һ 
			if (G.arcs[i][j]) inCount[j]++; 
		}
	}
	
	vector<int> topoRes;		// ����������·��
	bool hasZero = true; 
	while (hasZero) {
		hasZero = false;
		for (int i=1; i<=G.vexNum; i++) {
			// ����������Ϊ0�Ķ��� 
			if (!inCount[i]) {
				hasZero = true;
				inCount[i]--;
				topoRes.push_back(i);
				// ���Ըõ�Ϊʼ��ĵ����ȶ���һ 
				for (int j=1; j<=G.vexNum; j++) {
					if (G.arcs[i][j]) inCount[j]--;
				}
			}
		}
	}
	
	free(inCount);
	
	if (topoRes.size() < G.vexNum) {
		cout<<"�л���\n";
		getchar();
		exit(0);
	}
	
	return topoRes;
}


int main() {
	MGraph G;
	CreateMGraph(G);
	Traverse(G);
	
	
	vector<int> topoRes = TopoSort(G);
	cout<<"�������������£�\n";
	for (int i=0; i<topoRes.size(); i++) {
		cout<<topoRes[i]<<"---";
	}
	cout<<endl<<endl;


	int *ve = (int*)malloc(sizeof(int) * (G.vexNum+1));		// ÿ��������ʱ�� 
	int *vl = (int*)malloc(sizeof(int) * (G.vexNum+1));		// ÿ��������ʱ�� 
	
	// ��������翪��ʱ�� 
	for (int n=0; n<topoRes.size(); n++) {
		int j = topoRes[n];
		// ȡ����������jΪ�յ�ĵ�i�У�i�������ʱ�����i->j��ʱ���У������ֵ
		int max = 0;  
		for (int i=1; i<=G.vexNum; i++) {
			if (G.arcs[i][j]) {
				if (ve[i] + G.arcs[i][j] > max) max = ve[i] + G.arcs[i][j];
			}
		}
		ve[j] = max;
	}
	cout<<"ÿ��������翪��ʱ�����£�\n";
	for (int i=1; i<=G.vexNum; i++) {
		cout<<i<<"---"<<ve[i]<<"  ";
	} 
	cout<<endl<<endl;
	
	// �����������ʱ�� 
	int last = topoRes[G.vexNum-1];	// ���һ�����̵㣬���յ� 
	vl[last] = ve[last];	// ���յ��������ʱ����Ϊ���翪��ʱ�� 
	for (int n=G.vexNum-2; n>=0; n--) {
		int i = topoRes[n];
		// ȡ����������iΪʼ��ĵ�j�У�j�������ʱ���ȥi->j��ʱ���У�����Сֵ 
		int min = INT_MAX;  
		for (int j=1; j<=G.vexNum; j++) { 
			if (G.arcs[i][j] && (vl[j] - G.arcs[i][j] < min)) {
				min = vl[j] - G.arcs[i][j];
			}
		}
		vl[i] = min;
	}
	cout<<"ÿ�����������ʱ�����£�\n";
	for (int i=1; i<=G.vexNum; i++) {
		cout<<i<<"---"<<vl[i]<<"  ";
	} 
	cout<<endl<<endl;
	
	
	// ��ؼ�·�� 
	vector<Arc> importPath;
	for (int n=0; n<topoRes.size(); n++) {
		int i = topoRes[n];
		for (int j=1; j<=G.vexNum; j++) {
			if (G.arcs[i][j] && (vl[j]-G.arcs[i][j] == ve[i])) {
				Arc arc;
				arc.from = i;
				arc.to = j;
				arc.weight = G.arcs[i][j];
				importPath.push_back(arc);
			}
		}
	}
	cout<<"�ؼ�·�����£�\n";
	for (int i=0; i<importPath.size(); i++) {
		cout<<importPath[i].from<<"-->"<<importPath[i].to<<"  "<<importPath[i].weight<<endl;
	}
	
	free(ve);
	free(vl);
	
	DestroyGraph(G);
	return 0; 
}








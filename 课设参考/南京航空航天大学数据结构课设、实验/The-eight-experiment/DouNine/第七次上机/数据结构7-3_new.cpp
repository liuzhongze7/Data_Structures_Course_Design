#include<cstdio>
#include<algorithm>

using namespace std;

typedef struct {
	int from, to;
	int weight;
}Arc;

Arc arcs[100005];
int points[1005];		// ���鼯 

// �Ұְ� 
int find(int n) {
	return n == points[n] ? n : points[n] = find(points[n]);
}

bool cmp(Arc a, Arc b) {
	return a.weight < b.weight;
}

int main() {
	long long n=0, m=0;
	scanf("%d%d", &n, &m);
	
	for (int i=0; i<n; i++) points[i] = i;
	
	for (int i=0; i<m; i++) {
		scanf("%d%d%d", &arcs[i].from, &arcs[i].to, &arcs[i].weight);	// ��cin��scanf�� 
		arcs[i].from--;
		arcs[i].to--;
	}
	
	// ��m���ߣ����п�������
	sort(arcs, arcs+m, cmp);
	
	int sum = 0;
	for (int i=0; i<m; i++) {
		int x = find(arcs[i].from);
		int y = find(arcs[i].to);
		if (x != y) {
			points[x] = y;
			sum += arcs[i].weight;
		}
	}
	
	printf("%d", sum);
	return 0;
}


/*ĳѧУ��N��ѧ�����γ�M�����ֲ���ÿ�����ֲ����ѧ���������Ƶ���Ȥ���ã��γ�һ������Ȧ��һ��ѧ������ͬʱ�������ɸ���ͬ�ľ��ֲ������ݡ��ҵ����ѵ�����Ҳ���ҵ����ѡ�������ۿ��Եó������A��B�����ѣ���B��C�����ѣ���A��CҲ�����ѡ����д��������������Ȧ���ж����ˡ� 
[����Ҫ��]
��1������˵��������ĵ�һ�а�������������N (N<=30 000)��M (M<=1000)���ֱ����ѧУ��ѧ�������;��ֲ��ĸ���������M��ÿ�а����¸�ʽ����һ�����ֲ�����Ϣ������ѧ����1-N��ţ�
��i�����ֲ�������Mi���ո�ѧ��1���ո�ѧ��2�� ѧ��Mi 
��2�����˵�������һ����������ʾ���������Ȧ���ж����ˡ�
��3������������ 
����  7 4
      3 1 2 3
      2 1 4
      3 5 6 7
      1 6 
  ���  4*/
#include<cstdio>
#include<cstdlib>

void Connect(int *arr, int a, int b) {
	int i=a;
	while (arr[i] && arr[i] != a) {
		i = arr[i];
	}
	
	int j=b;
	while (arr[j] && arr[j] != b) {
		j = arr[j];
	}
	
	arr[i] = b;
	arr[j] = a;
}

int main() {
	
	int n=0, m=0;
	scanf("%d%d", &n, &m);
	int *stu = (int*)malloc(sizeof(int) * (n+1));
	for (int i=0; i<=n; i++) stu[i] = 0;
	for (int i=0; i<m; i++) {
		int count=0;
		scanf("%d", &count);
		int *club = (int*)malloc(sizeof(int) * count);
		for (int j=0; j<count; j++) {
			scanf("%d", &club[j]);
		}
		for (int j=1; j<count; j++) {
			Connect(stu, club[j-1], club[j]);
		}
		free(club);
	}
	
	int max=0;
	for (int i=1; i<=n; i++) {
		int count=1;
		int j=i;
		while (stu[j] && stu[j] != i) {
			j = stu[j];
			count++;
		}
		if (count > max) max = count;
	}
	printf("%d", max);
	free(stu);
	system("pause");
}


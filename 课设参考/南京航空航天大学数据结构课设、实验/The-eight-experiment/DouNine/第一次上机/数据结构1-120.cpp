#include<stdio.h>
#include<stdlib.h>

int main() {
	int n;
	printf("���������ʽP(x)����ߴ��ݣ�"); 
	scanf("%d", &n);
	
	int *a = (int*)malloc(sizeof(int) * (n+1));
	for(int i=0; i<=n; i++) {
		printf("��������Ϊ%d���ϵ����", i);
		scanf("%d", &a[i]);
	}
	
	printf("����ʽP(x)=%d*(x^%d)", a[0], 0);
	for(int i=1; i<=n; i++) {
		printf("+%d*(x^%d)", a[i], i);
	}
	printf("\n");
	
	int x0 = 0;
	printf("������x0��");
	scanf("%d", &x0);
	int sum = a[n];
	for(int i=n-1; i>=0; i--) {
		sum = sum * x0 + a[i];
	}
	
	printf("����ʽP(x0)��ֵ�ǣ�%d\n", sum);  
	free(a);
}

#include<stdio.h>
#include<stdlib.h>

int main() {
	
	int n = 0;
	printf("���������Ա�����ݸ�����");
	scanf("%d", &n);
	
	int *L = (int*)malloc(sizeof(int)*n);
	printf("�������������Ա��е����ݣ�\n");
	int i = 0;
	while(i<n) {
		scanf("%d", &L[i]);
		i++;
	} 
	
	int j = 0;
	int temp = 0;
	for(i=1; i<n; i++) {
		for(j=i; j>0 && L[j-1] > L[j]; j--) {
			temp = L[j-1];
			L[j-1] = L[j];
			L[j] = temp;
		}
	}
	
	for(i=0; i<n; i++) printf("%d ", L[i]);
	free(L);
} 

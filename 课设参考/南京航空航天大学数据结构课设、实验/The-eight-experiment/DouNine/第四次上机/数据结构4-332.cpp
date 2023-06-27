/*
��ѭ�����У���k��쳲���������ǰn� 
ѭ�����г���Ϊk������������ѭ������Ӧ��k��쳲������������k�
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct {
	int font, rear;
	int length;
}Queue;

int main() {
	printf("������k��n��");
	int k = 0, n = 0;
	scanf("%d%d", &k, &n); 
	int *q = (int*)malloc(4*k);
	
	Queue queue;
	queue.font = queue.rear = queue.length = 0;
	int sum = 0;
	for(int i=0; i<=n; i++) {
		if(i < k-1) {
			q[queue.rear] = 0;
			queue.rear++; 
		}
		if(i == k-1) {
			q[queue.rear] = 1;
			queue.rear++;
			sum = 1;
		}
		if(i > k-1) {
			int temp = sum - q[queue.font%k];
			queue.font++;
			q[queue.rear%k] = sum;
			//printf("-----------%d\n", sum);
			queue.rear++;
			sum += temp;
		}
	}
	
	for(int i=queue.font; i<queue.rear; i++) {
		//printf("================%d\n", i);
		printf("%d\n", q[i%k]);
	}
	
	free(q);
} 

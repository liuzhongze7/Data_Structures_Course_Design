/*
����ת�ã�����ת��
����������������ͷ���Ԫ������
5 5 10
����Ԫ�ص��кš��кź�ֵ��
1 2 3
1 3 3
2 2 2
2 4 4
2 5 4
3 1 3
3 5 5
4 1 2
4 3 2
5 5 5
*/
#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int data[100][3]; 
	int row, col, num;	// ������������������� 
}TSMatrix;

int main() {
	TSMatrix T;
	printf("���������������������ͷ���Ԫ������");
	scanf("%d%d%d", &T.row, &T.col, &T.num);
	
	printf("���������ξ����з���Ԫ�ص��кš��кź�ֵ��\n");
	for(int i=0; i<T.num; i++) {
		scanf("%d%d%d", &T.data[i][0], &T.data[i][1], &T.data[i][2]);
	}
	
	TSMatrix M;
	M.col = T.row;
	M.row = T.col;
	M.num = T.num;
	
	int *temp = (int*)malloc(sizeof(int)*(M.row+1));
	for(int i=0; i<=M.row; i++) temp[i] = 0;
	
	for(int i=0; i<T.num; i++) {
		temp[T.data[i][1]]++;
	}
	for(int i=2; i<=M.row; i++) {
		temp[i] += temp[i-1];
	}
	for(int i=M.row; i>=1; i--) {
		temp[i] = temp[i-1];
	}
	
	// ��ʼ��Tת�ó�M 
	for(int i=0; i<T.num; i++) {
		int pos = temp[T.data[i][1]];
		temp[T.data[i][1]]++;
		M.data[pos][0] = T.data[i][1];
		M.data[pos][1] = T.data[i][0];
		M.data[pos][2] = T.data[i][2];
	}
	
	printf("\n========ת��֮��========\n");
	for(int i=0; i<M.num; i++) {
		printf("%d %d %d\n", M.data[i][0], M.data[i][1], M.data[i][2]);
	}
	free(temp);
}




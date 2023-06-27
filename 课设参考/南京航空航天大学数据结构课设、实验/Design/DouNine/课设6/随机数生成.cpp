/*
��������ɳ���
*/ 
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>

using namespace std;


// ���ļ� 
FILE* fileOpen(char *fileName, char *method) {
	FILE *fp;
	if((fp=fopen(fileName,method)) == NULL) {
        printf("file cannot be opened\n");
        return NULL;
    }
    else printf("file has been opened\n");
    return fp;
}

// �ر��ļ� 
void fileClose(FILE *fp) {
	if(fclose(fp) != 0) printf("file cannot be closed\n");
    else printf("file has been closed\n");
    return;
} 


// ��������
void Traverse(int *num, int n) {
	cout<<"\n�������飺\n"; 
	for (int i=0; i<n; i++) {
		cout<<num[i]<<" ";
	}
	cout<<endl;
}


int main() {
	int count = 20000, limit = 0;
//	cout<<"�������������������ĸ���:\n";
//	cin>>count;
	cout<<"��������Щ��������(С�ڵ���ĳ����):\n"; 
	cin>>limit;
	
	FILE *fp = fileOpen("data10.txt", "w");
	
	fprintf(fp, "%d  %d\n", count, limit);
	
	cout<<"���ɵ�����������������£�\n";
	int *num = (int*)malloc(sizeof(int) * count);
	srand(time(0));
	for (int i=0; i<count; i++) {
		num[i] = rand()%limit;
		cout<<num[i]<<" ";
		fprintf(fp, "%d  ", num[i]);
	}
	cout<<endl;
	fileClose(fp);
	
	free(num);
}

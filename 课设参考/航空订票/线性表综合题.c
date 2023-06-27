#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {    /*����ڵ�*/
    int data;
    struct Node *next;
}Node;

int array[100];    /*���Ա�������洢*/
int count;    /*˳��������*/

int createList (int arr[]) {    /*����˳���*/
    int i;
    arr[0] = 0;
    printf("������˳����ȣ�");
    scanf("%d", &count);
    printf("������˳���ڵ�����:\n");
    for (i = 1; i <= count; i++) {
        scanf("%d", &arr[i]);
    }
    return 1;
}

int printList(int arr[]) {    /*��ӡ˳���*/
    int i;
    for (i = 1; i <= count; i++) {   /*��ӡ������*/
    printf("%d ", arr[i]);
    }
    printf("\n");
    return 1;
}

int sort(int arr[]) {    /*�����б�*/
    int M = 1, N = count, i, ch;/*�������٣��鲢������������*/
    int r1[N + 1], r2[N + 1];
    for (i = 1; i <= N; i++) {
        r1[i - 1] = arr[i];
    }
    system("CLS");
    printf("1.ֱ�Ӳ�������\n");
    printf("2.ð������\n");
    printf("3.ֱ��ѡ������\n");
    printf("4.��������\n");
    printf("5.�鲢����\n");
    printf("���������ѡ��");
    scanf("%d", &ch);
    switch(ch) {
        case 1:insertSort(arr);break;
        case 2:bubbleSort(arr);break;
        case 3:selectionSort(arr);break;
        case 4:quickSort(arr, M, N);break;
        case 5:mergeSort(r1, r2, 0, N - 1);
            for (i = 1; i <= N; i++) {
                arr[i] = r1[i - 1];
        }break;
    }
}

int insertSort(int arr[]) {    /*ֱ�Ӳ�������*/
    int i, j;
    for (i = 2; i <= count; i++) {
        arr[0] = arr[i];    /*array[0]��Ϊ�ල��*/
        j = i - 1;
        while (arr[0] < arr[j]) {    /*�Ӻ���ǰ�ҵ���һ���ؼ��ֲ�С��arr[0]�ļ�¼*/
            arr[j + 1] = arr[j];
            j--;
        }
    arr[j + 1] = arr[0];
    }
    return 1;
}

int bubbleSort(int arr[]) {    /*ð������*/
    int i, j, temp;
    for (i = 1; i <= count; i++) {
        for (j = 1; j <= count - i; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return 1;
}

int selectionSort(int arr[]) {    /*ֱ��ѡ������*/
    int i, j, temp, m;
    for (i = 1; i <= count; i++) {
        m = i;
        for (j = i + 1; j <= count; j++) {    /*�ҵ���С������*/
            if(arr[j] < arr[m]) {
                m = j;
            }
        if (i != m) {
            temp = arr[i];
            arr[i] = arr[m];
            arr[m] = temp;
            }
        }
    }
}

int quickSort(int arr[], int M, int N) {    /*��������*/
    int i, j, x;
    i = M, j = N;
    x = arr[i];
    do {
        while ((arr[j] >= x) && (j > i)) {
            j--;
        }
            if (i < j) {
                arr[i] = arr[j];
                i++;
                while (arr[j] <= x && (i < j)) {
                    i++;
                }
                if (i < j) {
                    arr[j] = arr[i];
                    j--;
                }
            }
    }while (i != j);
    arr[i] = x;
    i++;
    j--;
    if (M < j) {
        quickSort(arr, M ,j);
    }
    if (i < N) {
        quickSort(arr, i, N);
    }
}

int merge(int r[], int r2[], int S, int M, int N) {
    int i,k,j;
    i = S, k = S, j = M + 1;    /*��S��ʼ*/
    while ((i != M + 1) && (j != N + 1)) {    /*��������������δ����ʱ*/
        if (r[i] > r[j]) {
            r2[k] = r[j];
            j++;
        } else {
            r2[k] = r [i];
            i++;
        }
        k++;
    }
    while (i != M + 1) {    /*��ʣ�µ�ȫ������*/
        r2[k++] = r[i++];
    }
    while (j != N + 1) {
        r2[k++] = r[j++];
    }
    for (i = S; i <= N; i++) {
        r[i] = r2[i];
    }
}

int mergeSort(int r[], int r2[], int S, int N) {    /*�鲢����*/
    int M;
    if (S < N) {
        M = (S + N)/2;
        mergeSort(r, r2, S, M);
        mergeSort(r, r2, M + 1, N);
        merge(r, r2, S, M, N);
    }
}

int createNode(Node *L) {    /*��������*/
    Node *q;
    int m, n, i;    /*�ڵ����Ϊm���ڵ�����Ϊn*/
    printf("����������ڵ������");
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        q = (Node*)malloc(sizeof(Node));
        printf("������ڵ����ݣ�");
        scanf("%d", &n);
        q -> data = n;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*β��ʶΪNULL*/
    printf("\n");
    return 1;
}

int sortNode(Node *L) {    /*������ڵ�������򣬽���������*/
    int i, j, tempData;
    Node *head, *point;    /*����ָ��point����ָ��head����һ���ڵ�*/
    head = L;
    head = head -> next;
    int length = 0;
    while (head -> next != NULL) {    /*����������*/
        head = head -> next;
        length++;
    }
    for (i = 0; i < length; i++) {    /*ð������*/
        head = L;    /*��head��λ*/
        head = head -> next;
        for(j = i; j < length; j++) {
            point = head -> next;
            if(head -> data >= point -> data) {
                tempData = head -> data;
                head -> data = point -> data;
                point -> data = tempData;
            }
            head = head -> next;
        }
    }
    head = L;    /*ָ��ص���ͷ*/
    head = head -> next;
    while (head != NULL) {    /*�����������Ա���ʾ����*/
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf("\n");
    return 1;
}

int combine(int arr[], Node *L2) {    /*������ű�*/
    int a[100];
    int i, j, temp;
    for (i = 1; i <= count; i++) {
        a[i - 1] = arr[i];
    }
    for (i = 1; i <= count; i++) {
        ;
    }
    while (L2 != NULL) {
        a[count + 1] = L2 -> data;
        count++;
    }
    for (i = 0; i <= count; i++) {
        for (j = 0; j <= count - i; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }
    for (i = 0; i <= count; i++) {
        printf("%d ", a[i]);
    }
}

int main() {
    int choose;
    Node *L2;
    L2 = (Node*)malloc(sizeof(Node));
    while(1) {
        printf("1.����˳���\n");
        printf("2.˳�������\n");
        printf("3.��������\n");
        printf("4.��������\n");
        printf("5.�ϲ�˳���������\n");
        printf("0.�˳�\n");
        printf("��������ѡ��:");
        scanf("%d", &choose);
        switch(choose) {
            case 1:createList(array);printList(array);break;
            case 2:sort(array);printList(array);break;
            case 3:createNode(L2);break;
            case 4:sortNode(L2);break;
            case 5:combine(array, &L2);break;
            case 0:exit(0);
        }
        printf("\n");
    }
}

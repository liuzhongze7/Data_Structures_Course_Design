#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
    int data;
    struct Node *next;
}LNode;

int createList (LNode *L) {    /*�������Ա�*/
    LNode *q;
    int m, n, i;    /*�ڵ����Ϊm���ڵ�����Ϊn*/
    printf("����������ڵ����: ");
    scanf("%d", &m);
    printf("����������ڵ����ݣ��Ӵ�С��:\n");
    for (i = 0; i < m; i++) {
        q = (LNode*)malloc(sizeof(LNode));
        scanf("%d", &n);
        q -> data = n;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*β��ʶΪNULL*/
    return 1;
}

int print(LNode *L) {    /*��ӡ����*/
    LNode *q;
    q = L;    /*ָ��ص���ͷ*/
    q = q -> next;
    if (q == NULL) {    /*��������������ݾ���ʾ������*/
        printf("�����ݣ�");
    } else {
        while (q != NULL) {    /*�����������Ա���ʾ����*/
            printf("%d ", q -> data);
            q = q -> next;
        }
    }
    return 1;
}

int sortList(LNode *L) {    /*�Խڵ�������򣬽���������*/
    int i, j, tempData;
    LNode *head, *point;    /*����ָ��point����ָ��head����һ���ڵ�*/
    head = L;
    head = head -> next;
    int length = 0;
    if (head != NULL) {    /*��������������ݾ���������*/
        while (head -> next != NULL) {    /*����������*/
            head = head -> next;
            length++;
        }
        for (i = 0; i < length; i++) {    /*ð������*/
            head = L;    /*��head��λ*/
            head = head -> next;
        for(j = i; j < length; j++) {
            point = head -> next;
            if (head -> data >= point -> data) {
                tempData = head -> data;
                head -> data = point -> data;
                point -> data = tempData;
                }
            head = head -> next;
            }
        }
    }
    return 1;
}

int splitList(LNode *L1, LNode *L2, LNode *L3) {    /*��ԭ���Ա�ֿ����������Ա�*/
    LNode *p1, *p2, *p3;
    int m;    /*mΪ����*/
    p1 = L1;
    p2 = L2;
    p3 = L3;
    p1 = p1 -> next;
    while (p1 != NULL) {
        m = (p1 -> data) % 2;
        if (m == 1) {    /*��ǰָ��ָ�������Ϊ����ʱ*/
            p2 -> next = p1;
            p2 = p2 -> next;
            p1 = p1 -> next;
        } else if (m == 0) {    /*��ǰָ��ָ�������Ϊż��ʱ*/
            p3 -> next = p1;
            p3 = p3 -> next;
            p1 = p1 -> next;
        } else {
            break;
        }
    }
    p2 -> next = NULL;
    p3 -> next = NULL;
    return 1;
}

int main() {
    LNode *L1, *L2, *L3, *p;
    L1 = (LNode*)malloc(sizeof(LNode));
    L2 = (LNode*)malloc(sizeof(LNode));
    L3 = (LNode*)malloc(sizeof(LNode));
    createList(&L1);
    printf("ԭ���Ա�����Ľ��Ϊ��");
    print(&L1);
    splitList(&L1, &L2, &L3);
    sortList(&L2);
    sortList(&L3);
    printf("\n�������Ա�����Ľ��Ϊ��");
    print(&L2);
    printf("\nż�����Ա�����Ľ��Ϊ��");
    print(&L3);
}

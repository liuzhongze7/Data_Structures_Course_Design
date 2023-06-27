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
    printf("����������ڵ������");
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        q = (LNode*)malloc(sizeof(LNode));
        printf("������ڵ����ݣ�");
        scanf("%d", &n);
        q -> data = n;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*β��ʶΪNULL*/
    return 1;
}

int mergeListSL(LNode *L1, LNode *L2, LNode *L3) {    /*��L1��L2�ϲ���L3������*/
    LNode *p1, *p2, *p3;
    p1 = L1;
    p2 = L2;
    p3 = L3;
    p1 = p1 -> next;
    p2 = p2 -> next;
    while (p1 != NULL && p2 != NULL) {
        if (p1 -> data <= p2 -> data) {    /*���p1��dataС��p2��data���ͽ�p1����L3*/
            p3 -> next = p1;
            p3 = p1;
            p1 = p1 -> next;
        } else {    /*���p2��dataС��p1��data���ͽ�p2����L3*/
            p3 -> next = p2;
            p3 = p2;
            p2 = p2 -> next;
        }
    }
    p3 -> next = (p1 != NULL)? p1: p2;    /*���p1���нڵ㣬�ͽ�p1ʣ��ڵ�ȫ������L3��p2ͬ��*/
    p3 = L3;    /*ָ��ص�L3��ͷ*/
    p3 = p3 -> next;
    printf("�ϲ�������Ա�����Ľ��Ϊ��");
    while (p3 != NULL) {    /*��L3���Ա���ʾ����*/
        printf("%d ", p3 -> data);
        p3 = p3 -> next;
    }
    return 1;
}

int mergeListLS(LNode *L1, LNode *L2, LNode *L3) {    /*��L1��L2�ϲ���L3������*/
    LNode *p1, *p2, *p3;
    p1 = L1;
    p2 = L2;
    p3 = L3;
    p1 = p1 -> next;
    p2 = p2 -> next;
    while (p1 != NULL && p2 != NULL) {
        if (p1 -> data >= p2 -> data) {    /*���p1��data����p2��data���ͽ�p1����L3*/
            p3 -> next = p1;
            p3 = p1;
            p1 = p1 -> next;
        } else {    /*���p2��data����p1��data���ͽ�p2����L3*/
            p3 -> next = p2;
            p3 = p2;
            p2 = p2 -> next;
        }
    }
    p3 -> next = (p1 != NULL)? p1: p2;    /*���p1���нڵ㣬�ͽ�p1ʣ��ڵ�ȫ������L3��p2ͬ��*/
    p3 = L3;    /*ָ��ص�L3��ͷ*/
    p3 = p3 -> next;
    printf("�ϲ�������Ա�����Ľ��Ϊ��");
    while (p3 != NULL) {    /*��L3���Ա���ʾ����*/
        printf("%d ", p3 -> data);
        p3 = p3 -> next;
    }
    return 1;
}

int main() {
    LNode *L1, *L2, *L3;
    int ch;
    L1 = (LNode*)malloc(sizeof(LNode));
    L2 = (LNode*)malloc(sizeof(LNode));
    L3 = (LNode*)malloc(sizeof(LNode));
    printf("��ѡ������˳��");
    printf("1.����");
    printf("2.����\n");
    scanf("%d", &ch);
    createList(&L1);
    createList(&L2);
    switch(ch) {
        case 1:mergeListSL(&L1, &L2, &L3);break;
        case 2:mergeListLS(&L1, &L2, &L3);break;
        default: printf("�������");break;
    }
    return 1;
}


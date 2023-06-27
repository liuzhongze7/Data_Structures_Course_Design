#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
    int num;
    struct Node *next;
}Node;

int create(Node *L) {    /*����Լɪ��*/
    int i;    /*������*/
    int num;    /*ÿ���ڵ��е����ּ�Լɪ�򻷵Ľڵ�����*/
    Node *q;    /*�����½ڵ�*/
    printf("������Լɪ�򻷵Ľڵ�������");
    scanf("%d", &num);
    for (i = 1; i <= num; i++) {    /*�������ݽڵ�*/
        q = (Node*)malloc(sizeof(Node));
        q -> num = i;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*β��ʶΪNULL*/
    return 1;
}

int process(Node *L) {    /*ʵ��Լɪ��*/
    int m, n, i;    /*����ӵ�m���˿�ʼ����n��*/
    Node *head, *point;    /*����ͷ��㣬point�ڵ�(����ɾ���ڵ�)*/
    head = L;
    head = head -> next;    /*��ͷ����L�Ƶ�����ֵ�ĵ�һ���ڵ�*/
    L = head;
    while (head -> next != NULL) {    /*���������һ���ڵ�*/
        head = head -> next;
    }
    head -> next = L;    /*�ջ�*/
    printf("������ӵڼ����˿�ʼ��");
    scanf("%d", &m);
    printf("������Ҫ�����Σ�");
    scanf("%d", &n);
    for (i = 1; i < m; i++) {    /*��ָ���Ƶ���m���˴�*/
        L = L -> next;
    }
    if (n == 1) {    /*�����m������1�Σ������γ���*/
        while(L -> next != L) {    /*������ֻ��Lָ��Ľڵ��Լ��γɻ���������*/
            head = L;    /*L�������Ҫ����Ľڵ�*/
            while(head -> next != L) {    /*��headָ��L��ǰ�ڵ�*/
                head = head -> next;
            }
            printf("%d ", L -> num);
            point = L;   /*��pointָ��ָ���Ѿ�����Ľڵ�*/
            L = L -> next;
            head -> next = L;    /*���ϻ��պ�*/
            free(point);
        }
        printf("%d", L -> num);
        free(L);
        return 1;
    } else {    /*�����m������n��*/
        while(L -> next != L) {
            for (i = 1; i < n; i++) {    /*��Lָ��Ҫ����Ľڵ�*/
                L = L -> next;
            }
            while(head -> next != L) {
                head = head -> next;
            }
            printf("%d ", L -> num);
            point = L;
            L = L -> next;
            head -> next = L;
            free(point);
        }
        printf("%d", L -> num);
        free(L);
        return 1;
    }
}


int main() {
    Node *Circle;
    Circle = (Node*)malloc(sizeof(Node));
    create(&Circle);
    process(&Circle);
}



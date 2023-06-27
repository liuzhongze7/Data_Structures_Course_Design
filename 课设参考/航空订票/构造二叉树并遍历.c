#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct BitTree {
    int data;    /*��������*/
    struct BitTree *lChild, *rChild;    /*�������Һ���ָ��*/
}BitNode, *BitTree;

void buildTree(int inOrder[], int postOrder[], int il, int ir, int pl, int pr, BitTree T) {   /*��������ͺ����������*/
    T = (BitTree)malloc(sizeof(BitNode));
    T -> data = postOrder[pr];    /*�������������һ��Ԫ��Ϊ�������ĸ��ڵ�*/
    int m = il;
    while(inOrder[m] != postOrder[pr]) {    /*���Ҹ��ڵ����������е�λ��*/
        m++;
    }
    if (m == il) {    /*����������������Ϊ��*/
        T -> lChild = NULL;
    } else {
        buildTree(inOrder, postOrder, il, m - 1, pl, pl + m -1 - il, T -> lChild);    /*ȷ��������*/
    }
    if (m == ir) {    /*����������������Ϊ��*/
        T -> rChild = NULL;
    } else {
        buildTree(inOrder, postOrder, m + 1, ir, pr - ir + m, pr - 1, T -> rChild);    /*ȷ��������*/
    }
}

int preOrder(BitTree T) {    /*�ǵݹ��������*/
    BitTree stack[100];    /*����ջ���б���*/
    int front = 0, rear = 0;
    BitNode *p;
    if(T != NULL) {
        stack[rear] = T;    /*�����ڵ���ջ*/
        rear = (rear + 1) % 100;
    }
    while (front != rear) {
        p = stack[front];
        front = (front + 1) % 100;
        printf("%5d", p -> data);    /*����ڵ�*/
        if(p -> lChild != NULL) {    /*��������Ϊ�վ����������*/
            stack[rear] = p -> lChild;    /*��������ջ*/
            rear = (rear + 1) % 100;
        }
        if(p -> rChild != NULL) {    /*�����������*/
            stack[rear] = p -> rChild;    /*��������ջ*/
            rear = (rear + 1) % 100;
        }
    }
    return;
}

int main()  {
    int i, il, ir, pl, pr;    /*il��irΪ�������е����Ҷ˵�, pl��prΪ�������е����Ҷ˵�*/
    int len;
    BitNode *T;    /*���ĸ��ڵ�*/
    printf("����������ĳ���:\n");
    scanf("%d", &len);
    int inOrder[len];    /*���������*/
    printf("������������������:\n");
    for(i = 0; i < len; i++) {
        scanf("%d", &(inOrder[i]));
    }
    int postOrder[len];    /*���������*/
    printf("�����������������:\n");
    for(i = 0; i < len; i++) {
        scanf("%d", &(postOrder[i]));
    }
    il = 0;
    ir = len - 1;
    pl = 0;
    pr = len - 1;
    buildTree(inOrder, postOrder, il, ir, pl, pr, &T);
    preOrder(&T);
    return 1;
}



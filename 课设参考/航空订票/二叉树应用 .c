#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>

typedef int Elemtype;

typedef struct {
    Elemtype e;
}Elem;

typedef struct BitTree {
    Elem data;    /*��������*/
    struct BitTree *lChild, *rChild;    /*�������Һ���ָ��*/
}BitNode, *BitTree;

BitNode *T = NULL;

int createTree(BitTree *T) {    /*����������*/
    Elemtype ch;
    scanf("%d", &ch);
    if(ch == 0) {    /*0��ʾ����*/
        *T = NULL;
    } else {
        *T = (BitTree)malloc(sizeof(BitNode));
        if (!T) {
            exit(1);
        }
        (*T) -> data.e = ch;    /*���ɸ��ڵ�*/
        createTree(&(*T) -> lChild);    /*����������*/
        createTree(&(*T) -> rChild);    /*����������*/
    }
    return 1;
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

int inOrder(BitTree T) {    /*�ǵݹ��������*/
    BitNode *stack[100];
    int top;
    BitNode *p;
    top = 0;
    p = T;
    while(p != NULL || top > 0) {
        while(p != NULL) {    /*����������˵Ľڵ�*/
            stack[top++] = p;
            p = p -> lChild;
        }
        if(top > 0) {    /*��ջ��ѡ��ǰ�ڵ��������*/
            p = stack[--top];
            printf("%5d", p -> data);
            p = p -> rChild;
        }
    }
}

int levelPrint(BitTree T) {    /*�ǵݹ��α���*/
    BitTree queue[100];
    BitNode *p;
    int front = -1, rear = -1;
    rear++;
    queue[rear] = T;
    while(front != rear) {
        front = (front + 1) % 100;
        p = queue[front];
        printf("%5d", p -> data);
        if(p -> lChild != NULL) {
            rear = (rear + 1) % 100;
            queue[rear] = p -> lChild;
        }
        if(p -> rChild != NULL) {
            rear = (rear + 1) % 100;
            queue[rear] = p -> rChild;
        }
    }
}

int judge(BitTree T) {    /*�ж��Ƿ�Ϊ������*/
    if(!T) {    /*����1�����Ƕ���������*/
        return 1;
    } else if(!(T -> lChild)&&!(T -> rChild)) {     /*����������û��*/
        return 1;
    } else if((T -> lChild)&&!(T -> rChild)) {   /*ֻ��������*/
        if((T->lChild->data.e)>(T->data.e)) {
            return 0;    /*����0�����޶�����*/
        } else {
            return(judge(T -> lChild));   /*����Ѱ���ӽڵ�*/
        }
    }
    else if(!(T -> lChild)&&(T -> rChild)) {   /*ֻ��������*/
        if((T->rChild -> data.e) < (T -> data.e)) {
            return 0;
        } else {
            return(judge(T -> rChild));
        }

    } else {    /*�����������������*/
        if((T -> lChild -> data.e) > (T -> data.e)||(T -> rChild -> data.e) < (T -> data.e)) {
            return 0;
        } else {
            return (judge(T -> lChild) && judge(T -> rChild));
        }
    }
}

int searchBst(BitTree T, BitTree G, Elemtype key, BitTree *p) {    /*���ҽڵ�*/
    if(!T) {    /*�ж�ԭ���Ƿ����*/
        *p = G;
        return 0;
    } else if(key == T -> data.e) {
        *p = T;
        return 1;
    }
    else if(key < T -> data.e) {
        return searchBst(T -> lChild, T, key, p);
    }
    else {
        return searchBst(T -> rChild, T, key, p);
    }
    return 1;
}

int insertBst(BitTree T, Elemtype key) {    /*��������������*/
    BitTree p, N;
    if(searchBst(T, NULL, key, &p)) {
        return 0;
    } else {
        N = (BitTree)malloc(sizeof(BitNode));
        N -> data.e = key;
        N -> lChild = NULL;
        N -> rChild = NULL;
        if(!p) {
            T = N;
        } else if(key < p -> data.e) {
            p -> lChild = N;
        } else {
            p -> rChild = N;
        }
    }
    return 1;
}

int deleteBst(BitTree *T, int key) {    /*ɾ������������*/
    if(!(*T)) {
        return 0;
    } else {
        if(key == (*T) -> data.e) {
            Delete(T);    /*�ҵ�ָ���ڵ㣬ɾ��*/
        } else if(key < (*T) -> data.e) {
            return deleteBst(&(*T)->lChild, key);
        } else {
            return deleteBst(&(*T)->rChild, key);
        }
    }
}

int Delete(BitTree *p) { /*ɾ���ڵ�*/
    BitTree q, N;
    if(!(*p) -> lChild && !(*p) -> rChild) {
        *p = NULL;
    } else if(!(*p) -> lChild) {
        q = *p;
        free(q);
    } else if(!(*p) -> rChild) {
        q = *p;
        free(q);
    } else {
        q = *p;
        N = (*p) -> lChild;
        while(N -> rChild) {
            q = N;
            N = N -> rChild;
        }
        (*p) -> data.e = N -> data.e;
        if(q!=*p) {
            q -> rChild = N -> lChild;
        } else {
            q -> lChild = N -> lChild;
        }
        free(N);
    }
    return 1;
}

int main() {
    int ch = 0, flag = 0, key, m;
    flag = judge(T);
    while(1) {
        printf("1.����������\n");
        printf("2.����ǵݹ����\n");
        printf("3.����ǵݹ����\n");
        printf("4.��ηǵݹ����\n");
        printf("5.�ж϶������Ƿ�Ϊ����������\n");
        printf("6.������������������\n");
        printf("7.����������ɾ������\n");
        printf("0.�˳�\n");
        printf("���������ѡ��");
        scanf("%d", &ch);
        switch(ch) {
            case 1:printf("���������ݣ�0Ϊ�սڵ�:\n");
                   createTree(&T);printf("\n");break;
            case 2:printf("�ǵݹ��������Ϊ��\n");
                   preOrder(T);printf("\n");break;
            case 3:printf("�ǵݹ��������Ϊ��\n");
                   inOrder(T);printf("\n");break;
            case 4:printf("�ǵݹ��α���Ϊ��\n");
                   levelPrint(T);printf("\n");break;
            case 5:flag = judge(T);
                   if(flag)
                   printf("�����Ƕ���������\n");
                   else
                   printf("�������Ƕ���������\n");
                   printf("\n");break;
            case 6:printf("���������ݣ�");
                   scanf("%d",&key);
                   insertBst(T, key);break;
            case 7:printf("���������ݣ�");
                   scanf("%d",&m);
                   deleteBst(&T, m);break;
            case 0:exit(0);
        }
        printf("\n");
    }
    return 1;
}

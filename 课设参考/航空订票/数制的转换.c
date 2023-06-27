#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define STACK_INIT_SIZE 100    /*�洢�ռ��ʼ������*/
#define STACKINCREMENT 10    /*�洢�ռ��������*/

typedef struct {
    char *top;
    char *base;
    int stacksize;
}SqStack;

int InitStack (SqStack *S) {   /*����һ����ջ*/
    S -> base = (char*)malloc(STACK_INIT_SIZE*sizeof(char));
    S -> top = S -> base;
    S -> stacksize = STACK_INIT_SIZE;
    return 1;
}

int Push (SqStack *S, int e) {    /*����Ԫ��eΪ�µ�ջ��Ԫ��*/
    if (S -> top - S -> base >= S -> stacksize) {
        S -> base = (char*)realloc(S -> base, (S -> stacksize + STACKINCREMENT)*sizeof(char));
        if (!S -> base) {    /*ջ���*/
            return -1;
        }
        S -> top = S -> base + S -> stacksize;
        S -> stacksize += STACKINCREMENT;
    }
    *(S -> top) = e;    /*�ȸ�ֵ�ڽ�ָ���1*/
    S -> top ++;
    return 1;
}

int Pop (SqStack *S, int *e) {    /*��ջ*/
    if (S -> top == S -> base) {    /*ջ��*/
            return 0;
    } else {
        S -> top --;    /*�Ƚ�ָ���1�ڳ�ջ*/
        *e = *(S -> top);
    }
    return 1;
}

int Convert (SqStack *S, int data) {    /*ת������*/
    int i, j, e;    /*�ֱ�����,������ת���������*/
    i = data / 2;
    j = data % 2;
    Push(S, j);    /*��ԭ����Ϊ0��ֱ����ջ*/
    while (i != 0) {    /*��ԭ����Ϊ0������Ϊ1�ļ�������������ģ����*/
        j = i % 2;
        i = i / 2;
        Push(S, j);
    }
    printf("��Ӧ�Ķ�������Ϊ��");
    while(S -> top != S -> base)    /*������������ݳ�ջ*/
    {
        Pop(S, &e);
        printf("%d ", e);
    }
    return 1;
}

int main() {
    SqStack *S;
    int number;
    InitStack(&S);
    printf("������Ҫת����ʮ��������");
    scanf("%d", &number);
    Convert(&S, number);
}



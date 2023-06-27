#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define STACK_INIT_SIZE 100    /*�洢�ռ��ʼ������*/
#define STACKINCREMENT 20    /*�洢�ռ��������*/

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

int Push (SqStack *S, char e) {    /*����Ԫ��eΪ�µ�ջ��Ԫ��*/
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

int Pop (SqStack *S, char *e) {    /*��ջ*/
    if (S -> top == S -> base) {    /*ջ��*/
            return 0;
    } else {
        S -> top --;    /*�Ƚ�ָ���1�ڳ�ջ*/
        *e = *(S -> top);
    }
    return 1;
}

int isEmpty (SqStack *S) {    /*�ж�ջ�Ƿ�Ϊ��*/
    if (S -> top == S -> base) {
        return 0;
    } else {
        return 1;
    }
}

int match (SqStack *S, int counter) {    /*�ж������Ƿ�ƥ��*/
    int i, flag1 = 0, flag2 = 0, flag3 = 0;    /*��־λflag1,2,3, ��¼��������()[]{}�Ĵ���*/
    char e;
    if (isEmpty(S) == 0) {    /*�ж�ջ�Ƿ�Ϊ��*/
        printf("������ַ�Ϊ�գ�");
    } else {    /*��Ϊ�վ͵�ջ*/
        for (i = 0; i < counter; i++) {
            Pop(S, &e);
            switch (e) {    /*�ж������Ƿ�ƥ��*/
                case '(': flag1--;break;
                case ')': flag1++;break;
                case '[': flag2--;break;
                case ']': flag2++;break;
                case '{': flag3--;break;
                case '}': flag3++;break;
                default: break;
            }
        }
        if (flag1 == 0 && flag2 == 0 && flag3 == 0 && (counter != 0)) {
            printf("����ƥ�䣡");
        } else {
            printf("���Ų�ƥ�䣡");
        }
    }
    return 1;
}

int main() {
    int counter;   /*�������������¼��ջ����*/
    char c = 0;
    SqStack *S;
    InitStack(&S);
    printf("�����������ַ�(�س�����ʾ����)��\n");
    while (c != '\n') {    /*��������ַ��ǻس�ʱ,ֹͣ����*/
        c = getchar();
        if (c != '\n') {    /*��������ַ����ǻس�ʱ,�������ջ*/
            Push(&S, c);
            counter++;
        }
    }
    match(&S, counter);
    return 1;
}

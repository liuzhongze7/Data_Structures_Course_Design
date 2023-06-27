#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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

char getTop(SqStack S){    /*����ջ����һ��Ԫ��*/
    char e;
    if(S.top == S.base)
        return 0;
    e = *(S.top - 1);
    return e;
}

char Precede(char a, char b) {    /*�Ƚ���������������ȼ�,a��b�д�Ŵ��Ƚϵ������,
                                   '>'��ʾa>b,'0'��ʾ�����ܳ��ֵıȽ� */
    int i,j;
    char pre[][7]={    /*�����֮������ȼ�������һ�ű��*/
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};
    switch(a) {
        case '+': i = 0; break;
        case '-': i = 1; break;
        case '*': i = 2; break;
        case '/': i = 3; break;
        case '(': i = 4; break;
        case ')': i = 5; break;
        case '#': i = 6; break;
    }
    switch(b) {
        case '+': j = 0; break;
        case '-': j = 1; break;
        case '*': j = 2; break;
        case '/': j = 3; break;
        case '(': j = 4; break;
        case ')': j = 5; break;
        case '#': j = 6; break;
    }
    return pre[i][j];
}

int in(char c, char OP[8]) {    /*�ж������ĳ���ַ��Ƿ��������*/
    int i;
    for(i = 0; OP[i] != '\0'; i++) {
        if(OP[i] == c) {
            return 1;
        }
    }
    return 0;
}

char Operate(char a, char n, char b) {      /*�����������*/
    int i, j, result;
    char back;
    i = a - '0';    /*��charת��Ϊint*/
    j = b - '0';
    switch(n) {
        case '+': result = i + j; break;
        case '-': result = i - j; break;
        case '*': result = i * j; break;
        case '/': result = i / j; break;
    }
    back = result + '0';
    return back;
}

char evaluateExpression(SqStack OPTR, SqStack OPND) {
    char a, b, c, x, n, temp;
    temp = '#';
    Push(&OPTR, temp);
    char OP[8] = {'+','-','*','/','(',')','#','\0'};
    c = getchar();    /*�����ַ�*/
    while(c != '#' || getTop(OPTR) != '#') {    /*�ж��ǲ��������*/
        if(!in(c, OP)) {    /*������������ջ*/
            Push(&OPND, c);
            c = getchar();
             } else {    /*��������ͺ�ǰ��ıȽ�*/
            x = getTop(OPTR);
            switch(Precede(x, c)) {
                case '<':    /*ջ��Ԫ�����ȼ���*/
                    Push(&OPTR, c);
                    c = getchar();
                    break;
                case '=':    /*�����Ų�������һ�ַ�*/
                    Pop(&OPTR, &x);
                    c = getchar();
                    break;
                case '>':    /*��ջ������������ջ*/
                    Pop(&OPTR, &n);
                    Pop(&OPND, &b);
                    Pop(&OPND, &a);
                    Push(&OPND, Operate(a, n, b));
                    break;
            }
        }
    }
    return getTop(OPND);
}

int main(){
    char c;
    SqStack OPTR;    /*OPTRΪ�����ջ��OPNDΪ����ջ*/
    SqStack OPND;
    InitStack(&OPTR);
    InitStack(&OPND);
    printf("��������ʽ:\n");
    c = evaluateExpression(OPTR, OPND);
    printf("����� = %c\n",c);
    return 1;
}

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct {
    int cof;    //ϵ��
    int exp;    //ָ��
    struct Node *next;    /*ָ����һ���ָ��*/
}Poly;

int createPoly(Poly *L) {    /*��������ʽ����*/
    int x, y;    /*x��ʾϵ����y��ʾָ��*/
    Poly *q;    /*�����½ڵ�*/
    do {
        printf("���������ʽ��ϵ��(����ʽϵ������0ʱ����)��");
        scanf("%d", &x);
        if (x == 0) {    /*���ϵ��Ϊ0�ͽ�ָ������0*/
            y = 0;
        } else {
            printf("���������ʽ��ָ����");
            scanf("%d", &y);
        }
        q = (Poly*)malloc(sizeof(Poly));
        q -> cof = x;
        q -> exp = y;
        L -> next = q;
        L = q;
    }while(L -> cof != 0);    /*ϵ��Ϊ0������*/
    L -> next = NULL;    /*β��ʶΪNULL*/
    return 1;
}

int printPolynoimal(Poly *L) {
    Poly *head;
    head = L;
    head = head -> next;
    if (head -> cof == 0) {
        printf("F(x)=0\n");
        return;
    } else {
        printf("F(x)=%dX^%d", head -> cof, head -> exp);
        head = head -> next;
    }
    while (head -> cof != 0) {
        if (head -> cof > 0) {
            printf("+%dX^%d", head -> cof, head -> exp);
            head = head -> next;
        } else {
            printf("%dX^%d", head -> cof, head -> exp);
            head = head -> next;
        }
    }
    printf("\n");
    return 1;
}


int sortPolynoimal(Poly *L) {    /*�Խڵ�������򣬽���������*/
    int i, j, tempCof, tempExp, length = 0;
    Poly *head, *point;    /*����ָ��point����ָ��head����һ���ڵ�*/
    head = L;
    head = head -> next;
    while (head -> next != NULL) {    /*����������*/
        length++;
        head = head -> next;
    }
    for (i = 0; i < length - 1; i++) {    /*ð������*/
        head = L;   /*��head��λ*/
        head = head -> next;
        for(j = i; j < length - 1; j++) {
            point = head -> next;
            if(head -> exp > point -> exp) {
                tempCof = head -> cof;
                tempExp = head -> exp;
                head -> cof = point -> cof;
                head -> exp = point -> exp;
                point -> cof = tempCof;
                point -> exp = tempExp;
            }
            head = head -> next;
        }
    }
    return 1;
}

int addPolynoimal(Poly *L1, Poly *L2, Poly *L3) {
    int x = 0;    /*xΪ�Ͷ���ʽÿһ���ϵ��*/
    Poly *headL1, *headL2, *headL3;    /*����Ͷ���ʽ��ָ��ͽڵ�*/
    headL1 = L1;
    headL2 = L2;
    headL1 = headL1 -> next;
    headL2 = headL2 -> next;
    while (headL1 -> cof && headL2 -> cof) {
        if (headL1 -> exp == headL2 -> exp) {    /*��ָ����ͬʱ��ϵ�����*/
            x = headL1 -> cof + headL2 -> cof;
            if (x) {    /*ϵ���Ͳ�Ϊ��Ͳ��뵽�Ͷ���ʽ*/
                headL3 = (Poly*)malloc(sizeof(Poly));
                headL3 -> cof = x;
                headL3 -> exp = headL1 -> exp;
                L3 -> next = headL3;
                L3 = headL3;
                headL1 = headL1 -> next;
                headL2 = headL2 -> next;
            } else {    /*ϵ����Ϊ��������һ���ڵ�*/
                headL1 = headL1 -> next;
                headL2 = headL2 -> next;
            }
        } else if (headL1 -> exp < headL2 -> exp){    /*��ָ������ͬʱ����С�Ľڵ����L3*/
            headL3 = (Poly*)malloc(sizeof(Poly));
            headL3 -> cof = headL1 -> cof;
            headL3 -> exp = headL1 -> exp;
            L3 -> next = headL3;
            L3 = headL3;
            headL1 = headL1 -> next;
        } else {
            headL3 = (Poly*)malloc(sizeof(Poly));
            headL3 -> cof = headL2 -> cof;
            headL3 -> exp = headL2 -> exp;
            L3 -> next = headL3;
            L3 = headL3;
            headL2 = headL2 -> next;
        }
    }
    while (headL1 -> cof != 0) {   /*���L1��ʣ�༴��ǰ�ڵ�ϵ����Ϊ0����ʣ�µ�ȫ������L3*/
        headL3 = (Poly*)malloc(sizeof(Poly));
        headL3 -> cof = headL1 -> cof;
        headL3 -> exp = headL1 -> exp;
        L3 -> next = headL3;
        L3 = headL3;
        headL1 = headL1 -> next;
    }
    while (headL2 -> cof != 0) {    /*���L2��ʣ�༴��ǰ�ڵ�ϵ����Ϊ0����ʣ�µ�ȫ������L3*/
        headL3 = (Poly*)malloc(sizeof(Poly));
        headL3 -> cof = headL2 -> cof;
        headL3 -> exp = headL2 -> exp;
        L3 -> next = headL3;
        L3 = headL3;
        headL2 = headL2 -> next;
    }
    headL3 = (Poly*)malloc(sizeof(Poly));    /*�����cofֵΪ0�Ľڵ㣬���뵽����ĩβ��Ϊ��־�ڵ�*/
    headL3 -> cof = 0;
    L3 -> next = headL3;
   return;
}

int main() {
    Poly *L1, *L2, *L3;
    L1 = (Poly*)malloc(sizeof(Poly));
    L2 = (Poly*)malloc(sizeof(Poly));
    L3 = (Poly*)malloc(sizeof(Poly));
    printf("�������һ������ʽ\n");
    createPoly(&L1);
    printf("������ڶ�������ʽ\n");
    createPoly(&L2);
    sortPolynoimal(&L1);
    sortPolynoimal(&L2);
    printf("��һ������ʽ���£�\n");
    printPolynoimal(&L1);
    printf("�ڶ�������ʽ���£�\n");
    printPolynoimal(&L2);
    printf("��Ӻ�Ͷ���ʽ���£�\n");
    addPolynoimal(&L1, &L2, &L3);
    printPolynoimal(&L3);
    return 1;
}


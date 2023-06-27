#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct customer {    /*�˿ͽṹ��*/
	char name[20];
	int id;
	int seat;
	char sex[10];
	char goal[10];
	char type[1];
}Customer;

typedef struct list {    /*���˿͹滮Ϊ����*/
    Customer *array[25];     /*�����25��*/
    int length;
}sqList;

typedef struct node {    /*���ɻ��滮Ϊ����*/
    int number;
	int input;
    struct node *next;
}Node;

int temp1 = 0;    /*���������*/
int temp2 = 0;    /*����������*/

int createPlane(Node *L) {    /*�����ɻ�����*/
    int x, y;
    do {
        printf("������ɻ����(���Ϊ0ʱ�������)��");
        scanf("%d", &x);
        if (x != 0) {
            printf("������ǻ��ڣ�");
            scanf("%d", &y);
            Node *q;    /*�����½ڵ�*/
            q = (Node*)malloc(sizeof(Node));
            temp1++;
            q -> number = x;
            q -> input = y;
            L -> next = q;
            L = q;
        }
    }while(x != 0);    /*�ɻ����Ϊ0ʱ����*/
    L -> next = NULL;
    return 1;
}

int deleteNode(Node *L) {    /*ɾ���ɻ��ڵ�*/
    int num;
    Node *q;
    q = L;
    Node *r = q;
    q = q -> next;
    printf("������Ҫɾ���ķɻ���ţ�����÷ɻ��µĳ˿�ȫ��ɾ��������");
    scanf("%d", &num);
    while(q != NULL) {
        if (q -> number == num) {
            r -> next = q -> next;
            free(q);
            temp1--;
            return 1;
        } else {
            q = q -> next;
            r = r -> next;
        }
    }
    printf("δ�ҵ��÷ɻ���");
    return 0;
}

int initSqList (sqList *S) {    /*������ʼ��*/
    S -> length = 0;
    return 1;
}

int createSqList (Node *L, sqList *S) {   /*����˿�����*/
    int x, y, i;
    Node *q;
    q = L;
    q = q -> next;
    printf("������˿����ڷɻ��ţ�");
    scanf("%d", &x);
    while (q != NULL) {
        if (q -> number == x) {
            printf("�÷ɻ����м����˿�:");
            scanf("%d", &y);
            for (i = temp2 + 1; i <= y; i++) {
            S -> array[i] = createCustomer(i);
            S -> length ++;
            temp2++;
            }
            return S;
        } else {
            q = q -> next;
        }
    }
    printf("δ�ҵ��÷ɻ���ţ�");
    return 0;
}

int createCustomer(int i) {    /*�����³˿�*/
    Customer *q;
    q = (Customer*)malloc(sizeof(Customer));
    printf("������˿����ʶ��ţ�");
    scanf("%d", &(q -> id));
    printf("������˿�������");
    scanf("%s", &(q -> name));
    printf("��������λ�ţ�");
    scanf("%d", &(q -> seat));
    printf("������˿��Ա�");
    scanf("%s", &(q-> sex));
    printf("������Ŀ�ĵأ�");
    scanf("%s", &(q -> goal));
    printf("�������λ����: ");
    scanf("%s", &(q -> type));
    return q;
}

int searchPlane(Node *L) {    /*��Ѱ����*/
    int x, y;
    Node *q;
    q = L;
    printf("�����뺽����ţ�");
    scanf("%d", &x);
    while (q != NULL) {
        if (x == q -> number) {
            printf("�ҵ��ú��࣡\n");
            printf("������ţ�%d, �ǻ���:%d\n", q -> number, q -> input);
            return 1;
        } else {
            q = q -> next;
        }
    }
    printf("δ�ҵ��ú���\n");
    return 0;
}

int searchCustomer(Node *L, sqList *S) {    /*��Ѱ�˿�*/
    int x, y, i;
    char s;
    Node *q;
    q = L;
    q = q -> next;
    printf("������˿����ڷɻ��ţ�");    /*���ɻ��Ƿ����*/
    scanf("%d", &x);
    while(q != NULL) {
        if (q -> number == x) {
            break;
        } else {
            q = q -> next;
        }
    }
    if (q == NULL) {
        printf("δ�ҵ��÷ɻ�\n");
        return 0;
    }
    printf("������˿����ʶ��ţ�");
    scanf("%d", &y);
    for (i = 1; i <= temp2; i++) {
        if (y == S -> array[i] -> id) {
            printf("�ҵ��˿ͣ���ӡ�����ݣ�\n");
            printf("�˿�������%s\n", S -> array[i] -> name);
            printf("�˿����ʶ��ţ�%d\n", S -> array[i] -> id);
            printf("�˿���λ�ţ�%d\n", S -> array[i] -> seat);
            printf("�˿�Ŀ�ĵ�: %s\n", S -> array[i] -> goal);
            printf("��λ���ࣺ%s\n", S -> array[i] -> type);
            return 1;
            }
    }
    printf("δ�ҵ��ó˿�\n");
    return 0;
}

int reserve(Node *L, sqList *S) {
     int i;
    L = L -> next;
    FILE *fp = NULL;
    if ((fp = fopen("Customer.txt", "w")) == NULL) {
        printf("���ܴ��ļ���");
        return 0;
    }
    fprintf(fp, "%d\n", temp1);
    fprintf(fp, "%d\n", temp2);
    while (L != NULL) {    /*����ɻ��ڵ�*/
        fprintf(fp,"%d %d\n", L -> number, L -> input);
        L = L -> next;
    }
    for (i = 1; i <= temp2; i++) {    /*����˿ͽڵ�*/
        fprintf(fp, "%s %d %d %s %s %s\n", S -> array[i] -> name, S -> array[i] -> id, S -> array[i] -> seat,
                 S -> array[i] -> sex, S -> array[i] -> goal, S -> array[i] -> type);
    }
    fprintf(fp, "%d\n", S -> length);
    fclose(fp);
    printf("�ɹ����");
    return 1;
}

int read(Node *L, sqList*S) {
    FILE *fp = NULL;
    int i = 0;
    Node *q;
    if ((fp = fopen("Customer.txt", "r")) == NULL) {
        printf("���ܴ��ļ���");
        return 0;
    }
    fscanf(fp, "%d\n", &temp1);
    fscanf(fp, "%d\n", &temp2);
    for (i = 0; i < temp1; i++) {    /*��ȡ�ɻ�����*/
        q = (Node*)malloc(sizeof(Node));
        fscanf(fp, "%d %d\n", &q -> number, &q -> input);
        L -> next = q;
        L = q;
    }
    for (i = 1; i <= temp2; i++); {
        Customer *temp;
        temp = (Customer*)malloc(sizeof(Customer));
        fscanf(fp,"%s %d %d %s %s %s\n", &temp -> name, &temp -> id, &temp -> seat, &temp -> sex, &temp -> goal,
            &temp -> type);
        S -> array[i] = temp;
        }
    fscanf(fp ,"%d\n", &S -> length);
    fclose(fp);
    printf("�ɹ����");
    return 1;
}

int main() {
    Node *L;
    sqList *S;
    L = (Node*)malloc(sizeof(Node));
    S = (sqList*)malloc(sizeof(sqList));
    initSqList(&S);
    int ch;
    while (1) {
        printf("                       --------�ɻ�ƱԤ��ϵͳ--------\n");
        printf("                               1.��������\n");
        printf("                               2.�����˿�\n");
        printf("                               3.��ѯ������Ϣ\n");
        printf("                               4.��ѯ�˿���Ϣ\n");
        printf("                               5.������Ϣ\n");
        printf("                               6.��ȡ��Ϣ\n");
        printf("                               7.ɾ���ɻ���Ϣ\n");
        printf("                               0.�˳�ϵͳ\n");
        printf("����������ѡ��:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:createPlane(&L);break;
            case 2:S = createSqList(&L, &S);break;
            case 3:searchPlane(&L);break;
            case 4:searchCustomer(&L, S);break;
            case 5:reserve(&L, S);break;
            case 6:read(&L, &S);break;
            case 7:deleteNode(&L);break;
            case 0:exit(0);
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

typedef struct {
    int data[MAXSIZE];
    int length;
} SqList;

void InitList(SqList *L)
{
    L->length = 0;
}

void CreateList(SqList *L)
{
    int i;
    printf("请输入10个整数：\n");
    for(i = 0; i < MAXSIZE; i++) {
        scanf("%d", &L->data[i]);
        L->length++;
    }
}

void DispList(SqList L)
{
    int i;
    printf("顺序表中的元素为：\n");
    for(i = 0; i < L.length; i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

int SearchList(SqList L, int key)
{
    int i;
    for(i = 0; i < L.length; i++) {
        if(L.data[i] == key) {
            printf("查找成功！该元素在顺序表中的位置为：%d，该元素的值为：%d\n", i + 1, L.data[i]);
            return i;
        }
    }
    printf("查找失败！顺序表中不存在该元素！\n");
    return -1;
}

void InsertList(SqList *L, int pos, int key)
{
    int i;
    if(pos < 1 || pos > L->length + 1) {
        printf("插入位置不合法！\n");
        return;
    }
    if(L->length == MAXSIZE) {
        printf("顺序表已满，无法插入！\n");
        return;
    }
    for(i = L->length - 1; i >= pos - 1; i--) {
        L->data[i + 1] = L->data[i];
    }
    L->data[pos - 1] = key;
    L->length++;
    printf("插入成功！\n");
}

void DeleteList(SqList *L, int pos)
{
    int i;
    if(pos < 1 || pos > L->length) {
        printf("删除位置不合法！\n");
        return;
    }
    for(i = pos; i < L->length; i++) {
        L->data[i - 1] = L->data[i];
    }
    L->length--;
    printf("删除成功！\n");
}

int main()
{
    SqList L;
    int choice, key, pos;
    InitList(&L);
    
    printf("请选择需要进行的操作：\n");
    printf("1. 创建顺序表\n");
    printf("2. 查找元素\n");
    printf("3. 插入元素\n");
    printf("4. 删除元素\n");
    printf("5. 显示顺序表\n");
    printf("0. 退出程序\n");
    
    while(1) {
        printf("请输入操作编号：");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                CreateList(&L);
                break;
            case 2:
                printf("请输入需要查找的元素：");
                scanf("%d", &key);
                SearchList(L, key);
                break;
            case 3:
                printf("请输入待插入元素的值：");
                scanf("%d", &key);
                printf("请输入待插入位置：");
                scanf("%d", &pos);
                InsertList(&L, pos, key);
                break;
            case 4:
                printf("请输入待删除位置：");
                scanf("%d", &pos);
                DeleteList(&L, pos);
                break;
            case 5:
                DispList(L);
                break;
            case 0:
                exit(0);
            default:
                printf("输入有误，请重新选择操作！\n");
        }
    }
    return 0;
}


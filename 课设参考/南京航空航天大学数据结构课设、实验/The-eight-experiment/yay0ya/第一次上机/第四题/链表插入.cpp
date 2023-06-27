#include <stdio.h>
#include <stdlib.h>

//����������
typedef struct LNode
{
    int data;
    struct LNode *next;
}LNode, *LinkList;

/* ������ */
LinkList CreatLink(int num)
{
    int data;

    //pָ��ǰ���������һ����㣬qָ��׼������Ľ�㡣
    LinkList head = NULL, rearNode = NULL, newNode;

    for (int i = 0; i < num; i++)
    {
        scanf("%d", &data);
        newNode = (LinkList)malloc(sizeof(LNode));
        newNode -> data = data;
        newNode -> next = NULL;
        if (i == 0)                 //ͷ���
        {
            head = newNode;
        }
        else
        {
            rearNode -> next = newNode;
        }
        rearNode = newNode;
    }
    return head;
}

LinkList LinkInsertSort(LinkList head)
{
    LinkList originList, nodeScan, preNode, newNode;

    if (head == NULL)
        return head;

    //����ԭ����Ϊ�������������
    originList = head -> next;

    //��������ĵ�һ���ڵ�Lָ��ڵ�
    head -> next = NULL;

    //������������
    while (originList)
    {
        newNode = originList;
        originList = originList -> next;

        preNode = NULL;

        //Ѱ��Ԫ�ز���λ��
        for (nodeScan = head; (nodeScan != NULL) && (nodeScan -> data < newNode -> data); preNode = nodeScan, nodeScan = nodeScan -> next);

        //ѭ���˳���ʾ���ҵ��ڵ�����λ��
        if (nodeScan == head)
            head = newNode;
        else
            preNode -> next = newNode;

        newNode -> next = nodeScan;
    }

    return head;
}
/* ����������� */
void PrintLink(LinkList head)
{
    LinkList nodeScan;
    for (nodeScan = head; nodeScan ;nodeScan = nodeScan->next)
    {
        printf("%-3d ", nodeScan->data);
    }
}
int main()
{
    LinkList head;
    int listLen;
    printf("��������ڵ������\n");
    scanf("%d", &listLen);
    printf("����Ԫ��ֵ��\n");

    head = CreatLink(listLen);

    head = LinkInsertSort(head);
    printf("�����\n");
    PrintLink(head);
    putchar('\n');
    return 0;
}


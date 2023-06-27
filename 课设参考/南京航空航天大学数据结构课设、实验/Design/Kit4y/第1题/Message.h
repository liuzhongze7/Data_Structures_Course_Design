#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"Store.h"
using namespace std;
typedef struct SortMessage //����һ��˫��ѭ�����������Ϣ�ǰ�������Ʒ���������̱�š��������������ȡ���Ʒ���ơ��۸��������������ȴӸ����ͣ������������򣬲���һ��ʾ��
{
    int id;//���ӵ�и���Ʒ�����̵��±�
    string StoreName;
    string pdtName;
    double pdtPrice;
    int salesVolume;
    struct SortMessage *next;
    struct SortMessage *last;
}SortMessage;
bool CreateSort(Store *&S,string pdtName,SortMessage *&SortM);
bool ShowMessage(SortMessage *&SortM);

#endif // MESSAGE_H_INCLUDED

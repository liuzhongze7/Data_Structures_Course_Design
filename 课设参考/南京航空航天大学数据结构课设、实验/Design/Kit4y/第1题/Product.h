#ifndef PRODUCT_H_INCLUDED
#define PRODUCT_H_INCLUDED
#include<iostream>
#include<cstdio>
using namespace std;
typedef struct Product //����һ����������洢����������Ϣ������30�������Ա��Ϊ�򣬱�Ŵ�1��ʼ���������ļ��ж�ȡ���ݣ����ܽ����ݴ洢���ļ���������Ϣ�������ݽṹ������ơ�
{
    string pdtName;
    double pdtprice;
    int salesVolume;//ͷ������Ʒ��Ŀ
    struct Product *next;
}Product;


#endif // PRODUCT_H_INCLUDED

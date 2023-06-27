#include<fstream>
#include<cassert>
#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include"Store.h"
#include"Store.cpp"
#define OK 1
using namespace std;
void readTxT(Store *&S)
{
    S = (Store *)malloc(sizeof(Store));
    ifstream infile;
    infile.open("data.txt",ios::in);
    assert(infile.is_open());
    string str;
    stringstream ss;
    getline(infile,str);
    int Storenum;
    ss << str;
    ss >> Storenum;
    S->storeId = Storenum;//�������̸���
    for(int i = 0;i < S->storeId;i++)
    {
        int m;
        Store *newS = (Store *)malloc(sizeof(Store));
        newS->pdt = (Product *)malloc(sizeof(Product));
        Product *pdt = newS->pdt;
        newS->next = NULL;
        pdt->next = NULL;

        getline(infile,str);
        m = atoi(str.c_str());
        newS->storeId = m;//��������ID

        getline(infile,str);
        newS->storeName = str;//����������

        getline(infile,str);
        m = atoi(str.c_str());
        newS->storeCredit = m;//����������Ϣ

        getline(infile,str);
        m = atoi(str.c_str());
        pdt->salesVolume = m;//������Ʒ����
        /*cout << "���̱�ţ�" << newS->storeId << endl;
        cout << "��������" << newS->storeName << endl;
        cout << "����������"<<newS->storeCredit << endl;
        cout << "������Ʒ����" << pdt->salesVolume << endl;
        cout << endl;*/
        for(int j = 0;j < pdt->salesVolume;j++)
        {
            Product *newP  = (Product *)malloc(sizeof(Product));
            newP->next = NULL;

            getline(infile,str);
            newP->pdtName = str;//������Ʒ��

            getline(infile,str);
            double price = (double)atof(str.c_str());//string ת double
            newP->pdtprice = price;//������Ʒ�۸�

            getline(infile,str);
            int volume = atoi(str.c_str());//string ת int
            newP->salesVolume = volume;//������Ʒ����

            /*cout << "Name��" << newP->pdtName << endl;
            cout << "price��" << price << "  " << newP->pdtprice << endl;
            cout << "volume��" << newP->salesVolume << endl;
            cout << endl;*/
            Product *pnow = newS->pdt;
            for(int k = 0;k < j;k++)
                pnow = pnow ->next;
            pnow->next = newP;//����pdt����
        }
        Store *snow = S;
        for(int k = 0;k < i;k++)
            snow = snow->next;
        snow->next = newS;
    }
    infile.close();
}

void writeTXT(Store *&S)
{
    ofstream outfile;
    outfile.open("data1.txt",ios::out);
    Store *snow = S->next;
    outfile << S->storeId << endl;
    for(int i = 0;i < S->storeId;i++)
    {

        outfile << snow->storeId << endl;
        outfile << snow->storeName << endl;
        outfile << snow->storeCredit << endl;
        Product *pnow = snow->pdt;
        int num  = pnow->salesVolume;
        outfile << pnow->salesVolume <<endl;
        for(int j = 0;j < num;j++)
        {
            pnow = pnow->next;
            outfile << pnow->pdtName << endl;
            outfile << pnow->pdtprice <<endl;
            outfile << pnow->salesVolume <<endl;
        }
        snow = snow->next;
    }
    outfile.close();
}
bool TraverseStore(Store *&S)
{
    Store *snow = S->next;

    for(int i = 0 ;i < S->storeId;i++)
    {
        Product *pnow = snow->pdt;
        int num = pnow->salesVolume;
        cout << "���̱�ţ�" << snow->storeId << endl;
        cout << "��������" << snow->storeName << endl;
        cout << "����������"<<snow->storeCredit << endl;
        cout << "������Ʒ����" << pnow->salesVolume << endl;
        cout << endl;
        for(int j = 0;j < num;j++)
        {
            pnow = pnow->next;
            cout << "Name��" << pnow->pdtName << endl;
            cout << "price��" << pnow->pdtprice << endl;
            cout << "volume��" << pnow->salesVolume << endl;
            cout << endl;
        }
        snow = snow->next;
    }
}
int main()
{
    Store *S;
    readTxT(S);
    Store *S1 = S->next;
    Store *S2 = S1->next;
    //cout << S1->storeName << endl;
    //cout << S2->storeName << endl;
    TraverseStore(S);
    writeTXT(S);
    return OK;
}

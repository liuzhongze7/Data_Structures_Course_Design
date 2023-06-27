#include"Store.h"
#include<cstdlib>
#include<fstream>
#include<cassert>
#include<sstream>
#include<string>
#include<cstring>
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define TRUE 1
#define FALSE 0
using namespace std;
bool CreateStore(Store *&S)//S��Store�����ͷ���
{
    S = new Store;
    if(!S)
        exit(OVERFLOW);
    S -> storeId = 0;
    S -> pdt = NULL;
    S -> storeCredit = 0;
    S -> next = NULL;
    return OK;
}
bool InsertStore(Store *&S)
{
    if(!S)
        return ERROR;
    Store *newStore = new Store;
    if(!newStore)
        exit(OVERFLOW);
    newStore -> pdt = new Product;
    Product *pdt = newStore->pdt;
    pdt->next = NULL;
    pdt->salesVolume = 0;//��ʼ�����̵���Ʒ��ĿΪ0
    string name;
    int num = 0;
    cout << "********************** "<< endl;
    cout << "�����뽨�����̵���Ϣ��"<< endl;
    cout << "��������";
    cin >> name;
    cout << "�����ȣ�";
    cin >> num;
    newStore->storeCredit = num;
    cout << newStore->storeName<<endl;
    newStore->storeName = name;
    newStore ->next = NULL;
    cout << "**********************"<<endl;
    S->storeId++;//��������+1
    newStore->storeId = S->storeId;
    if(S->next == NULL)
        S->next = newStore;
    else
    {
        Store *now = S->next;
        while(now->storeId != S->storeId-1)
            now = now->next;
        now->next = newStore;
    }
    return OK;
}
bool DeleteStore(Store *&S,int id)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "�����ڸõ��̣�" << endl;
        return ERROR;
    }
    Store *now = S->next;
    Store *last = S;
    while(now->storeId != id && now != NULL )
    {
        last = now;
        now = now->next;
    }

    last->next = now->next;
    free(now->pdt);
    free(now);
    now = last->next;
    while(now != NULL)
    {
        now->storeId--;
        now = now->next;
    }
    S->storeId--;
    return OK;
}

bool checkMessage(Store *&S,int id)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "�����ڸõ��̣�" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = snow->pdt;
    cout << endl << "******************************" << endl;
    cout << "*�õ�����Ϣ���£�" << endl;
    cout << "*���̺ţ�" << snow->storeId << endl;
    cout << "*��������" << snow->storeName << endl;
    cout << "*���������ȣ�" << snow->storeCredit << endl;
    cout << "*��Ʒ��Ϣ��";
    if(pnow->next == NULL)
        cout << "����Ʒ��Ϣ��" << endl;
    else
        cout << "��������" << pnow->salesVolume << "����Ʒ" << endl;
    cout << "******************************" << endl;
    cout<<endl;
    pnow = pnow->next;
    while(pnow != NULL)
    {
        cout << "******************************" << endl;
        cout << "��Ʒ����" << pnow->pdtName << endl;
        cout << "��Ʒ�۸�" << pnow->pdtprice << endl;
        cout << "��Ʒ������" << pnow->salesVolume << endl;
        cout << "******************************" <<endl<<endl;
        pnow = pnow->next;
    }
    return OK;
}

bool InsertProduct(Store *S,int id)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "�����ڸõ��̣�" << endl;
        return ERROR;
    }
    Product *newPdt = new Product;
    string Name;
    int num;
    cout << "**********************" << endl;
    cout << "�����������Ʒ����Ϣ��" << endl;
    cout << "��Ʒ���ƣ�";
    cin >> Name;
    cout << "��Ʒ�۸�";
    cin >> num;
    newPdt->pdtprice = num;
    newPdt->pdtName = Name;
    newPdt->salesVolume = 0;
    cout << "**********************" << endl;
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = snow->pdt;
    pnow->salesVolume++;
    while(pnow->next != NULL)
        pnow = pnow->next;
    pnow->next = newPdt;
    newPdt->next = NULL;
    return OK;
}
bool DeleteProduct(Store *&S,int id,string pdtName)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "�����ڸõ��̣�" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *p = snow->pdt;
    p->salesVolume--;
    Product *pnow = (snow->pdt)->next;
    Product *plast = snow->pdt;
    while(pnow != NULL && pnow->pdtName != pdtName)
    {
        plast = pnow;
        pnow = pnow->next;
    }
    if(pnow == NULL)
    {
        cout << "û���ҵ�����Ʒ��" << endl;
        return ERROR;
    }
    cout << "����Ʒ��ϢΪ��" << endl;
    cout << "Name��" << pnow->pdtName << endl;
    cout << "price��" << pnow->pdtprice << endl;
    cout << "volume��" << pnow->salesVolume << endl;
    plast->next = pnow->next;
    plast = plast->next;
    delete(pnow);
    return OK;
}
bool ChangeProduct(Store *S,int id,string pdtName)
{
    if(id > S->storeId || id <= 0)
    {
        cout << "�����ڸõ��̣�" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = (snow->pdt)->next;
    while(pnow != NULL && pnow->pdtName != pdtName)
        pnow = pnow->next;
    if(pnow == NULL)
    {
        cout << "û���ҵ�����Ʒ��" << endl;
        return ERROR;
    }
    cout << "��ѡ�����Ʒ��Ϣ����" << endl;
    cout << "��Ʒ���ƣ�" << pnow->pdtName << endl;
    cout << "��Ʒ�۸�" << pnow->pdtprice << endl;
    cout << "��Ʒ������" << pnow->salesVolume << endl << endl;
    int choose;
    cout << "��ѡ��Ҫ�޸ĵ���Ϣ��" <<endl;
    cout << "1����Ʒ����" << endl;
    cout << "2����Ʒ�۸�" << endl;
    cout << "3: ��Ʒ���Ƽ��۸�" << endl;
    cin >> choose;
    if(choose == 1)
    {
        cout << "�������µ���Ʒ���ƣ�";
        cin >> pnow->pdtName;
        return OK;
    }
    else if(choose == 2)
    {
        cout << "�������µ���Ʒ�۸�";
        cin >> pnow->pdtprice;
        return OK;
    }
    else if(choose == 3)
    {
        cout << "�������µ���Ʒ���ƣ�";
        cin >> pnow->pdtName;
        cout << "�������µ���Ʒ�۸�";
        cin >> pnow->pdtprice;
        return OK;
    }
    else
        cout << "����������������룡"<<endl;
}
bool Purchase(Store *S,int id,string pdtName,int num)
{
        if(id > S->storeId || id <= 0)
    {
        cout << "�����ڸõ��̣�" << endl;
        return ERROR;
    }
    Store *snow = S->next;
    while(snow->storeId != id)
        snow = snow->next;
    Product *pnow = (snow->pdt)->next;
    while(pnow != NULL && pnow->pdtName != pdtName)
        pnow = pnow->next;
    if(pnow == NULL)
    {
        cout << "û���ҵ�����Ʒ��" << endl;
        return ERROR;
    }
    cout << "��ѡ�����Ʒ��Ϣ����" << endl;
    cout << "��Ʒ���ƣ�" << pnow->pdtName << endl;
    cout << "��Ʒ�۸�" << pnow->pdtprice << endl;
    cout << "��Ʒ������" << pnow->salesVolume << endl << endl;
    cout << "ȷ������(1Ϊȷ��)" << endl;
    int choose = 0;
    cin >> choose;
    if(choose == 1)
        pnow->salesVolume += num;
    cout << "��ϲ��ɹ������� " << pnow->pdtName << " ��Ʒ " << num << "��" << endl;
    return OK;
}

void readTxT(Store *&S)
{
    S = new Store;
    ifstream infile;
    infile.open("data.txt",ios::in);
    if(!infile.is_open())
    {
        cout << "�ļ���ʧ�ܣ�" << endl;
        exit(ERROR);
    }
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
        Store *newS = new Store;
        newS->pdt = new Product;
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
        cout << "���̱�ţ�" << newS->storeId << endl;
        cout << "��������" << newS->storeName << endl;
        cout << "����������"<<newS->storeCredit << endl;
        cout << "������Ʒ����" << pdt->salesVolume << endl;
        cout << endl;
        for(int j = 0;j < pdt->salesVolume;j++)
        {
            Product *newP  = new Product;
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
    outfile.open("data.txt",ios::out);
    if(!outfile.is_open())
    {
        cout << "�ļ���ʧ�ܣ�" << endl;
        exit(ERROR);
    }
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
        cout << "*******************" << endl;
        cout << "���̱�ţ�" << snow->storeId << endl;
        cout << "��������" << snow->storeName << endl;
        cout << "����������"<<snow->storeCredit << endl;
        cout << "������Ʒ����" << pnow->salesVolume << endl;
        cout << "*******************" << endl;
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

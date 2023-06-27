#include"Message.h"
#define ERROR 0
#define OK 1

bool CreateSort(Store *&S,string pdtName,SortMessage *&SortM)
{
    SortM = new SortMessage;
    SortMessage *SortM1= new SortMessage;
    SortM1->next = SortM;
    SortM1->last = SortM;
    SortM->next = SortM1;
    SortM->last = SortM1;
    SortM->id = 0;
    SortM->pdtName = pdtName;//����ͷ�ڵ�SortM��β�ڵ�SortM1
    Store *now = S->next;
    while(now != NULL)
    {
        Product *pdt = now->pdt;
        while(pdt != NULL)
        {
            if(pdt->pdtName == SortM->pdtName)
            {
                SortMessage *newm = new SortMessage;
                SortM->id++;
                newm->id = now->storeId;
                newm->last = SortM1->last;
                newm->pdtName = pdtName;
                newm->pdtPrice = pdt->pdtprice;
                newm->salesVolume = pdt->salesVolume;
                newm->StoreName = now->storeName;
                SortMessage *SortM2 = SortM1;
                SortMessage *SortM3 = SortM->next;//ѭ������
                while(SortM3 != SortM1)
                {
                    if(SortM3->salesVolume < newm->salesVolume)
                    {
                        SortM2 = SortM3;
                        break;
                    }//Ѱ�Ҳ���λ�ã�������������
                    SortM3 = SortM3->next;
                }
                SortM2->last->next = newm;
                newm->next = SortM2;
                SortM2->last = newm;
                break;
            }
            else
                pdt = pdt->next;
        }
        now = now->next;
    }
    return OK;
}

bool ShowMessage(SortMessage *&SortM)
{
    if(SortM->id == 0)
    {
        cout << "û���������۴���Ʒ" << endl;
        return ERROR;
    }
    SortMessage *now = SortM->next;
    cout << "********************" << endl;
    cout << "��Ʒ���ƣ�"<<SortM->pdtName << endl;
    cout << "********************" << endl << endl;
    while(now != SortM->last)
    {
        cout << "***************************" << endl;
        cout << "��" << now->id << "������" << endl;
        cout << "������:" << now->StoreName << endl;
        cout << "����Ʒ�۸�" << now->pdtPrice << endl;
        cout << "����Ʒ������" << now->salesVolume << endl;
        cout << "***************************" << endl;
        now = now->next;
    }
    return OK;
}

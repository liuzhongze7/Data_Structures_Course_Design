/*1��������վ��Ϣ���������������Ա�
[��������]
���һ�����򣬶�������Ϣ����������Ϣ���������̱�ţ��������������ȣ�0-5��������Ʒ����1���۸�1������1��������Ʒ����2���۸�2������2��������Ʒ����3���۸�3������3������
��Ʒ���ư���(ë����ˢ�����࣬����ϴ��ˮ����ԡ¶��6��������Ʒ)��ÿ�����̾�����������ȷ��������Ʒ���۸����ļ����룬������ʼΪ0��
[����Ҫ��]
��1������һ����������洢����������Ϣ������30�������Ա��Ϊ�򣬱�Ŵ�1��ʼ���������ļ��ж�ȡ���ݣ����ܽ����ݴ洢���ļ���������Ϣ�������ݽṹ������ơ�
��2����������ɾ���̡��������̣�����Զ���һ����������β����ɾ�����̣��Ա��Ϊ׼�����޸ĺ������ı�ţ����ֱ�������ԡ�������ɾ��Ʒ��
��3����ѯĳһ����Ʒ���ƣ�����һ��˫��ѭ�����������Ϣ�ǰ�������Ʒ���������̱�š��������������ȡ���Ʒ���ơ��۸��������������ȴӸ����ͣ������������򣬲���һ��ʾ��
��4������ĳһ���̵���Ʒ���޸ĵ�����������Ʒ����Ϣ��������
��5������һ��˳��ṹ������Ʒ��Hash�����ַ���洢��ǰÿ����Ʒ������������� 
��6���κε�������Ϣ�仯��ʵ���ļ��洢��*/
#include"Product.h"//������Ϣ
#include"Store.h" //��������
#include"Message.h"//��Ʒ
#include"Store.cpp"//���к���ʵ��
#include"Message.cpp"//������Ϣ�ļ򵥺�������
#define OK 1
#define ERROR 0
int main()
{
    Store *S;
    CreateStore(S);
    int count = 0;
    cout<<"233"<<endl;
    while(1)
    {
        cout << "��������Ҫ���еĲ�����" << endl;
        cout << "1���������̣�" << endl;
        cout << "2��ɾȥ���̣�" << endl;
        cout << "3���������̵���Ʒ��" << endl;
        cout << "4��ɾȥ���̵���Ʒ��" << endl;
        cout << "5���Ķ����̵���Ʒ��Ϣ��" << endl;
        cout << "6��������Ʒ��" << endl;
        cout << "7���鿴������Ϣ��" <<endl;
        cout << "8��������Ʒ�������̰������ߵ������У�" << endl;
        cout << "9�����ļ��������Ϣ��" << endl;
        cout << "10���鿴�������̣�" << endl;
        cout << "11��д���ļ���" <<endl;
        cout << "12���˳���" << endl;
        scanf("%d",&count);
        if(count == 1)
        {
            InsertStore(S);
        }
        if(count == 2)
        {
            int Id;
            cout << "������Ҫɾ���ĵ����̱�ţ�";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"�Ƿ�ȷ������Y/N��" << endl;
            cin >> ch;
            if(ch == 'Y')
                DeleteStore(S,Id);
        }
        if(count == 3)
        {
            int Id;
            cout << "������Ҫ������Ʒ�ĵ����̱�ţ�";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"�Ƿ�ȷ������Y/N��" << endl;
            cin >> ch;
            if(ch == 'Y')
                InsertProduct(S,Id);
        }
        if(count == 4)
        {
            int Id;
            string Name;
            cout << "������Ҫɾȥ��Ʒ�ĵ����̱�ţ�";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"�Ƿ�ȷ������Y/N��" << endl;
            cin >> ch;
            if(ch == 'Y')
            {
                cout << "������Ҫɾȥ����Ʒ���ƣ�";
                cin >> Name;
                DeleteProduct(S,Id,Name);
            }
        }
        if(count == 5)
        {
            int Id;
            string Name;
            cout << "������Ҫ�Ķ���Ϣ����Ʒ���ڵ����̱�ţ�";
            cin >> Id;
            checkMessage(S,Id);
            char ch;
            cout<<"�Ƿ�ȷ������Y/N��" << endl;
            cin >> ch;
            if(ch == 'Y')
            {
                cout << "������Ҫ�Ķ���Ϣ����Ʒ���ƣ�";
                cin >> Name;
                ChangeProduct(S,Id,Name);
            }
        }
        if(count == 6)
        {
            int Id;
            string Name;
            int num;
            cout << "������Ҫ�������Ʒ���ڵ����̱�ţ�";
            cin >> Id;
            checkMessage(S,Id);
            cout << "������Ҫ�������Ʒ���ƣ�";
            cin >> Name;
            cout << "������Ҫ�������Ʒ������";
            cin >> num;
            Purchase(S,Id,Name,num);
        }
        if(count == 7)
        {
            int Id;
            cout << "������Ҫ���ҵ����̱�ţ�";
            cin >> Id;
            checkMessage(S,Id);
        }
        if(count == 8)
        {
            string name;
            cout << "������Ҫ���ҵ���Ʒ" << endl;
            cin >> name;
            SortMessage *SortM;
            CreateSort(S,name,SortM);
            ShowMessage(SortM);
        }
        if(count == 9)
        {
            readTxT(S);
        }
        if(count == 10)
        {
            TraverseStore(S);
        }
        if(count == 11)
        {
            writeTXT(S);
        }
        if(count == 12)
        {
            return OK;
        }
        cout << endl;
    }
    return OK;
}

/*
* FileName:  FamilyTree.cpp
* Author:    ���ַ�
* StuNumber: 1951976
* Date:      2020.12.15
*/


#include <iostream>
#include <string>
using namespace std;

// ʹ����Ů-�ֵ�����

/*=================== ���˽���� =======================*/
struct PersonNode
{
    string personName;                // ����
    PersonNode* firstChild = NULL;    // ����Ů
    PersonNode* nextSibling = NULL;   // ���ֵ�
    PersonNode(string value, PersonNode * first = NULL, PersonNode * next = NULL)
            : personName(value), firstChild(first), nextSibling(next) {}    // ���캯��
};


/*=================== �������� ===========================*/
class FamilyTree
{
private:
    PersonNode* root = nullptr;       // ����㡪������
    PersonNode* current = nullptr;    // ��ǰ���

    bool Find(string name);                                  // ��������name
    bool Find(PersonNode* p, string name);                   // ����pΪ������������name
    bool AddPerson(string familyName, string childName);     // �����Ů
    void PrintFamily(PersonNode * p);                        // �Թ�������ʽ��ӡ����
    bool Update(string originName, string updateName);       // ��������
    bool DeletePerson(string name);                          // ɾ����ͥ
    void Destroy(PersonNode* delbranch);                     // ���ٷ�֧

public:
    FamilyTree() : root(nullptr) {}                         // ���캯��
    ~FamilyTree() { Destroy(root); }                        // ��������
    bool AddAncestor(string rootAncestor);                  // �������
    string GetAncestor();                                   // ��ȡ��������
    void Switch(char choice);                               //����ѡ���� 
};

// ����ѡ����
void FamilyTree::Switch(char choice)
{
    switch (choice)
    {
    // ����µ��Ӵ�
    case 'A':    
    {
        cout << "������Ҫ������ͥ���˵������� ";
        string fatherName;
        cin >> fatherName;
        cout << "������" << fatherName << "�Ķ�Ů������ ";
        int kidNum;
        cin >> kidNum;
        while (kidNum < 0)
        {
            cout << "��������Ϊ�����������������룺";
            cin >> kidNum;
        }
        cout << "����������" << fatherName << "�Ķ�Ů�������� ";
        string kidName;
        int IsExist = 1;
        while (kidNum--)
        {
            cin >> kidName;
            if (!AddPerson(fatherName, kidName))
                IsExist = 0;
        }
        if (IsExist == 1)
        {
            cout << fatherName << "�ļ�ͥ�ǣ� ";
            PrintFamily(current);
        }
        else
            cout << "�������޴��ˣ�" << endl;
        break;
    }

    // Ϊĳ��ͥ�����Ů
    case 'B':
    {
        cout << "������Ҫ�����Ů���˵������� ";
        string fatherName;
        cin >> fatherName;
        cout << "������" << fatherName << "����Ů�������� ";
        string kidName;
        cin >> kidName;
        if (AddPerson(fatherName, kidName))
        {
            cout << fatherName << "�ļ�ͥ�ǣ� ";
            PrintFamily(current);
        }
        else
            cout << "�������޴��ˣ�" << endl;
        break;
    }

    // ��ɢ��ͥ
    case 'C':
    {
        cout << "������Ҫ��ɢ��ͥ�˵������� ";
        string fatherName;
        cin >> fatherName;
        if (DeletePerson(fatherName))
            cout << "��ʱ���������ǣ� ";
        else
            cout << "�������޴��ˣ�" << endl;

        cout << "��ʱ���������ǣ� ";
        PrintFamily(root);
        break;
    }

    // ���ļ�ͥ��Ա����
    case 'D':
    {
        cout << "������Ҫ�����������˵�Ŀǰ������ ";
        string originName;
        cin >> originName;
        cout << "��������ĺ�������� ";
        string newName;
        cin >> newName;
        if (Update(originName, newName))
            cout << originName << "�Ѹ���Ϊ" << newName << endl;
        else
            cout << "�������޴��ˣ�" << endl;

        cout << "��ʱ���������ǣ� ";
        PrintFamily(root);
        break;
    }

    // ��ѯĳ��ͥ�г�Ա
    case 'E':
    {
        cout << "��������Ҫ��ѯ�ļ�ͥ���ף� ";
        string fatherName;
        cin >> fatherName;
        cout << "�ü�ͥ����Ϊ�� ";
        if (Find(fatherName))
            PrintFamily(current);
        else
            cout << "�������޴��ˣ�" << endl;
        break;
    }

    // ��ѯ�������г�Ա
    case 'F': 
    {
        cout << "�ô��ͥ���������ǣ��������ʽ�� ";
        PrintFamily(root);
        break;
    }

    // �˳�����
    case 'G':
    {
        exit(1);
        break;
    }

    default: break;
    }
}

// �������
bool FamilyTree::AddAncestor(string rootAncestor)
{
    root = new PersonNode(rootAncestor);
    if (root)
        return true;
    return false;
}

// ��������
string FamilyTree::GetAncestor()
{
    return root->personName;
}

// �����Ů
bool FamilyTree::AddPerson(string familyName, string childName)
{
    current = nullptr;                    // ��ͷ����
    if (Find(root, familyName) == false)  // û���ҵ�
    {
        return false;
    }
    else
    {
        PersonNode* curChild = current->firstChild;  //�ж�˫�׵�һ�������Ƿ����

        if (curChild == nullptr)                     // ��һ�����Ӳ�����,ֱ�ӳ�Ϊ��һ������
        {
            curChild = new PersonNode(childName);
            current->firstChild = curChild;
        }
        else                                 // ��һ�����Ӵ��ڣ����ڸú��ӵ��ֵ�����
        {
            PersonNode* p = current->firstChild;  // ָ��ǰ���ĵ�һ������
            while (p->nextSibling != nullptr)
                p = p->nextSibling;

            p->nextSibling = new PersonNode(childName);  //�����ֵ���ĩβ
        }

        return true;
    }
}

// �Ӹ�������������Ϊname����
bool FamilyTree::Find(string name)
{
    if (root == nullptr)
        return false;
    return Find(root, name);
}

// �ڸ�Ϊ*p��������ֵΪfamilyName�Ľ�㣬�ҵ�ʹp��Ϊ��ǰ��㣬����true�����򣬵�ǰ��㲻�䣬����false
bool FamilyTree::Find(PersonNode* p, string name)
{
    bool result = false;
    if (p->personName == name)
    {
        result = true;
        current = p;
    }
    else
    {
        PersonNode* q = p->firstChild;
        while (q != nullptr && !(result = Find(q, name)))
            q = q->nextSibling;
    }
    return result;
}

// ��������
bool FamilyTree::Update(string originName, string updateName)
{
    current = nullptr;            // �Ӹ���㿪ʼ����
    if (Find(root, originName))
    {
        current->personName = updateName;
        return true;
    }
    else
        return false;
}

// ɾ����Ϊname���˵ļ�ͥ
bool FamilyTree::DeletePerson(string name)
{
    current = nullptr;
    if (Find(root, name)) // ����Ů-���ֵܷ�����ֱ��ɾ��
    {
        current->personName = "#"; //��ʱʵ��ɾ������
        PersonNode* p = current->firstChild;
        Destroy(current->firstChild);  // �����Ӵ�
        current->firstChild = nullptr;
        return true;
    }
    else
        return false;
}

// ���ٷ�֧
void FamilyTree::Destroy(PersonNode* delbranch)
{
    if (delbranch != nullptr)
    {
        Destroy(delbranch->firstChild);
        Destroy(delbranch->nextSibling);
        delete delbranch;
    }
}

// �Թ�������ʽ��ӡ��ͥ��Ա
void FamilyTree::PrintFamily(PersonNode * p)
{
    PersonNode * child;
    cout << p->personName;
    if (p->firstChild)
    { //�к���
        cout << "(";
        for (child = p->firstChild; child->nextSibling; child = child->nextSibling)
        {
            PrintFamily(child);
            cout << ",";
        }
        PrintFamily(child);
        cout << ")";
    }
}

 // ��ʼ������
void Interface() 
{
    cout << "********************************************" << endl;
    cout << "**            ���׹���ϵͳ                **" << endl;
    cout << "**                                        **" << endl;
    cout << "**         ��ѡ��Ҫִ�еĲ���             **" << endl;
    cout << "**            A---���Ƽ���                **" << endl;
    cout << "**            B---��Ӽ�ͥ��Ա            **" << endl;
    cout << "**            C---��ɢ�ֲ���ͥ            **" << endl;
    cout << "**            D---���ļ�ͥ��Ա����        **" << endl;
    cout << "**            E---��ѯС��ͥ����          **" << endl;
    cout << "**            F---��ѯ��������            **" << endl;
    cout << "**            G---�˳�����                **" << endl;
    cout << "**                                        **" << endl;
    cout << "**          ��ϵͳʹ�ù������ʽ������ף�**" << endl;
    cout << "********************************************" << endl;
}

/*=========================== ������ =========================================*/
int main()
{
    Interface();                // ��ʼ������
    FamilyTree family;
    cout << "\n�����뽨��һ�����ף�\n\n";
    cout << "���������ȵ������� ";
    string name;
    cin >> name;
    family.AddAncestor(name);  // �������
    cout << "�˼��׵������ǣ� " << family.GetAncestor() << endl;

    char choice;
    while (1)
    {
        cout << "\n\n��ѡ��Ҫִ�еĲ����� ";
        cin >> choice;

        while (choice < 'A' || choice > 'G')  // ��������
        {
            cout << "�޲�����������ѡ�� ";
            cin >> choice;
        }

        family.Switch(choice);   // ����ѡ��
    }

    system("pause");    // ����.exe�ļ��˳�ǰ��ʾ���
    return 0;
}




/*
* Author:    ���ַ�
* StuNumber: 1951976
* Date:      2020.11.20
*/


#include <iostream>
#include <string>
#include<iomanip>

using namespace std;


/*=========================== ѧ����Ϣ�ṹ�� ==============================*/
struct StudentInfo
{
    string stuNumber;    // ѧ��
    string stuName;      // ����
    string stuGender;    // �Ա�
    string stuAge;       // ����
    string stuCategory;  // ���
};

// ��������
istream & operator>>(istream & in, StudentInfo & stu)
{
    in >> stu.stuNumber >> stu.stuName >> stu.stuGender >> stu.stuAge >> stu.stuCategory;
    return in;
}

// �������
ostream & operator<<(ostream & out, const StudentInfo & stu)
{
    out << setiosflags(ios::left)
        << setw(12) << stu.stuNumber
        << setw(12) << stu.stuName 
        << setw(12) << stu.stuGender
        << setw(12) << stu.stuAge
        << setw(12) << stu.stuCategory << endl;
    return out;
}


/*============================== ѧ����� =================================*/
struct StudentNode
{
    StudentInfo data;    // ѧ����Ϣ
    StudentNode * link;  // ָ����
    StudentNode(StudentNode * next = NULL) : link(next) {}
    StudentNode(StudentInfo d, StudentNode * next = NULL) :data(d), link(next) {}
};

// ���ѧ����Ϣ
ostream& operator<<(ostream& out, const StudentNode& stuNode)
{
    out << stuNode.data;
    return out;
}


/*====================== ��������ϵͳ�� ���� ������ʵ�� =========================*/
class StudentSystem
{
private:
    StudentNode * headNode;                 // �����ͷָ��
    StudentNode * rearNode;                 // βָ��
    StudentNode * Locate(int i);            // ��λ������������i��Ԫ��
    StudentNode * Locate(string stuNumber); // ��λ��������ѧ������Ԫ�� 
    void Init(const StudentInfo & stu);     // ��ʼ������
public:
    StudentSystem();                        // ���캯��
    ~StudentSystem();                       // ��������
    int Length() ;                          // ͳ�Ʊ���ѧ������
    void Interface();                       // ��ʼ������
    void Create();                          // ����������Ϣϵͳ
    void Search();                          // ͨ�����Ų��Ҳ������Ϣ
    void Insert();                          // ��λ�ò���ѧ����Ϣ
    void Delete();                          // ͨ������ɾ��ѧ����Ϣ
    void Update();                          // ͨ�������޸�ѧ����Ϣ(ѧ�Ų��ܸ�)
    void Output();                          // ������п�����Ϣ
    void Switch(int choice);                // ����ѡ����
};

// ���캯��
StudentSystem::StudentSystem()
{
    rearNode = headNode = new StudentNode;
}
void StudentSystem::Init(const StudentInfo& stu)
{
    StudentNode* newNode = new StudentNode(stu);
    rearNode->link = newNode;
    rearNode = newNode;
}

// ��������
StudentSystem::~StudentSystem()
{
    StudentNode * q;
    while (headNode->link)
    {
        q = headNode->link;
        headNode->link = q->link;
        delete q;
    }
    delete headNode;     // �ͷ�ͷ�ڵ�
}

// ��ʼ������
void StudentSystem::Interface()
{
    cout << "***************************************\n";   //����
    cout << "**                                   **\n";
    cout << "**         ��ӭ���뿼����Ϣϵͳ      **\n";
    cout << "**           ֧�ֹ��ܣ�              **\n";
    cout << "**              0���˳�              **\n";
    cout << "**              1������              **\n";
    cout << "**              2��ɾ��              **\n";
    cout << "**              3������              **\n";
    cout << "**              4���޸�              **\n";
    cout << "**              5��ͳ��              **\n";
    cout << "**                                   **\n";
    cout << "***************************************\n\n";
    cout << "�뽨��������Ϣϵͳ��\n";
}

// ����ϵͳ
void StudentSystem::Create()
{
    int n;
    StudentInfo stu;
    cout << "�����뿼�������� ";
    cin >> n;
    if (n < 1)
    {
        cout << "��������ӦΪ�����������������룺 ";
        cin >> n;
        
    }
    cout << "���������뿼���Ŀ��š��������Ա����估�������\n" << endl;
    for (int i = 1; i <= n; i++)
     {
        cin >> stu;
        Init(stu);
     }
}

// ��λ������������i��Ԫ��
StudentNode * StudentSystem::Locate(int i)
{
    if (i < 0 || i > Length())
        return NULL;
    StudentNode * current = headNode;
    int k = 0;
    while (current && k < i)
    {
        current = current->link;
        k++;
    }
    return current;
}

// ��λ��������ѧ������Ԫ�� 
StudentNode* StudentSystem::Locate(string stuNumber)
{
    StudentNode * current = headNode->link;
    while (current)
    {
        if (current->data.stuNumber == stuNumber)
        {
            return current;
            break;
        }
        current = current->link;
    }
    return NULL;
}

// ����
int StudentSystem::Length()
{
    int length = 0;
    StudentNode* p = headNode->link;
    while (p)
    {
        p = p->link;
        length++;
    }
    cout << "Ŀǰ��������Ϊ�� " << length << endl;
    return length;
}

// ͨ�����Ų��Ҳ������Ϣ
void StudentSystem::Search()  
{
    cout << "������Ҫ���ҵĿ����Ŀ��ţ� ";
    string stuNumber;
    cin >> stuNumber;
    StudentNode* current = Locate(stuNumber);
    if (!current)
        cout << "�ÿ��������ڣ�\n";
    else
    {
        cout << setiosflags(ios::left)
            << setw(12) << "����"
            << setw(12) << "����"
            << setw(12) << "�Ա�"
            << setw(12) << "����"
            << setw(12) << "�������";
        cout << endl;
        cout << current->data;
    }
}

// ����ѧ����Ϣ
void StudentSystem::Insert()  
{
    cout << "��������Ҫ���뿼����λ�ã� ";
    int i;
    cin >> i;
    StudentNode * precurrent = Locate(i - 1);
    if (!precurrent)
        cout << "�������λ�ò����ڣ�\n";
    else
    { 
        cout << "����������Ҫ���뿼���Ŀ��š��������Ա����估�������!\n";
        StudentInfo stu;
        cin >> stu;
        StudentNode* newNode = new StudentNode(stu);
        newNode->link = precurrent->link;
        precurrent->link = newNode;
        Output();              // ������
    }
}

// ͨ������ɾ��ѧ����Ϣ
void StudentSystem::Delete()   
{
    cout << "��������Ҫɾ���Ŀ������ţ� ";
    string stuNumber;
    cin >> stuNumber;
    StudentNode * del = Locate(stuNumber);
    if (!del)
        cout << "������Ŀ��������ڣ�\n";   // Ҫɾ����ѧ��������
    else
    {
        cout << "��ɾ���Ŀ�����Ϣ�ǣ� " << del->data << endl;
        if (headNode->link == del)     // Ҫɾ�����ʱ��һ�����
        {
            headNode->link = rearNode = NULL;
            delete del;
        }
        else
        {
            StudentNode* q;
            if (del->link == NULL)
                q = new StudentNode;   // Ҫɾ������ǵ�һ�����
            else
                q = del->link;     // �뵱ǰ������һ����㽻�����ݺ�ɾ����һ�����
            del->data = q->data;           // ����һ��������ݸ��ǵ�ǰ����
            del->link = q->link;
            delete q;
        }
    }
    Output();
}

// ͨ�������޸�ѧ����Ϣ
void StudentSystem::Update()                  
{
    cout << "��������Ҫ�޸ĵĿ�����ѧ�ţ� ";
    string stuNumber;
    cin >> stuNumber;
    StudentNode * current = Locate(stuNumber);
    if (!current)
        cout << "��Ҫ�޸ĵĿ��������ڣ�\n";
    else
    {
        cout << "������������ĺ����Ŀ��š��������Ա����估�������!\n";
        StudentInfo stu;
        cin >> stu;
        current->data = stu;
        Output();
    }
}

// ����ѡ����
void StudentSystem::Switch(int choice)
{
    switch (choice)
    {
    case 0: exit(1); break;
    case 1: Insert(); break;
    case 2: Delete(); break;
    case 3: Search(); break;
    case 4: Update(); break;
    case 5: Length(); break;
    }
}

// �������
void StudentSystem::Output()
{
    if (headNode->link)
    {
        cout << setiosflags(ios::left)
            << setw(12) << "����"
            << setw(12) << "����"
            << setw(12) << "�Ա�"
            << setw(12) << "����"
            << setw(12) << "�������";
        cout << endl;
        StudentNode* current = headNode->link;
        while (current)
        {
            cout << current->data;
            current = current->link;
        }
    }
    else
        cout << "�޿�����" << endl;
}


/*================================= ������ ===================================*/
int main()
{
    StudentSystem stuSystem;
    stuSystem.Interface();             // ��ʼ������
    stuSystem.Create();                // ����ϵͳ
    stuSystem.Output();                // ����մ�����ϵͳ
    int choice;                        // ����ѡ��
    while (1)
    {
        cout << "\n��ѡ����Ҫ���еĲ����� ";
        cin >> choice;
        if (choice < 0 || choice > 5)
        {
            cout << "�޴˲����룬���������룺 ";
            cin >> choice;
        }
        stuSystem.Switch(choice);
    }
    return 0;
}
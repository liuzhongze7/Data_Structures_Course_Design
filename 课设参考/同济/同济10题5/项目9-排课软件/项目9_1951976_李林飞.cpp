/*
* FileName: CoursseScheduling.cpp
* Author : ���ַ� 
* StuNumber: 1951976
* Date: 2020.12.20
*/


#define _CRT_SECURE_NO_WARNINGS    // �õ�strcpy()��strncpy() 

#include <iostream>
#include <vector>    
#include <cstring>
#include <fstream> 
#include <iomanip>

using namespace std;



/*========================================== ������ =======================================*/
// ���н��
template<class Type>
struct QueueNode
{
    Type data;
    QueueNode<Type>* link;
    QueueNode(QueueNode<Type>* next = NULL) :link(next) {}
    QueueNode(Type d, QueueNode<Type>* next = NULL) :data(d), link(next) {}
};

template<class Type>
class Queue
{
private:
    QueueNode<Type>* front;    // ����ָ��
    QueueNode<Type>* rear;     // ��βָ��

public:
    Queue() :front(NULL), rear(NULL) {}  // ���캯��
    ~Queue();                            // ��������
    Type Front();                        // ���ض���Ԫ��
    Type Back();                         // ���ض�βԪ��
    void Push(const Type& item);         // ���
    void Pop();                          // ����
    bool Empty();                        // �п�
    int Size();                          // ����
};

// �������� ���� �ͷſռ�
template<class Type>
Queue<Type>::~Queue()
{
    QueueNode<Type>* p;
    while (front)
    {
        p = front;
        front = front->link;
        delete p;
    }
}

// ���ض���Ԫ��
template<class Type>
Type Queue<Type>::Front()
{
    return front->data;
}

// ���ض�βԪ��
template<class Type>
Type Queue<Type>::Back()
{
    return rear->data;
}

// ���
template<class Type>
void Queue<Type>::Push(const Type& item)
{
    if (front == NULL)   // �ն���
    {
        front = rear = new QueueNode<Type>(item);
        if (front == NULL) {
            cout << "�ռ����ʧ�ܣ�" << endl;
            exit(1);
        }
    }
    else               // �ǿն���
    {
        rear->link = new QueueNode<Type>(item);
        if (rear->link == NULL) {
            cout << "�ռ����ʧ�ܣ�" << endl;
            exit(1);
        }
        rear = rear->link;    // ����βָ��
    }
}

// ����
template<class Type>
void Queue<Type>::Pop()
{
    if (Empty())
    {
        cerr << "Attempt to pop the empty queue!" << endl;
        exit(1);
    }
    QueueNode<Type>* q = front;
    front = front->link;
    delete q;
}

// �п�
template<class Type>
bool Queue<Type>::Empty()
{
    return front == NULL;
}

// ���ض��г���
template<class Type>
int Queue<Type>::Size()
{
    int length = 0;
    QueueNode<Type>* p = front;
    while (p)
    {
        length++;
        p = p->link;
    }
    return length;
}




/*========================================== ͼ�� ===========================================*/
class Graph
{
private:
    int numVertex;           // ������
    int numEdge;             // ����
    int** matrix;            // �ڽӾ���    
    int* mark;               // �������
    int* inDegree;           // ���

public:
    Graph(int n);            // ���캯��
    ~Graph();                // ��������
    int Vnum()const;         // ���ض�����
    int Enum()const;         // ���ر���

    int first(int v)const;                // ���ض���v���ڽӵ�
    int next(int v, int w)const;          // ������һ�ڽӵ�
    void setEdge(int v, int w, int wgt);  // ��ӱ�
    void deletEdge(int v, int w);         // ɾ����
    int weight(int v, int w)const;        // ���ر�(v,w)��Ȩֵ
    int getMark(int v)const;              // ���ؽ��v�ı��״��
    void setMark(int v, int val);         // ������v���Ϊval
    void subOneInDegree(int v);           // ����V���ڵĵ���ȼ�һ
    int* getAllIndegree();                // ���ش洢��ȵ�����
};

// ���캯�� ���� ��ʼ������������̬����ռ�
Graph::Graph(int n)
{
    numVertex = n;
    numEdge = 0;

    // �������
    mark = new int[numVertex];
    for (int i = 0; i < numVertex; i++)
        mark[i] = 0;
   
    // �ڽӾ���
    matrix = new int* [numVertex];
    for (int i = 0; i < numVertex; i++)
        matrix[i] = new int[numVertex];
    
    // �ڽӾ����ʼ��Ϊ0
    for (int i = 0; i < numVertex; i++)
        for (int j = 0; j < numVertex; j++)
            matrix[i][j] = 0;
       
    // ��������ʼ��
    inDegree = new int[numVertex];
    for (int i = 0; i < numVertex; i++)
        inDegree[i] = 0;
   
}

// �������� ���� ��������ռ�
Graph::~Graph()
{
    delete mark;
    for (int i = 0; i < numVertex; i++)
        delete matrix[i];
   
    delete matrix;
    delete inDegree;
}

// ���ض�����
int Graph::Vnum()const
{
    return numVertex;
}

// ���ر���
int Graph::Enum()const
{
    return numEdge;
}

// ���ض���v���ڽӶ���
int Graph::first(int v)const
{
    for (int i = 0; i < numVertex; i++)
    {
        if (0 != matrix[v][i])
        {
            return i;
        }
    }

    return numVertex;
}

// ���ؽ��v���ڵ���һ������
int Graph::next(int v, int w)const
{
    for (int i = w + 1; i < numVertex; i++)
    {
        if (0 != matrix[v][w])
        {
            return i;
        }
    }

    return numVertex;
}

// ��ӱߣ�v,w����ȨֵΪwgt
void Graph::setEdge(int v, int w, int wgt)
{
    if (wgt < 0)
    {
        std::cout << "Ȩֵ����Ϊ0";
    }

    if (0 == matrix[v][w])
    {
        numEdge++;        // ������1
        inDegree[w]++;    // w������ȼ�1
    }

    matrix[v][w] = wgt;
}

// ɾ���ߣ�v,w��
void Graph::deletEdge(int v, int w)
{
    if (0 != matrix[v][w])
    {
        numEdge--;       // ������1
        inDegree[w]--;   // w������ȼ�1��
        matrix[v][w] = 0;
    }
}

// ���ر�(v,w)��Ȩֵ
int Graph::weight(int v, int w)const
{
    return matrix[v][w];
}

// ���ض���v�ı��״��
int Graph::getMark(int v)const
{
    if (v<0 || v>numVertex)
    {
        std::cout << "�������Ч";
    }
    return mark[v];
}

// ������v���Ϊval
void Graph::setMark(int v, int val)
{
    if (v<0 || v>numVertex)
    {
        std::cout << "�������Ч";
    }

    mark[v] = val;
}

// ���붥��v���ڽӵĶ������ȼ�1
void Graph::subOneInDegree(int v)
{
    for (int i = 0; i < numVertex; i++)
    {
        if (0 != matrix[v][i])
        {
            inDegree[i]--;
        }
    }
}

// ���������Ϣ����
int* Graph::getAllIndegree()
{
    return inDegree;
}



/*================================================== �γ��� ============================================*/
//�洢�γ���Ϣ
class Course
{
private:
    string code;               // �γ̱��
    string name;               // �γ�����
    short studyTime;           // ѧʱ
    short term;                // ѧ��
    vector<string> condition;  // ���޿γ�

    bool isLimit;              //�Ƿ������޿γ�

public:
    // ���졢��������
    Course(string code, string name, short studyTime, short term);
    Course() {}
    ~Course() {}

    //�γ̱��
    void setCode(string code);
    string getCode();

    //�γ�����
    void setName(string mname);
    string getName();

    //�γ�ѧʱ
    void setStudyTime(short mstudyTime);
    short getStudyTime();

    //�γ̿�ʼѧ��
    void setTerm(short mterm);
    short getTerm();

    // ���޿γ�
    void addCondition(string code);
    vector<string> getCondition();

    // �Ƿ������޿γ�
    bool IsLimit();   
};


// ���캯�� ���� ��ʼ���γ���Ϣ
Course::Course(string mcode, string mname, short mstudyTime, short mterm)
{
    isLimit = false;
    code = mcode;
    name = mname;
    studyTime = mstudyTime;
    term = mterm;
}

// �γ̱��
void Course::setCode(string mcode)
{
    code = mcode;
}

string Course::getCode()
{
    return code;
}

// �γ�����
void Course::setName(string mname)
{
    name = mname;
}

string Course::getName()
{
    return name;
}

// �γ�ѧʱ
void Course::setStudyTime(short mstudyTime)
{
    studyTime = mstudyTime;
}

short Course::getStudyTime()
{
    return studyTime;
}

// �γ�ѧ��
void Course::setTerm(short mterm)
{
    term = mterm;
}

short Course::getTerm()
{
    return term;
}

// ���޿γ�
void Course::addCondition(string code)
{
    isLimit = true;
    condition.push_back(code);
}

vector<string> Course::getCondition()
{
    return condition;
}

// �Ƿ������޿γ�
bool Course::IsLimit()
{
    return isLimit;
}






/*====================================== �ſ��� ============================================*/
#define TermNum 8       // ѧ����

class CourseScheduling
{
private:
    /*=== ���ݳ�Ա ===*/
    char course_table[TermNum + 1][11][6][100];   // ÿ�ſγ̵Ŀα��ţ�ѧ�ڡ��ڴΡ����ڡ��γ���
    int numsOfTerm[TermNum];                      // ÿѧ�ڿγ���
    string InFileName;                            // �γ���Ϣ�ļ��� ���� ��
    string OutFileName;                           // �α���Ϣ�ļ��� ���� д
    Queue<int>  q[TermNum + 1];                   // ��Ϊ0�����Ӧ��ѧ�ڶ���

    /*==== �������� ==== */
    // ���ļ�
    int readFile(fstream& in, int* nums, Course* courses);
    // ��ʼ���γ���Ϣ ���� ���ؿγ���Ŀ
    int GetAllCourseFromFile(Course* courses, string fileName, int* nums);

    // ����ͼ
    void CreateGraph(Graph& gra, Course* courses, int numOfCourses);

    // ��������
    bool TopologicalOrder(Graph& gra, Course* courses);
    // �������������� ���� �����Ϊ0�Ķ������Ӧ�Ķ���
    void zero_indgree_push(Graph& gra, Course* courses);
 
    //  �ſ�
    bool range(int num, int term, char* name);
    // �ſθ������� ���� �ŵ�һ���������ڿ�
    bool range_one(int& week_day, int term, char* course_name);
    bool range_two(int& week_day, int term, char* course_name);
    bool range_three(int& week_day, int term, char* course_name);
    // ���ҿտΣ������ص�һ�ڿεĽڴ�
    int find_one(int week_day, int term);
    int find_two(int week_day, int term);
    int find_three(int week_day, int term);


public:
    void Interface();                           // ��ʼ��ϵͳ����
    void ReadInFileName(string fileName);       // ��ȡ�γ���Ϣ�ļ���
    bool CreateCourseTable();                   // �����α�
    void ReadOutFileName(string fileName);      // ��ȡ�α��ļ���
    void PrintCourseTable();                    // ����α�
};


// ���ļ�
int CourseScheduling::readFile(fstream& in, int* nums, Course* courses)
{
    while (1)
    {
        cout << "�γ�����Ϊ38,������˸�ѧ�ڵĿγ̷ֲ����ո��������";
        int total = 0;
        for (int i = 0; i < 8; i++)
        {
            cin >> nums[i];
            total += nums[i];
        }

        if (total == 38)
            break;
        else
            cout << "\n�γ̷ֲ��������������룺 ";
    }
   
    int count = 0;
    char* chstemp = new char[50];
    char temp;
    short numtemp;
    while (!in.eof())
    {
        in >> chstemp;
        // �ļ�ĩβΪ�ո�
        if (in.eof())
        {
            break;
        }
        courses[count].setCode(chstemp);
        in >> chstemp;
        courses[count].setName(chstemp);
        in >> numtemp;
        courses[count].setStudyTime(numtemp);
        in >> numtemp;
        courses[count].setTerm(numtemp);

        while ('\n' != (temp = in.get()))
        {
            if (' ' != temp && '\t' != temp)
            {
                in.putback(temp);
                in >> chstemp;
                courses[count].addCondition(chstemp);
            }
        }
        count++;
    }

    //�ͷſռ�
    delete [] chstemp;

    return count;
}


//���ļ��ж�ȡ��Ϣ����������Course����,���ض�ȡ�Ŀγ�����
int CourseScheduling::GetAllCourseFromFile(Course* courses, string fileName, int* nums)
{
    fstream tempInFile(fileName, ios::in);
    if (!tempInFile)
    {
        cout << "In���ļ�ʧ�ܣ�" << fileName.data();
        return -1;
    }
    int numberOfCourse;
    numberOfCourse = readFile(tempInFile, nums, courses);
    tempInFile.close();

    return numberOfCourse;
}


// ��ʼ������
void CourseScheduling::Interface()
{
    cout << "******************************************************\n";
    cout << "**                                                  **\n";
    cout << "**                ���ѧԺ�ſ�ϵͳ                  **\n";
    cout << "**                                                  **\n";
    cout << "**                      8��ѧ��38�ڿ�������ѡ����   **\n";
    cout << "**                                                  **\n";
    cout << "******************************************************\n\n";
}

// ��ȡ�γ���Ϣ�ļ���
void CourseScheduling::ReadInFileName(string fileName)
{
    InFileName = fileName;
}

// ��ȡ�α��ļ�����
void CourseScheduling::ReadOutFileName(string fileName)
{
    OutFileName = fileName;
}


// ����ͼ
void CourseScheduling::CreateGraph(Graph& gra, Course* courses, int numOfCourses)
{
    vector<string> conditions;
    for (int i = 0; i < numOfCourses; i++)
    {
        if (courses[i].IsLimit())
        {
            conditions = courses[i].getCondition();
            for (int j = 0; j < (int)conditions.size(); j++)
            {
                for (int k = 0; k < numOfCourses; k++)
                {
                    if (courses[k].getCode() == conditions.at(j))
                    {
                        gra.setEdge(k, i, 1);
                        break;
                    }
                }
            }
        }
    }

    return;
}

// ��������
bool CourseScheduling::TopologicalOrder(Graph& gra, Course* courses)
{

    zero_indgree_push(gra, courses);
    //��term�ж�Ӧ�Ŀγ��ſ�
    int v;
    int size;
    Course course;
    char name[100];
    for (int term = 1; term <= TermNum; term++)
    {
        size = (int)q[term].Size();
        for (int i = 0; i < size; i++)
        {
            v = q[term].Front();
            q[term].Pop();
            //�ſ�
            course = courses[v];
            strncpy(name, course.getName().data(), 99);
            range(course.getStudyTime(), term, name);

            //����Խv���ڵĶ�����ȼ�һ
            gra.subOneInDegree(v);

            //���
            int* inDegrees = gra.getAllIndegree();
            for (int j = 0; j < gra.Vnum(); j++)
            {
                if (0 == inDegrees[j] && (0 == courses[j].getTerm() || courses[j].getTerm() > term) && 0 == gra.getMark(j))
                {
                    q[courses[j].getTerm()].Push(j);
                    gra.setMark(j, 1);//����Ѿ�����
                }
                else if (0 == inDegrees[j] && (courses[j].getTerm() > 0 && courses[j].getTerm() <= term) && 0 == gra.getMark(j))
                {
                    cout << "�γ̳�ͻ���ſν�����" << endl;
                    return false;;
                }
              
            }

        }

        for (int i = 0; i < numsOfTerm[term - 1] - size; i++)
        {
            v = q[0].Front();
            q[0].Pop();
            //�ſ�
            course = courses[v];
            strncpy(name, course.getName().data(), 99);
            range(course.getStudyTime(), term, name);
            // ����Խv���ڵĶ�����ȼ�һ
            gra.subOneInDegree(v);

            //���
            int* inDegrees = gra.getAllIndegree();
            for (int j = 0; j < gra.Vnum(); j++)
            {
                if (0 == inDegrees[j] && (0 == courses[j].getTerm() || courses[j].getTerm() > term) && 0 == gra.getMark(j))
                {
                    q[courses[j].getTerm()].Push(j);
                    gra.setMark(j, 1);//����Ѿ�����
                }
                else if (0 == inDegrees[j] && (0 < courses[j].getTerm() && courses[j].getTerm() <= term) && 0 == gra.getMark(j))
                {
                    cout << "�γ̳�ͻ���ſν�����" << endl;
                    return false;
                }
            }

        }
    }

    for (int i = 0; i < gra.Vnum(); i++)
    {
        if (0 == gra.getMark(i))
        {
            cout << "��δ�������пγ̣��ſ�ʧ�ܣ�";
            return false;
        }
    }

    return true;
}


void CourseScheduling::zero_indgree_push(Graph& gra, Course* courses)
{
    int* inDegrees = gra.getAllIndegree();
    // ����Ϊ0�ĵ����Ӧ�Ķ���
    for (int i = 0; i < gra.Vnum(); i++)
    {
        if (0 == inDegrees[i])
        {
            q[courses[i].getTerm()].Push(i);
            gra.setMark(i, 1);// ����Ѿ�����
        }
    }
}

// �ſ�
bool CourseScheduling::range(int num, int term, char* name)
{
    int static week_day = 1;

    if (num == 1)
    {
        if (range_one(week_day, term, name) == false)
        {
            return false;
        }
        else
        {
            week_day = (week_day + 2 -5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
            return true;
        }
    }
    else if (num % 3 == 0)
    {
        for (int i = 0; i < num / 3; i++)
        {
            if (range_three(week_day, term, name) == false)
            {
                return false;
            }
            else
            {
                week_day = (week_day + 2 - 5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
                return true;
            }
        }
    }
    else if (num % 2 == 0)
    {
        for (int i = 0; i < num / 2; i++)
        {
            if (range_two(week_day, term, name) == false)
            {
                return false;
            }
            else
            {
                week_day = (week_day + 2 - 5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
                return true;
            }
        }
    }
    else if (5 == num)
    {
        if (range_three(week_day, term, name) == false)
        {
            return false;
        }
        else
        {
            week_day = (week_day + 2 - 5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
            if (range_two(week_day, term, name) == false)
            {
                return false;
            }
            else
            {
                week_day = (week_day + 2 - 5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
                return true;
            }
        }
    }
    return false;
}


// �����ſΣ���һ�ڿ�
bool CourseScheduling::range_one(int& week_day, int term, char* course_name)
{
    int local;
    for (int i = 0; i < 5; i++)
    {
        local = find_one(week_day, term);
        if (-1 == local)
        {
            week_day = (week_day + 2 - 5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
        }
        else
        {
            strcpy(course_table[term][local][week_day], course_name);
            return true;
        }
    }
    return false;
}


// �����ſΣ������ڿ�
bool CourseScheduling::range_two(int& week_day, int term, char* course_name)
{
    int local;
    for (int i = 0; i < 5; i++)
    {
        local = find_two(week_day, term);
        if (-1 == local)
        {
            week_day = (week_day + 2 - 5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
        }
        else
        {
            strcpy(course_table[term][local][week_day], course_name);
            strcpy(course_table[term][local + 1][week_day], course_name);
            return true;
        }
    }
    return false;

}

// �����ſΣ������ڿ�
bool CourseScheduling::range_three(int& week_day, int term, char* course_name)
{
    int local;
    for (int i = 0; i < 5; i++)
    {
        local = find_three(week_day, term);
        if (-1 == local)
        {
             week_day = (week_day + 2 -5) > 0 ? (week_day + 2 - 5) : (week_day + 2);
        }
        else
        {
            strcpy(course_table[term][local][week_day], course_name);
            strcpy(course_table[term][local + 1][week_day], course_name);
            strcpy(course_table[term][local + 2][week_day], course_name);
            return true;
        }
    }
    return false;
}

// ����һ�ڿտΣ������ص�һ�ڿεĽڴ�
int CourseScheduling::find_one(int week_day, int term)
{
    for (int i = 1; i <= 10; i++)
    {
        if (strlen(course_table[term][i][week_day]) == 0)
        {
            return i;
        }

    }
    return -1;
}

// �������ڿտΣ������ص�һ�ڿεĽڴ�
int CourseScheduling::find_two(int week_day, int term)
{
    if (strlen(course_table[term][1][week_day]) == 0 && strlen(course_table[term][2][week_day]) == 0)
    {
        return 1;
    }
    if (strlen(course_table[term][6][week_day]) == 0 && strlen(course_table[term][7][week_day]) == 0)
    {
        return 6;
    }
    if (strlen(course_table[term][3][week_day]) == 0 && strlen(course_table[term][4][week_day]) == 0)
    {
        return 3;
    }
    if (strlen(course_table[term][4][week_day]) == 0 && strlen(course_table[term][5][week_day]) == 0)
    {
        return 4;
    }
    if (strlen(course_table[term][8][week_day]) == 0 && strlen(course_table[term][9][week_day]) == 0)
    {
        return 8;
    }
    if (strlen(course_table[term][9][week_day]) == 0 && strlen(course_table[term][10][week_day]) == 0)
    {
        return 9;
    }
    return -1;
}

// �������ڿտΣ������ص�һ�ڿεĽڴ�
int CourseScheduling::find_three(int week_day, int term)
{
    if (strlen(course_table[term][3][week_day]) == 0 && strlen(course_table[term][4][week_day]) == 0 &&
        strlen(course_table[term][5][week_day]) == 0)
    {
        return 3;
    }
    if (strlen(course_table[term][8][week_day]) == 0 && strlen(course_table[term][9][week_day]) == 0 &&
        strlen(course_table[term][10][week_day]) == 0)
    {
        return 8;
    }
    return -1;
}

// �����α�
bool CourseScheduling::CreateCourseTable()
{
    Course* temp = new Course[100];
    int allCourse;
    allCourse = GetAllCourseFromFile(temp, InFileName, numsOfTerm);
    if (allCourse < 0)
    {
        return false;
    }

    // ��ͼ
    Graph gra(allCourse);
    CreateGraph(gra, temp, allCourse);

    // ��տα�
    for (int i = 1; i <= TermNum; i++)                       //ѧ����
        for (int j = 1; j <= 10; j++)                        //�ڴ�
            for (int k = 1; k <= 5; k++)                     //����   
                strcpy(course_table[i][j][k], "");

    // ��������
    if (!TopologicalOrder(gra, temp))
    {
        //�ͷſռ�
        delete[]temp;
        return false;
    }

    delete[] temp;
    return true;
}


// ����α��ļ���
void CourseScheduling::PrintCourseTable()
{
    fstream outToFile(OutFileName, ios::out);
    if (!outToFile)
    {
        cout << "���ļ�ʧ��!" << endl;
        return;
    }

    for (int i = 1; i <= 8; i++)
    {

        outToFile << '\t' << '\t' << '\t' << '\t' << "�������רҵ��" << i << "ѧ�ڿα�" << endl;
        outToFile << endl;
        outToFile << setw(20) << "����";
        outToFile << setw(20) << "����һ";
        outToFile << setw(20) << "���ڶ�";
        outToFile << setw(20) << "������";
        outToFile << setw(20) << "������";
        outToFile << setw(20) << "������";
        outToFile << endl;
        for (int j = 1; j <= 10; j++)
        {
            outToFile << setw(20) << "��" << j << "��";
            for (int k = 1; k <= 5; k++)
            {
                outToFile << setw(20) << course_table[i][j][k];
            }
            outToFile << endl;
            outToFile << endl;
        }

        outToFile << endl;
        outToFile << endl;
        outToFile << endl;
        outToFile << endl;
        outToFile << endl;
        outToFile << endl;
        outToFile << endl;
    }
    outToFile.close();
}



/*======================================== ������ ====================================*/
int main()
{
    
    CourseScheduling CS;    // �α�ϵͳ
    string fileName;        //�ļ���

    // ��ʼ��ϵͳ����
    CS.Interface();

    // ����������Ϣ
    cout << "����������Ϣ�� \n";
    cout << "1.�γ���Ϣ�ļ����� courseInformation.txt  \n";
    cout << "2.�α��ļ������������� .txt�ļ���\n";
    cout << "3.�뱣֤8ѧ�ڿγ���֮�͵��ڿγ�������\n\n";

    // ��ȡ�γ���Ϣ
    cout << "�����������Ŀγ���Ϣ�ļ����� ";
    cin >> fileName;
    CS.ReadInFileName(fileName);

    while (1)
    {
        // �����α�
        if (CS.CreateCourseTable())
            cout << "�ſγɹ�����ָ���α����ļ��� \n";
        else
            cout << "�ſ�ʧ�ܣ�\n";

        // �α����ļ���
        cin >> fileName;
        CS.ReadOutFileName(fileName);

        // ����α�
        CS.PrintCourseTable();
        cout << "�����ϣ�\n\n";

        cout << "�����ſΣ�( y or n)";
        char tag = 'y';
        cin >> tag;
        if (tag == 'n')
            break;
    }

    cout << "ллʹ�ã�ף��ÿ�쿪�ģ�����Bye~~\n\n";
    system("pause");   // ����.exe�ļ��˳�ǰ��ʾ��Ϣ
    return 0;
}

/*====================================== ENDING ===================================================*/
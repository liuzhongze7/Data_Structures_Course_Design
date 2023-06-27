/*
* FileName: MathOperator.cpp
* Function: Evaluate the calculation expression (+,-,*,/,^,%)
* Author: ���ַ�
* StuNumber: 1951976
* Date: 2020.12.9
*/


// ���ȼ���
/***************************** Precedure of operator *******************************************/
/*                                   Precedure                                                 */
/*    Symbol                  Input Precedure               Stack Precedure             Rank   */
/*     ^ %                                                                                     */
/*     + -                                                                                     */
/*    + - (binary)                    1                            1                      -1   */
/*    / *                             2                            2                      -1   */
/*    (                               3                            -1                      0   */
/*    )                               0                             0                      0   */


#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;


// ��������
#define OperatorExpected 0
#define OperandExpected  1
#define MissingLeftParenthesis 2
#define MissingRightParenthesis 3
#define InvalidInput 4
#define leftparenthesis '('
#define rightparenthesis ')'



/*================================= ջģ���� =====================================*/
// stack node
template <class Type>
struct Node
{
    Type data;
    Node<Type>* link = NULL;
    Node<Type>(Type x) : data(x) {}
    Node<Type>(Type x, Node<Type>* next = NULL) : data(x), link(next) {}
};

// template satck
template <class Type>
class Stack
{
private:
    Node<Type>* top;           // ջ��ָ��

public:
    Stack() :top(NULL) {};    // ���캯��
    ~Stack();                 // ��������

    void Push(const Type& x); // ��ջ   
    Type Pop();               // ��ջ
    Type Top() const;         // ����ջ��Ԫ��
    // �п�
    bool Empty() const { return top == NULL ? true : false; }  
    int Size() const;         // ����
};

// �������� ���� �ͷſռ�
template<class Type>
Stack<Type>::~Stack()
{
    Node<Type>* q;
    while (top)
    {
        q = top;
        top = top->link;
        delete q;
    }
}

// ��ջ
template<class Type>
void Stack<Type>::Push(const Type& x)
{
    top = new Node<Type>(x, top);
    if (top == NULL) 
    {
        cout << "The allocation of space failed!" << endl;
        exit(1);
    }
}

// ��ջ
template<class Type>
Type Stack<Type>::Pop()
{
    if (top == NULL)
    {
        cerr << "Attempt to pop an empty stack!" << endl;
        exit(1);
    }

    // ��¼ջ��Ԫ��ֵ
    Type x = top->data;

    // ɾ��ջ��
    Node<Type>* q = top;
    top = top->link;
    delete q;
    return x;
}


// ����ջ��Ԫ��
template<class Type>
Type Stack<Type>::Top() const
{
    return top->data;
}

// ����ջ����
template<class Type>
int Stack<Type>::Size() const
{
    Node<Type>* p = top;
    int length = 0;
    while (p)
    {
        length++;
        p = p->link;
    }
    return length;
}



/*===================================== ������ ===================================*/
class MathOperator 
{
private:
    char op;                   // �����
    int inputprecedence;       // ��ջ���ȼ�
    int stackprecedence;       // ��ջ���ȼ�

public:
    // ���졢��������
    MathOperator() {}
    MathOperator(char ch);
    ~MathOperator() {}

    // ���� >=
    int operator>= (MathOperator a) const;
    // ����
    void Evaluate(Stack<float> & operandStack);
    // ȡ�����
    char GetOp();
};


// ���캯�� ���� �������ֵ�����ȼ���ʼ��
MathOperator::MathOperator(char ch) 
{
    op = ch; 
    switch (op)
    {
        // '+' and '-' have input/stack preceedence 1
    case '+':
    case '-':   inputprecedence = 1;
                stackprecedence = 1;
                break;

        // '*' and '/' have input/stack precedence 2
    case '^':
    case '%':
    case '*':
    case '/':   inputprecedence = 2;
                stackprecedence = 2;
                break;

        // '(' has input precedence 3, stack precedence -1
    case '(':   inputprecedence = 3;
                stackprecedence = -1;
                break;

        // ')' has input/stack precedence 0
    case ')':   inputprecedence = 0;
                stackprecedence = 0;
                break;
    }
}

// ���� >=
int MathOperator::operator>= (MathOperator a) const
{
    return stackprecedence >= a.inputprecedence;
}


// ���� ���� ȡջ����Ԫ�ظ��ݲ��������㣬�����ջ
void MathOperator::Evaluate(Stack<float>& operandStack)
{
    float operand1 = operandStack.Pop(); // �Ҳ�����
    float operand2 = operandStack.Pop(); // �������

    // �������������Ӧ�ļ���
    switch (op) 
    {
    case '+':   operandStack.Push(operand2 + operand1);
                break;

    case '-':   operandStack.Push(operand2 - operand1);
                break;

    case '*':   operandStack.Push(operand2 * operand1);
                break;

    case '/':   operandStack.Push(operand2 / operand1);
                break;

    case '%':   operandStack.Push(int(operand2) % int(operand1));
                break;

    case '^':   operandStack.Push(pow(operand2, operand1));
    }
}

// ���������
char MathOperator::GetOp()
{
    return op;
}


/****************************************** Main Function***********************************************/
// ��������
// �ж���������������������
int isoperator(char ch) 
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == '^' || ch == '%')
        return 1;
    else
        return 0;
}

// �жϿո�
int iswhitespace(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return 1;
    else
        return 0;
}

// ������ʾ���� 
void Error(int n)
{
    static char errormsgs[5][30] = {
                    "Operator expected",
                    "Operand expected",
                    "Missing left parenthesis",
                    "Missing right parenthsis",
                    "Invalid input"
    };
    cerr << errormsgs[n] << endl;
    exit(1);
}

// ��ʼ�����溯��
void Interface()
{
    cout << "**************************************************\n";
    cout << "**                                              **\n";
    cout << "**                                              **\n";
    cout << "**                ��������ϵͳ                  **\n";
    cout << "**                                              **\n";
    cout << "**                                              **\n";
    cout << "**                   ֧���������+ - * / . ^ %  **\n";
    cout << "**                   ֧�ָ�����С��������       **\n";
    cout << "**                   ���������������ţ�����     **\n";
    cout << "**                                              **\n";
    cout << "**                                              **\n";
    cout << "**************************************************\n\n";
}


/*====================================== ������ ====================================*/
int main()
{
    Interface();        // ��ʼ������
   
    while (1)
    {
        cout << "\n��������ʽ( = ��ʾ����):\n ";
        // �����ջ
        Stack<MathOperator> OperatorStack;

        // ������ջ
        Stack<float> OperandStack;

        // ������
        MathOperator opr1, opr2;

        int rank = 0;   // ��ȡ���ʽ���ȼ������������������ƥ�䣬������ӦΪ1
        float number;   // ���������
        char ch;        // ���ζ�����ʽ

        // ������������
        int Flag = 0;   // ��־���ţ�������
        int Num_Add_Sub = 0;      // ��ȡ + - �������жϵ�һ���������Ƿ�Ϊ����
        int Num_operand = 0;      // ��ȡ���ָ���


        // ������ = ��ʱ������
        while (cin.get(ch) && ch != '=')
        {
            // +-���������
            if (ch == '+' || ch == '-')
                Num_Add_Sub++;

            // С���㴦��
            if (isdigit(ch) || ch == '.')
            {
                Flag = 0;
                // ���ʱС�����˻�����
                cin.putback(ch);
                cin >> number;
                Num_operand++;

                // ���������ȼ�Ϊ1
                rank++;
                if (rank > 1)
                    Error(OperatorExpected);
                // ��������ջ
                OperandStack.Push(number);
            }

            // ���������
            else if (isoperator(ch))
            {
                if (ch != '(' && ch != ')' && ch != '=')
                    Flag++;

                // ����-��+�������ſ�ͷ�����
                // ��һ�����������������Ϊ0ʱ���� + �� -�������Ϊ��������
                // �ڶ��������������������-+������������Ϊ��������
                if ((Num_operand == 0 && Num_Add_Sub == 1) || (Flag == 2 && ch == '-') || (Flag == 2 && ch == '+'))
                {
                    cin.putback(ch);
                    cin >> number;

                    // ������������1
                    Num_operand++;
                    // ���������ȼ�Ϊ1
                    rank++;
                    if (rank > 1)
                        Error(OperatorExpected);
                    // ��������ջ
                    OperandStack.Push(number);
                    Flag = 0;
                }

                else
                {
                    // �� ���ȼ�Ϊ0
                    if (ch != '(')
                        rank--;
                    if (rank < 0)
                        Error(OperandExpected);


                    // �����ȼ��ж������ջ�Ľ�ջ���ջ
                    opr1 = MathOperator(ch);
                    while (!OperatorStack.Empty() && (opr2 = OperatorStack.Top()) >= opr1)
                    {
                        opr2 = OperatorStack.Pop();
                        opr2.Evaluate(OperandStack);
                    }
                    OperatorStack.Push(opr1);
                }
            }

            // �����Ŵ���
            else if (ch == rightparenthesis)
            {
                opr1 = MathOperator(ch);
                while (!OperatorStack.Empty() && (opr2 = OperatorStack.Top()) >= opr1) {
                    opr2 = OperatorStack.Pop();
                    opr2.Evaluate(OperandStack);
                }
                if (OperatorStack.Empty())
                    Error(MissingLeftParenthesis);
                opr2 = OperatorStack.Pop(); // �����ų�ջ
            }

            // ���������
            else if (!iswhitespace(ch))
                Error(InvalidInput);
        }



        // ���ʽ��ȡ����ʽ���ȼ�ӦΪ1�����������ƥ�����
        if (rank != 1)
            Error(OperandExpected);

        // �ж������ջ�������ջ�Ƿ�Ϊ�գ�����ʾ��Ӧ�Ĵ���
        while (!OperatorStack.Empty())
        {
            opr1 = OperatorStack.Pop();
            if (opr1.GetOp() == leftparenthesis)
                Error(MissingRightParenthesis);
            opr1.Evaluate(OperandStack);
        }

        // ������
        cout << "The value is " << OperandStack.Pop() << endl;

        // ���������ж�
        cout << "\n����ո������������ n �˳��� ";
        if (getchar() == 'n')
        {
            break;
        }
    }

    system("pause"); // �������ʱ.exe�ļ���ʾ������Ϣ
    return  0;
 }
#pragma once
#include<iostream>
#include<cmath>
using namespace std;
class divideByZero :public exception                      //�쳣�ദ����ĸΪ0
{
public:
	const char* what()const throw()
	{
		return "ERROR! DIVIDE BY ZERO.\n";
	}
};
class wrongExpression :public exception                   //�쳣�ദ���ַ������ʽ����
{
public:
	const char* what()const throw()
	{
		return "ERROR! BAD EXPRESSION.\n";
	}
};
class outOfRange :public exception                        //ջΪ��ȡԪ�ر���
{
public:
	const char* what()const throw()
	{
		return "ERROR! OUT OF RANGE.\n";
	}
};
template<class T>
class stack
{
public: 
	stack() {};                                   //���캯��
	virtual bool Push(const T& x) = 0;            //��Ԫ�ؽ�ջ
	virtual T Get_top() = 0;                      //ջ��Ԫ�س�ջ
	virtual T Read_top() const= 0;                //��ȡջ��Ԫ��
	virtual bool Empty()const = 0;                //�ж�ջ�Ƿ�Ϊ��
	//virtual int Get_size()const = 0;            //����ջ�е�Ԫ�ظ���
};
template<class T>
class Linked_stack:public stack<T>
{
public:
	Linked_stack() :top(NULL) {};           //���캯����ջ��ָ���ÿ�
	~Linked_stack() { Make_empty();};       //��������,��ջ�����ݶ�����
	bool Push(const T& x);                  //��ջ
	T Get_top();                            //��ջ
	T Read_top()const;                      //��ȡջ��Ԫ��
	bool Empty()const;                      //�ж�ջ�Ƿ��
	void Make_empty();                      //��ջ�ÿ�
private:
	struct Link_node                        //������а���һ�������Լ���һ���ĵ�ַ
	{
		T data;
		Link_node* link;
	};
	Link_node* top;                         //ջ��ָ��
};
template<class T>
bool Linked_stack<T>::Push(const T& x)            //��ջ����
{
	Link_node* p;
	p = new Link_node;                            
	if (p == NULL)                                //����ʧ��
	{
		exit(1);
		cout << "����ʧ��" << endl;
		return false;
	}
	else                                          //�����µĺ�x�Ľ��
	{
		p->data = x;
		p->link = top;
		top = p;
		return true;
	}
}
template<class T>
T Linked_stack<T>::Get_top()                   //��ջ����
{
	T x;
	if (Empty() == true)                       //�ж�ջ�Ƿ�Ϊ��
	{
		throw outOfRange();
	}
	else                                       //ջ��Ϊ��
	{
		Link_node* p = top;                    //p�ݴ�ջ��Ԫ��
		top = top->link;                       //�ı�topָ��
		x = p->data;                           //��p��ջ������ֵ���
		delete p;                              //���ջ��Ԫ��
		return x;
	}
}
template<class T>
T Linked_stack<T>::Read_top()const             //��ȡջ�����������ı�����ֵ
{
	T x;
	if (Empty() == true)                       //�ж�ջ�Ƿ�Ϊ��
	{
		throw outOfRange();
	}
	else                                       //��Ϊ�ն�ȡջ��Ԫ��
	{
		x = top->data;
		return x;
	}
}
template<class T>
bool Linked_stack<T>::Empty()const         //�ж�ջ�Ƿ�Ϊ��
{
	if (top == NULL)                       //�ж�ջ�Ƿ�Ϊ��
	{
		return true;
	}
	else
	{
		return false;
	}
}
template<class T>
void Linked_stack<T>::Make_empty()         //��ջ�ÿ�
{
	Link_node* p;                       
	while (top != NULL)                    //ͷָ�벻Ϊ��ʱ�������ƣ�ɾ��ջ��Ԫ�� 
	{
		p = top;
		top = top->link;
		delete p;
	}
}
class calculator
{
private:
	Linked_stack<char>optr;                                  //�����ջ
	Linked_stack<int>opnd;                                   //������ջ
public:
	calculator() {};                                         //���캯��
	~calculator() {};                                        //��������
	int prior_in_stack(char item);                           //����ջ����������ȼ�
	int prior_out_stack(char ch);                            //����ջ����������ȼ�
	int precede(char item, char ch);                         //�Ƚ�ջ������������ȼ�
	int operate(int a, int b, char sign);                    //a,b����sign����
	int calculator_number();                                 //������ʽ��ֵ
};
int calculator::prior_in_stack(char item)
{
	int prior_in=0;
	switch (item)                           //����ջ���������ͬ�����ȼ�
	{
	case'=':
	{
		prior_in = 0;
		break;
	}
	case'+':
	case'-':
	{
		prior_in = 3;
		break;
	}
	case'*':
	case'/':
	{
		prior_in = 5;
		break;
	}
	case'%':
	{
		prior_in = 7;
		break;
	}
	case'^':
	{
		prior_in = 9;
		break;
	}
	case'(':
	{
		prior_in = 1;
		break;
	}
	case')':
	{
		prior_in = 10;
		break;
	}
	}
	return prior_in;
}
int calculator::prior_out_stack(char ch)               //����ջ���������ͬ�����ȼ�
{
	int prior_out=0;
	switch (ch)
	{
		case'=':
		{
			prior_out = 0;
			break;
		}
		case'+':
		case'-':
		{
			prior_out = 2;
			break;
		}
		case'*':
		case'/':
		{
			prior_out = 4;
			break;
		}
		case'%':
		{
			prior_out = 6;
			break;
		}
		case'^':
		{
			prior_out = 8;
			break;
		}
		case'(':
		{
			prior_out = 10;
			break;
		}
		case')':
		{
			prior_out = 1;
			break;
		}
		default:
		{
			throw wrongExpression();
			break;
		}
		}
	return prior_out;
}
int calculator::precede(char item, char ch)
{
	if (prior_in_stack(item) < prior_out_stack(ch))               //ջ����������ȼ���
	{
		return -1;
	}
	else if (prior_in_stack(item) == prior_out_stack(ch))         //ջ������������ȼ���ͬ
	{
		return 0;
	}
	else                                                          //ջ����������ȼ���
	{
		return 1;
	}
}
int calculator::operate(int a, int b, char sign)
{
	int result=0;                              //������������������
	switch (sign)
	{
	case'+':
	{
		result = a + b;
		break;
	}
	case'-':
	{
		result = a - b;
		break;
	}
	case'*':
	{
		result = a * b;
		break;
	}
	case'/':
	{
		if (b == 0)
		{
			throw divideByZero();
		}
		result = a / b;
		break;
	}
	case'%':
	{
		result = a % b;
		break;
	}
	case'^':
	{
		result = pow(a,b);
		break;
	}
	}
	return result;
}
int calculator::calculator_number()                                                   //������ʽ��ֵ
{
	int number=0,a=0,b=0,operate_number,look=0;
	char item, ch=NULL,sign,judge_sign=NULL;
	optr.Make_empty();                                                                //���ַ�ջ������ջ�ÿ�
	opnd.Make_empty();
	optr.Push('=');                                                                   //�ַ�ջ����=
	while ((ch = getchar()) != '\n')                                                  //������ȡ��ֱ�������س�
	{
		if ((judge_sign == NULL||judge_sign=='(') && (ch == '+' || ch == '-'))        //�ж��Ƿ�Ϊ��Ŀ�����
		{
			if (ch == '+')
			{
				look++;                                                               //chΪ+ʱ��¼��
			}
			else
			{
				look = look + 2;                                                      //chΪ-ʱ��¼��
			}
		}
		else
		{
			judge_sign = ch;
			switch (ch)
			{
			case'+':case'-':case'*':case'/':case'%':case'^':case'(':case')':case'=': //��ȡchΪ�����ַ���������в���
			{
				item=optr.Read_top();                                                //���ַ�ջ�����ַ�
				while (precede(item, ch) == 1)                                       //ch���ַ��������ַ��Ƚ������ȼ�ch<item
				{
					sign=optr.Get_top();                                             //���ַ������������ַ�
					b=opnd.Get_top();                                                //��������������
					a=opnd.Get_top();
					opnd.Push(operate(a, b, sign));                                  //�����������
					item = optr.Read_top();                                          //Ϊ����ch��֮���һ����������ȼ��Ƚ�
				}
				if (precede(item, ch) == -1)                                         //ch���ַ��������ַ��Ƚ������ȼ�ch>item
			    {
				optr.Push(ch);                                                       //��chѹ��ջ��
			    }
				else if (precede(item, ch) == 0)                                     //�����Ż��ߵȺŴ�ջ�е���
				{
				item = optr.Get_top();
			    }
				break;
			}
			default:                                                                 //���ַ���Ϊ�����ַ�
			{
				cin.putback(ch);                                                     //�����˻ض�ȡ����
				cin >> operate_number;                                               //��ȡ����
				if (look == 2)                                                       //����Ƿ���Ҫ�����е�Ŀ����
				{
					operate_number = 0 - operate_number;                             //���е�Ŀ����
				}
				look = 0;                                                            //��look����
				opnd.Push(operate_number);                                           //������ѹ��ջ��
				judge_sign = 'R';                                                    //���ж��Ƿ���е�Ŀ�����ǰһ���ַ��û�
				break;
			}
			}
		}
	}
	number=opnd.Get_top();                                                           //�����ջ��ȡ���
	if (optr.Empty()==false)                                                         //����ַ�ջ�л���Ԫ��                                                      
	{
		throw wrongExpression();
	}
	return number;
}



	

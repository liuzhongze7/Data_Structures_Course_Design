#pragma once
#include<string>
#include<fstream>
#include<iomanip>
#include<iostream>
using namespace std;
void MakeSchedule(string Course_Information[38][5], int term_num_course, int arranged_course)
{
	string* Class_Name = new string[term_num_course];
	int* Class_Time = new int[term_num_course];
	ofstream Outfile;
	Outfile.open("�α�(���ź�).txt", ios::app);
	for (int i = 0; i < term_num_course; i++)                                            //��ȡ��ѧ�ڵ�num_of_course�ڿγ���Ϣ
	{	
		Class_Name[i] = Course_Information[arranged_course + i][1];                      //����ĳ�ÿ���ѧʱ������ClassTime*�У��γ�����ClassName*��	
		Class_Time[i] = (int)(Course_Information[arranged_course + i][2][0] - '0');
	}
	string Schedule[4][5];                                                             //���α���ÿ��Ԫ�س�ʼ��Ϊһ���ո����ڽ��������ſα���Ϊ
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 5; j++) 
		{
			Schedule[i][j] = " ";
		}
	}
                                                                     //�ſα�
	for (int i = 0; i < term_num_course; i++)                        //��ѧʱ�Ŀγ̵��ſα���
	{
		int temp = 0;
		if (Class_Time[i] == 3) 
		{
			for (int j = 1; j < 4; j += 2) 
			{
				for (int k = 0; k < 5; k++) 
				{
					if (Schedule[j][k] == " ") 
					{
						Schedule[j][k] = Class_Name[i];
						j = 4;
						k = 5;
					}
				}
			}
		}
		else if (Class_Time[i] == 4)                                 //��ѧʱ�Ŀγ̵��ſα���
		{
			for (int j = 0; j < 4; j += 2)
			{
				for (int k = 0; k < 5; k++) 
				{
					if (Schedule[j][k] == " ") 
					{
						Schedule[j][k] = Class_Name[i];
						temp = k;
						j = 4;
						k = 5;
					}
				}
			}
			if (temp == 0) 
			{
				for (int j = 0; j < 4; j += 2) 
				{
					for (int k = 2; k < 5; k++) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 1) 
			{
				for (int j = 0; j < 4; j += 2) 
				{
					for (int k = 3; k < 5; k++)
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 2) 
			{
				for (int j = 0; j < 4; j += 2) 
				{
					for (int k = 0; k < 5; k += 4) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 3) 
			{
				for (int j = 0; j < 4; j += 2) 
				{
					for (int k = 0; k < 2; k++)
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 4) 
			{
				for (int j = 0; j < 4; j += 2) 
				{
					for (int k = 0; k < 3; k++) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
		}
		else if (Class_Time[i] == 5)                                        //��ѧʱ�Ŀγ̵��ſα���
        {
			for (int j = 0; j < 4; j += 2) 
			{
				for (int k = 0; k < 5; k++) 
				{
					if (Schedule[j][k] == " ")
					{
						Schedule[j][k] = Class_Name[i];
						temp = k;
						j = 4;
						k = 5;
					}
				}
			}
			if (temp == 0) 
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 2; k < 5; k++) 
					{
						if (Schedule[j][k] == " ")
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 1) 
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 3; k < 5; k++) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 2)
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 0; k < 5; k += 4)
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 3) 
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 0; k < 2; k++) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 4) 
			{
				for (int j = 0; j < 4; j += 2) 
				{
					for (int k = 0; k < 3; k++) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
		}
		else if (Class_Time[i] == 6)                                           //��ѧʱ�Ŀγ̵��ſα���
{
			for (int j = 1; j < 4; j += 2)
			{
				for (int k = 0; k < 5; k++) 
				{
					if (Schedule[j][k] == " ") 
					{
						Schedule[j][k] = Class_Name[i];
						temp = k;
						j = 4;
						k = 5;
					}
				}
			}
			if (temp == 0) 
			{
				for (int j = 1; j < 4; j += 2)
				{
					for (int k = 2; k < 5; k++) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 1) 
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 3; k < 5; k++) 
					{
						if (Schedule[j][k] == " ")
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 2) 
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 0; k < 5; k += 4) 
					{
						if (Schedule[j][k] == " ")
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 3)
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 0; k < 2; k++) 
					
					{
						if (Schedule[j][k] == " ") {
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
			else if (temp == 4) 
			{
				for (int j = 1; j < 4; j += 2) 
				{
					for (int k = 0; k < 3; k++) 
					{
						if (Schedule[j][k] == " ") 
						{
							Schedule[j][k] = Class_Name[i];
							j = 4;
							k = 5;
						}
					}
				}
			}
		}
	}	                                                
	for (int i = 0; i < 4; i++)                                         //��Ŀ���ļ��д�ӡĳһѧ�ڵĿα�
	{
		Outfile << "��" << i + 1 << "���";
		for (int j = 0; j < 5; j++) 
		{
			Outfile << setw(20) << Schedule[i][j];
		}
		Outfile << endl;
	}
	delete[]Class_Name;
	delete[]Class_Time;
	Outfile.close();
}
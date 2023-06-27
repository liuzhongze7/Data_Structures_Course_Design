#include<iostream>
#include<fstream>
#include<cstring>
#include<string> 
#include<cstdlib>

using namespace std;

typedef struct Json
{
	bool flag;
	//��ʶ�ǲ���OBJECT 
	string key;
	//�� 
	string value;
	//ֵ 
}json;
//ӳ���ֵ�Ľṹ�� 

fstream file;
int n,m;
json test[10000];
//hashӳ������ 

string nowKey;
string tempKey;
string nowValue;
//�������ڴ����key��value

int flag = 0;
//��ʶ���ڴ������key����value

int hash(char * p)
{
	int x = 1,y;
	string key = p;
	//���ڴ�����ײ
	 
	for(;*p;p++)
	{
		x *= *p;
		x -= *p / 2;
		x %= 10000;
	}
	y = x;
	
	while(test[x].key.size() && !(test[x].key == key.substr(5,1000)))
	//���������ײ���������һλ 
	{
		//cout << "hash(" << test[x].key << "):" << x << endl;
		x++;
		x %= 10000;
		if(x == y)
		{
			cout << "Error hash,memery is out!!!\n";
			exit(0);
		}
		//��ֹ��� 
	}
	//cout << "hash(" << test[x].key << "):" << x << endl;
	
	return x;
}
//hash���� 

void toJson(char * line)
{
	while(*line)
	{
		if(*line == '{')
		//����Ŀ�ʼ 
		{
			if(nowKey.size())
			//�ı丸�ڵ���ַ��� 
			{
				nowKey = tempKey;
				nowKey += '.';
				tempKey = nowKey;
				flag ^= 1;
			}
			else
			//��һ��'{'�ַ����⴦�� 
			{
				nowKey = "json."; 
				tempKey = nowKey;
			}
		}
		else if(*line == '"')
		//�����ַ��� 
		{
			if(!flag)
			//����key 
			{
				line++;
				while(*line != '"')
				{
					if(*line == '\\')
					{
						line++;
					}
					tempKey += *line;
					line++;
				}
				//cout << tempKey << ":";
			}
			else
			//����value 
			{
				line++;
				while(*line != '"')
				{
					if(*line == '\\')
					{
						line++;
					}
					nowValue += *line;
					line++;
				}
				//cout << nowValue << "\n";
			}
		}
		else if(*line == ':' || *line == ',' || *line == '}')
		//ת��ͽ��� 
		{
			flag ^= 1;
			if(*line == ',' || *line == '}')
			//�����ֵӳ�䵽json���� 
			{
				test[hash((char *)tempKey.c_str())].key = tempKey.substr(5,1000);
				if(!nowValue.size())
				{
					test[hash((char *)tempKey.c_str())].value = "OBJECT";
					test[hash((char *)tempKey.c_str())].flag = 1;
				}
				else
				{
					test[hash((char *)tempKey.c_str())].value = nowValue;
					test[hash((char *)tempKey.c_str())].flag = 0;
				}
				//cout << test[hash((char *)tempKey.c_str())].key << ":" << test[hash((char *)tempKey.c_str())].value << endl;
				if(*line == ',')
				{
					tempKey = nowKey;
				}
				nowValue = "";
			}
			if(*line == '}')
			//����һ�������޸ĸ��ڵ��ַ��� 
			{
				flag ^= 1;
				if(nowKey == "json.")
				{
					nowKey = "";
					tempKey = nowKey;
				}
				else
				{
					nowKey = nowKey.substr(0,nowKey.rfind("."));
					tempKey = nowKey;
					//cout << tempKey << endl;
					nowKey = nowKey.substr(0,nowKey.rfind(".") + 1);
					nowValue = "";
					//cout << nowKey << endl;
				}
			}
		}
		
		line++;
	}
	
	return;
}
//���ı���Ϣ�����json�ṹ�� 

void getValue(char * line)
{
	string s = "json.";
	
	s += line;
	
	if(test[hash((char *)s.c_str())].value.size())
	{
		if(!test[hash((char *)s.c_str())].flag)
		{
			cout << "STRING ";
		}
		cout << test[hash((char *)s.c_str())].value << endl;
	}
	else
	{
		cout << "NOTEXIST" << endl;
	}
	
	return;
}
//ͨ��json�ṹ���õ�ǰ��ѯ��value  

int main()
{
	char line[1000];
	file.open("3.txt",ios::in);
	
	file >> n >> m;
	file.getline(line,1000);
	//�������� 
	while(n--)
	{
		file.getline(line,1000);
		//cout << line << endl;
		
		toJson(line);
		//����ǰ�� 
	}
	
	while(m--)
	{
		file.getline(line,1000);
		
		getValue(line);
		//����ǰ��ѯ 
	} 
	
	return 0;
}

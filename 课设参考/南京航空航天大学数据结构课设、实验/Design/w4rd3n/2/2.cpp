#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int N,K,w,s,c;
int key[100001];

typedef struct Action
{
    int num;
    int time;
    int flag;
}action;
//�����Կ�׺ͻ�Կ������������flagΪ0��ʾ�裬flagΪ1��ʾ�� 

vector<action> a;
action temp;

bool cmp(action a,action b){
    if(a.time != b.time)
    //�Ȱ�ʱ���� 
	{
        return a.time < b.time;
    }
	else if(a.flag != b.flag)
	//�Ȼ��ٽ� 
	{
        return a.flag > b.flag;
    }
	else
	//��Ŵ�С���� 
	{
        return a.num < b.num;
    }
}
//���ڱȽϵĺ��� 

int main()
{
    cin >> N >> K;
    
    for(int i = 1;i <= N;i++)
	{
        key[i]=i;
    } 
    //��ʼ��Կ�׵�λ�� 
    
    while(K--)
	{
        cin >> w >> s >> c;
        
        temp.num = w;
        temp.time = s;
        temp.flag = 0;
        a.push_back(temp);
        //��Կ��
        temp.num = w;
        temp.time = s + c;
        temp.flag = 1;
        a.push_back(temp); 
        //��Կ��
    } 
    
    sort(a.begin(),a.end(),cmp);
    //����
    
    for(int i = 0;i < a.size();i++)
	{
        if(a[i].flag == 1)
        //��Կ��
		{
            for(int k = 1;k <= N;k++)
			{
                if(key[k] == 0)
				{
                    key[k] = a[i].num;
                    break;
                }
            }
        }
		else
		//��Կ�� 
		{
            for(int j = 1;j <= N;j++)
			{
                if(key[j] == a[i].num)
				{
                    key[j] = 0;
                    break;
                }
            }
        }
    } 

    for(int i = 1;i <= N;i++)
	{
        cout << key[i] <<" ";
    }
    
    return 0;
}

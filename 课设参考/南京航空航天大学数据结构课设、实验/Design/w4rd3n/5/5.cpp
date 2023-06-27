#include<stdio.h>
#include<stdlib.h>
#define INF 0x7fffffff 

typedef struct Node
{
    long long c;
	//����
    int flag;
	//��ʶ��·�����ͣ�1ΪС����0Ϊ��� 
}node;

FILE * input;
//�ļ�ָ��
 
int n,m;
int t,a,b;
long long c;
//���ڶ�ȡ����ı���

struct Node G[1001][1001];
//�ڽӾ��󴢴��·

long long dd[1001];
long long xd[1001];
long long xd_sq[1001];
//dd��sd�ֱ𱣴�ÿ����㵽������Ĵ��·��֮�ͺ�С��·��֮��,���ֵ�Ϊ����һ��·������ 
long long d[1001];
//���滨�� 

int p[1001];
//��¼����ǰ�����
int flag[1001];
//����Ƿ����

void Dijkstra(int s,int n)
{
	d[s] = 0;
	dd[s] = 0;
	xd[s] = 0;
	//��ʼ�������Ļ���Ϊ0
	
	while(1)
	{
		int x = -1;
        long long min = INF;
        
        for(int i = 1;i <= n;i++)
        {
            if(!flag[i] && d[i] < min)
            //����Ѱ����С���� 
            {
                x = i;
				//��¼��� 
                min = d[i];
				//��¼��ǰ����С��
            }
        }
        
        if(x == -1)
		{
			break;
		}
		flag[x] = 1;
		
		for(int i = 1;i <= n;i++)
		//�����ɳ� 
        {
            if(G[x][i].c != INF && !flag[i])
			//���ڵ�·������һ����û�߹� 
            {
                if(G[x][i].flag == 1)
                //��ǰ��·��С��
                {
                    long long xdnow = INF;
                    //����ǰ����С���Ļ��� 
                    long long ddnow = INF;
                    //����ǰ���ߴ���Ļ��� 
                    
                    if(xd[x] != INF)
					//Դ��㵽x��С�� 
                    {
                        if(p[x] == 0)
                        //û��ǰ����㣬Ҳ���ǲ�û�н��� 
						{
							xdnow = (xd[x] + G[x][i].c) * (xd[x] + G[x][i].c);
						}
                        else
                        //�н��� 
						{
							xdnow = dd[p[x]] + (xd[x] + G[x][i].c) * (xd[x] + G[x][i].c);
						}
                    }
                    
                    if(dd[x] != INF)
					//Դ��㵽x�д��
					{
						ddnow = (G[x][i].c) * (G[x][i].c) + dd[x];
					}
					
                    if(xdnow < ddnow)
                    //ǰ��ѡ����С�� 
                    {
                        xd[i] = xd[i] < (xd[x] + G[x][i].c) ? xd[i] : (xd[x] + G[x][i].c);
                        xd_sq[i] = xdnow < xd_sq[i] ? xdnow : xd_sq[i];
                    }
                    else
                    //ǰ��ѡ���ߴ�� 
                    {
                        xd[i] = xd[i] < G[x][i].c ? xd[i] : G[x][i].c;
                        xd_sq[i] = ddnow < xd_sq[i] ? ddnow : xd_sq[i];
                        
                        p[i] = x;
						//��¼ǰ�����
                    }
                    
                    d[i] = xd_sq[i] < dd[i] ? xd_sq[i] : dd[i];
                    //��¼��С���� 
                }
                else
				//��ǰ��·�Ǵ��
                {
                    long long xdnow = INF;
                    long long ddnow = INF;
                    
                    if(dd[x] != INF)
                    //Դ��㵽x�д��
					{
						xdnow = dd[x] + G[x][i].c;
					}
                    if(xd[x] != INF)
                    //Դ��㵽x��С��
					{
						ddnow = xd_sq[x] + G[x][i].c;
					}
					
                    long long min2;
                    
					min2 = xdnow < ddnow ? xdnow : ddnow;
                    dd[i] = dd[i] < min2 ? dd[i] : min2;
                    d[i] = xd_sq[i] < dd[i] ? xd_sq[i] : dd[i];
                }
            }
        }
	}
	
	return;
} 

int main()
{
	input = fopen("input.txt","r+");
	
	fscanf(input,"%d %d",&n,&m);
	
	for(int i = 0;i <= n;i++)
    {
        for(int j = 0;j <= n;j++)
        {
            G[i][j].c = INF;
            G[j][i].c = INF;
        }
    }
    //��ʼ����·�Ļ���
    
    for(int i = 0;i < 1001;i++)
    {
    	dd[i] = INF;
    	xd[i] = INF;
    	xd_sq[i] = INF;
    	p[i] = 0;
    	d[i] = INF;
	}
	
	while(m--)
	{
		fscanf(input,"%d %d %d %lld",&t,&a,&b,&c);
		//printf("%d %d %d %lld\n",t,a,b,c);
		
		if(t==1)
		//С��
        {
            G[a][b].c = c;
            G[b][a].c = c;
            G[a][b].flag = 1;
            G[b][a].flag = 1;
        }
        else
        //��� 
        {
            G[a][b].c = c;
            G[b][a].c = c;
            G[a][b].flag = 0;
            G[b][a].flag = 0;
        }
	}
	
	Dijkstra(1,n);
	//ʹ��Dijkstra�㷨��Ԫ���·�� 
	
	for(int i = 1;i <= n;i++)
	{
		printf("to %d cost:%d\n",i,d[i]);
	}
	
	fclose(input);
	//�ر��ļ�ָ�� 
	
	return 0;
} 

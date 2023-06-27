/*
[��������]
����С����С����ȥ����棬С�����𿪳���С����������
����С�������ܵĵ�·��Ϊ�����С��������ȽϺ��ߣ�ÿ��1����С��������1��ƣ�Ͷȡ�
	С�������ߣ����������С����С����ƣ��ֵ��������ӣ�������s����С��������s2��ƣ�Ͷȡ�
�������磺��5��·�ڣ�1��·�ڵ�2��·��ΪС����2��·�ڵ�3��·��ΪС����3��·�ڵ�4��·��Ϊ�����
	4��·�ڵ�5��·��ΪС��������·��֮��ľ��붼��2������С����1��·�ڵ�5��·�ڣ�
	����ƣ��ֵΪ(2+2)2+2+22=16+2+4=22��
	����С���õ��˵�ͼ����������滮һ��������·�ߣ�ʹ�ð����·�߿���С����ƣ�Ͷ���С��
[����Ҫ��]
�����ʽ��
��������ĵ�һ�а�����������n, m���ֱ��ʾ·�ڵ������͵�·��������·����1��n��ţ�
	С����Ҫ������1��·�ڵ�n��·�ڡ�
������m��������·��ÿ�а����ĸ�����t, a, b, c����ʾһ������Ϊt������a��b����·�ڣ�����Ϊc�����˫���·��
����tΪ0��ʾ�����tΪ1��ʾС������֤1��·�ں�n��·������ͨ�ġ�
�����ʽ
���һ����������ʾ����·����С����ƣ�Ͷȡ�
��������
6 7
1 1 2 3
1 2 3 2
0 1 3 30
0 3 4 20
0 4 5 30
1 3 5 6
1 5 6 1
�������
76
����˵��
������1��С����2������С����3��ƣ�Ͷ�Ϊ5^2=25��Ȼ���3�ߴ������4����5��ƣ�Ͷ�Ϊ20+30=50������5��С����6��ƣ�Ͷ�Ϊ1���ܹ�Ϊ76��
�γ����Ҫ��
��1��Ҫ����ı��ļ������룻
��2�������ʵ������ݽṹ�洢�����������еĵ�·���γɵ�ͼ�ṹ��
��3����д�������ŵ��㷨�������������С����ɵ�ƣ��ֵ��ָ����������ʾ�����ڵϽ�˹�����㷨���иĽ�������ɱ��⣩��
��4�����ϸ���ĿҪ�����������⣬��Ҫ���������·�ߵ�·�����Լ��ӳ����㵽���������Сƣ��ֵ��
*/
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<stack>

using namespace std;

typedef struct 
{
	char type;
	int weight;
}Arc;

typedef struct 
{
	int pre;	// ���·������һ���� 
	int length;	// ���õ�(�����±�Ϊ��Ӧ��ŵĵ�)����ʼ������·������ 
	bool final;	// �Ƿ�����С·���� 
}Djs;

// ȫ�ֱ��� 
FILE *fp;
char fileName[] = "data.txt";
int n = 0, m = 0;
Arc **graph;
Djs *dj = NULL; 


// ���ļ� 
void fileOpen(char *method) 
{
	
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// �ر��ļ� 
void fileClose() 
{
	
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
}

// ��ʼ������ 
void Init() 
{
	
	//printf("--------->Init()\n");
	fileOpen("r");
	fscanf(fp, "%d%d", &n, &m);
	// ��ʼ��ͼ 
	graph = (Arc**)malloc(sizeof(Arc*) * (n+1));
	for (int i=0; i<=n; i++) 
	{
		graph[i] = (Arc*)malloc(sizeof(Arc) * (n+1));
	}
	for (int i=0; i<=n; i++) 
	{
		for (int j=0; j<=n; j++) 
		{
			graph[i][j].type = 0;
			graph[i][j].weight = 0;
		}
	}
	
	// �������ݸ�ͼ��ֵ 
	int x = 0, y = 0, type = 0, weight = 0;
	for (int i=1; i<=m; i++) 
	{
		fscanf(fp, "%d%d%d%d", &type, &x, &y, &weight);
		graph[x][y].type = type;
		graph[x][y].weight = weight;
		graph[y][x] = graph[x][y];
	}
	
	// ��ʼ���Ͻ�˹�����㷨���ݽṹ 
	dj = (Djs*)malloc(sizeof(Djs) * (n+1));
	for (int i=1; i<=n; i++) 
	{
		dj[i].final = false;
		dj[i].pre = 1;
		if (graph[1][i].type) dj[i].length = graph[1][i].weight * graph[1][i].weight;
		else dj[i].length = graph[1][i].weight;
	}
	dj[1].final = true;
	
	//printf("<--------------\n");
}

// ��������
void Finish() 
{
	
	for (int i=0; i<=n; i++) 
	{
		free(graph[i]);
	}
	free(graph);
	free(dj);
	fileClose();
} 

// ������������ĳ�㵽��ʼ��ĳ���
int getLength(int end, int pre) 
{
	//cout<<"===============\n";
	int length = 0, cur = end, sum = 0;
	while (cur != 1) 
	{
		//cout<<pre<<"===="<<cur<<"===="<<graph[pre][cur].type<<endl;
		if (graph[pre][cur].type) 
		{
			sum += graph[pre][cur].weight;
			//cout<<"sum:"<<sum<<endl;
		}
		else 
		{
			length += sum*sum + graph[pre][cur].weight;
			sum = 0;
			//cout<<"length:"<<length<<endl;
		}
		cur = pre;
		pre = dj[cur].pre;
	}
	length += sum*sum + graph[pre][cur].weight;
	//cout<<"======="<<length<<"======="<<endl;
	return length;
}

// ���ݵϽ�˹���������·�� 
void FindDjs() 
{
	
	// ��n-1����Ϊ��ʼ���Ѿ�Ϊtrue 
	for (int i=1; i<=n-1; i++) 
	{
		int min = INT_MAX, minPos = i;
		for (int j=1; j<=n; j++) 
		{
			if (dj[j].length && !dj[j].final && dj[j].length<min) 
			{
				min = dj[j].length;
				minPos = j;
			}
		}
		dj[minPos].final = true;
		for (int j=1; j<=n; j++) 
		{
			// graph[minPos][j].weight��Ϊ0����˵��jλ�ö��������µ����� 
			int newLength = getLength(j, minPos);
			if (!dj[j].final && graph[minPos][j].weight && 
				(!dj[j].length || dj[j].length && newLength < dj[j].length)) 
			{
				dj[j].length = newLength;
				dj[j].pre = minPos;
			}
		}
//		for (int j=1; j<=n; j++) {
//			printf("%d %d %d\n", dj[j].pre, dj[j].length, dj[j].final);
//		}
	}
}


int main() 
{
	
	Init();
	
//	for (int i=0; i<n; i++) {
//		for (int j=0; j<n; j++) {
//			printf("%d(%d)  ", graph[i][j].weight, graph[i][j].type);
//		}
//		printf("\n");
//	}
//	printf("\n");
//	
//	for (int i=1; i<=n; i++) {
//		printf("%d %d %d\n", dj[i].pre, dj[i].length, dj[i].final);
//	}
//	printf("\n");
	
	FindDjs();
	
	printf("%d\n\n", dj[n].length);
	
	stack<int> res;
	int cur = n, pre = dj[cur].pre;
	while (cur != 1) 
	{
		res.push(cur);
		cur = pre;
		pre = dj[cur].pre;
	}
	res.push(cur);
	printf("%d", res.top());
	res.pop();
	while (!res.empty()) 
	{
		printf("--->%d", res.top());
		res.pop();
	}	
	printf("\n\n");
	
	for (int i=1; i<=n; i++) 
	{
		printf("1------>%d: %d\n", i, dj[i].length);
	}
	
	Finish();
}

#include<iostream>
using namespace std;
void BubbleSort(int* a,int len)
{
    
    bool flag = true;//��־�����ж��Ƿ�����
    for(int i = 0;i < len;++i)//��ѭ��
    {
        for(int j = 0;j < len-i-1;++j)//��ѭ����ÿ��ѭ���Ƚ�len-i-1��
        {
            if(a[j]>a[j+1])
            {
                int temp;
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
                flag = false;
            }
        }
        if(flag)//�������ֱ������
        {
            break;
        }
    }
}
int main()
{
    int n,*p,*q;
    cin>>n;
    p=new int [n];
    q=p;
    for(int i=0;i<n;i++){
    	cin>>*q;
    	q++;
	}
    BubbleSort(p,n);
	for(int i=0;i<n;i++){
		cout<<*p<<" ";
		p++;
	}
	return 0;
}

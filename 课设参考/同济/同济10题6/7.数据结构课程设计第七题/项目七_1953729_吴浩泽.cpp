#include"��Ŀ��_1953729_�����.h"
using namespace std;
int main()
{
	int x, y,a,sum=0;
	Priority_Queue<int>minnumber;            //int�͵���С��
	minnumber.buildheap();                   //������С��
	a=minnumber.size();                      //Ԫ�صĸ���
	for (int i = 1; i < a-1; i++)            //����ѭ��
	{
		x = minnumber.Out_Queue();
		y = minnumber.Out_Queue();
		x = x + y;
		sum = sum + x;                       //ǰa-2��ѭ��ѭ������С����ֻ������Ԫ��
		minnumber.In_Queue(x);
	}
	x = minnumber.Out_Queue();               //���һ�ν����������Ԫ�ص����
	y = minnumber.Out_Queue();
	sum = sum + x + y;
	cout << sum;                             //��������
	return 0;
}
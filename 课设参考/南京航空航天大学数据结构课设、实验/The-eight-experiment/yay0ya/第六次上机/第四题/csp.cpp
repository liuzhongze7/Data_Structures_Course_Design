#include<iostream>
using namespace std;
typedef struct ball{
	int locate;//С�����ڵ�λ��
	bool state;//Ĭ��״̬Ϊ1��ʱ��ǰ����״̬Ϊ0��ʱ���� 
}Ball;
int main(){
	int n;
	Ball *ball;
	cin>>n;//С��ĸ���
	ball=new Ball[n];
	
	int L;//�߶εĳ���
	cin>>L;
	while(L%2!=0){
		cout<<"���������߶εĳ���\n";
		cin>>L;
	}
	
	int t;//��¼t���С���λ�� 
	cin>>t;
	for(int i=0;i<n;i++){
		cin>>ball[i].locate;
		while(ball[i].locate%2!=0){
			cout<<"���������С���λ��\n";
			cin>>ball[i].locate; 
		}
		ball[i].state=1;//�տ�ʼ��Ĭ��С�������� 
	}
	
	
	
	for(int i=0;i<n;i++){
		if(ball[i].locate==L){
			ball[i].state=0;//�жϸտ�ʼ �Ƿ���С�� 
		}
		if(ball[i].locate==0){
			ball[i].state=1;
		}
	}
	
	//ʱ��������е��ж� 
	for(int i=0;i<t;i++){
		//�ж��Ƿ���С��֮�����ײ������У���С��֮���״̬����ת�� 
		for(int j=0;j<n;j++){
			for(int s=j+1;s<n;s++){
				if(ball[j].locate==ball[s].locate){
					int temp;
					temp=ball[j].state;
					ball[j].state=ball[s].state;
					ball[s].state=temp;
				}
			}
		}//for
		 
		//�ж��Ƿ���С��ײǽ�������С��ײǽ����С���״̬��ԭ����1ת��Ϊ0����
		//�Ƿ���С��ײ�������ǽ���У���0ת��Ϊ1 
		for(int j=0;j<n;j++){
			if(ball[j].locate==L){
				if(ball[j].state==1){
				ball[j].state=0;
			}
			}
			if(ball[j].locate==0){
			ball[j].state=1;
		}
		}
		
	//��С����һ����λ�ã�����Ǻ��˵�С��С��λ��--�����ǰ����С��С��λ��++ 
		for(int j=0;j<n;j++){
			if(ball[j].state==0){
				ball[j].locate--;
			}
			if(ball[j].state==1){
				ball[j].locate++;
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<ball[i].locate<<" "; 
	}
	cout<<endl;
	return 0;
} 

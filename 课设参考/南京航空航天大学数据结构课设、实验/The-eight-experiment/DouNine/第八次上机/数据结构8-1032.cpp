/*
��������
*/
#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;
	
int main() {
	srand(time(0));
	int n;
	cout<<"������ɫ��������\n";
	cin>>n;
	int a[n];
	for (int i=0; i<n; i++) {
		a[i] = rand()%3;
	}
	
	for (int i=0; i<n; i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;
	
	int i = 0, j = n-1, k;
	int temp, t;

	// ��iλ��Ϊ0��ǰ�� 
	while (a[i] == 0) i++;
	// ��kλ��Ϊ0��2ʱ��ǰ�� 
	k = i; 
	while (a[k] != 1) {
		// ���kλ��Ϊ0����iλ�ã�iλ�ñ�Ϊ2��������iǰ�� 
		if (a[k] == 0) {
			t = a[k];
			a[k] = a[i];
			a[i] = t;
			i++;
		}
		// kǰ�� 
		k++;
	}
	// �õ�1������ 
	temp = a[k];
	a[k] = a[i];
	
	int ki = i, kj = j; 
	while (1) {
		// jλ����ǰ�ߣ�ֱ����Ϊ2 
		while (a[j] == 2) j--;
		// ��kj��j֮����kj=j 
		if (kj > j) kj = j;
		// ��kjλ��Ϊ1��2ʱ��kj-- 
		while (a[kj] != 0 && kj > ki) {
			// ��kjλ��Ϊ2ʱ����jλ�ã�jλ�ñ�Ϊ1��������j-- 
			if (a[kj] == 2) {
				t = a[kj];
				a[kj] = a[j];
				a[j] = t;
				j--;
			}
			kj--;
		}
		// ���kj��ki����������� 
		if (kj == ki) break;
		// ��kjλ��Ϊ0ʱ���ŵ�iλ�ã�iλ��ԭ��Ϊ�գ���ͬʱ��jλ�õ�1�ŵ�kjλ�ã�jλ��Ϊ�� 
		a[i] = a[kj];
		a[kj] = a[j];
		
		// iλ��ͬ�� 
		while (a[i] == 0) i++;
		if (ki < i) ki = i;
		while (a[ki] != 2 && ki < j) {
			if (a[ki] == 0) {
				t = a[ki];
				a[ki] = a[i];
				a[i] = t;
				i++;
			}
			ki++;
		}
		if (ki == kj) break;
		a[j] = a[ki];
		a[ki] = a[i];
	}
	a[i] = temp;
	
	for (int i=0; i<n; i++) {
		cout<<a[i]<<" ";
	}
	cout<<endl;
}

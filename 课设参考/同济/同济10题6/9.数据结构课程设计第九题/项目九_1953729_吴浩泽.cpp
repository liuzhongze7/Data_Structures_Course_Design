#include"��Ŀ��_1953729_�����.h"
using namespace std;
int main() {
	int sum = 0;
	int num_every_term[8] = { 0 };                              //�ʼ���˸�ѧ�ڿ�Ŀ������Ϊ0                    
	while (sum != 38)                                         //8��ѧ�ڿγ�����Ϊ38�ƣ������ȼ��8��ѧ�ڿγ����Ƿ����Ҫ��
	{
		cout << "����������ÿ��ѧ�������Ŀγ���:";
		for (int i = 0; i < 8; i++)
		{
			cin >> num_every_term[i];
			sum += num_every_term[i];
		}
		if (sum != 38)                                        	//�γ����������Ϊ38�ƣ�Ҫ����������
		{
			cerr << "8��ѧ�ڿγ����ܺ�ӦΪ38�����������룡" << endl;
			sum = 0;
		}
		else 
		{
			cout << "����ɹ�����ȴ���" << endl;               //�γ�����Ϊ38�ƣ������ſ�ģʽ
		}
	}
	sum = 0;
	ifstream Infile;
	Infile.open("�α�.txt");
	if (!Infile)
	{
		cout << "error";
	}
	ofstream Outfile;
	Outfile.open("�α�(���ź�).txt", ios::app);
	int readed_times = 0;                                       //��ȡ�γ���Ϣ����
	int recorded_course = 0;                                    //��¼�Ѷ�ȡ�γ���
	string Course_Information[38][5];
	int arranged_course = 0;
	for (int i = 0; i < 8; i++) {
		while (readed_times != num_every_term[i] * 5) {
			Infile >> Course_Information[recorded_course][readed_times % 5];   //���ļ��ж�ȡ�γ���Ϣ��38*5��������
			if (readed_times % 5 == 4) {
				recorded_course++;
			}
			readed_times++;
		}
		readed_times = 0;
	}
	for (int i = 0; i < 8; i++)                                 //��ӡ�α�
	{
		Outfile << setw(50) << "��" << i + 1 << "ѧ��" << endl;
		Outfile << setw(25) << "Mon" << setw(20) << "Tues" << setw(20) << "Wen" << setw(20) << "Thur" << setw(20) << "Fri" << endl;
		MakeSchedule(Course_Information, num_every_term[i], arranged_course);
		arranged_course = arranged_course + num_every_term[i];
		Outfile << endl;
		Outfile << endl;
	}
	cout << "�ſγɹ���" << endl;                              //�ſ������
	Infile.close();
	Outfile.close();
	return 0;
}
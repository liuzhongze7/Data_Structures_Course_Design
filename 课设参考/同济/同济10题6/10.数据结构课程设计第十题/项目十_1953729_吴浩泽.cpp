#include"��Ŀʮ_1953729_�����.h"
int main()
{
	int number = 0, choice = 0;
	long long int exchange_time = 0;
	double sort_time = 4;
	int* array1;                                          //��̬����
	int* array2;
	Sort sort;                                           //�������Աsort
	srand((unsigned int)time(NULL));                                   //���������
	sort.Initial_interface();                            //���ú�����ӡ��ʼ����      
	array1 = new int[sort.Random_number];
	array2 = new int[sort.Random_number];
	for (int i = 0; i < sort.Random_number; i++)
	{
		array1[i] = rand();
		array2[i] = array1[i];
	}
	while (choice != 9)
	{
		cout << "��ѡ�������㷨��";
		cin >> choice;
		switch (choice)
		{
			case 1:
			{
				cout << endl;
				exchange_time = sort.Bubble_sort(array1,sort_time);
				cout << "ð����������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "ð�����򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 2:
			{
				cout << endl;
				exchange_time = sort.Selection_sort(array1, sort_time);
				cout << "ѡ����������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "ѡ�����򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 3:
			{
				cout << endl;
				exchange_time = sort.Direct_insertion_sort(array1,sort_time);
				cout << "ֱ�Ӳ�����������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "ֱ�Ӳ������򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 4:
			{
				cout << endl;
				exchange_time = sort.Shell_sort(array1, sort_time);
				cout << "ϣ����������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "ϣ�����򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 5:
			{
				cout << endl;
				exchange_time = sort.Quick_sort(array2, sort_time,0, sort.Random_number-1);
				cout << "������������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "�������򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 6:
			{
				cout << endl;
				exchange_time = sort.Heap_sort(array1, sort_time);
				cout << "����������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "�����򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 7:
			{
				cout << endl;
				exchange_time = sort.Merge_sort(array1, sort_time);
				cout << "�鲢��������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "�鲢���򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 8:
			{
				cout << endl;
				exchange_time = sort.Radix_sort(array1, sort_time);
				cout << "������������ʱ�䣺" << endl;
				cout << sort_time << endl;
				cout << "�������򽻻�������" << endl;
				cout << exchange_time << endl;
				cout << endl;
				break;
			}
			case 9:
			{
				system("pause");
				return 0;
			}
			default:
			{
				cout << "�������ݲ��Ϸ�,���������룺" << endl;
			}
		}
	}
}


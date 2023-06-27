/*
* FileName:  Sort.cpp
* Function:  �����㷨�Ƚ�
* Author:    ���ַ�
* StuNumber: 1951976
* Date:      2020.12.21
*/

#include <vector>    // ����������㷨vector
#include <iostream>
#include<algorithm>
#include <ctime>
#include <cstdlib>


using namespace std;


// �����㷨��
class SortAlgorithm
{
private:
    vector <int> RandNumbers;     // �����������ÿ���������ʹ����ͬ������
    double SortTime;  // ��������ʱ��
    long long ExchangeTimes; // ��������

    /*  �������� */
    bool IsSorted(vector<int> & cur);              // �ж��Ƿ��������
    void Swap(vector<int>& randNum, int i, int j);   // ��������
    int partition(vector<int>& temp, int low, int high);    // ����
    void quickSort(vector<int>& temp, int low, int high);
    void sink(vector<int>& temp, int k, int N);
    int getDigit(const vector<int>& temp);
    void merge(vector<int>& temp, vector<int>& aux, int lo, int mid, int hi);
    void mergeSort(vector<int>& temp, vector<int>& aux, int lo, int hi);

    /* ������ */
    void BubbleSort();  // ð������
    void SelectSort();  // ѡ������
    void InsertSort();  // ֱ�Ӳ�������
    void ShellSort();   // ϣ������
    void QuickSort();   // ��������
    void HeapSort();    // ������
    void MergeSort();   // �鲢����
    void RadixSort();   // ��������

public:
    SortAlgorithm(int Num);    //  ���캯�����������������ĸ���

    void Switch(int choice);   // ����ѡ����
};

// ���캯��
SortAlgorithm::SortAlgorithm(int Num)
{
    SortTime = 0.0;
    ExchangeTimes = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i < Num; i++)
        RandNumbers.push_back(rand() % Num);        // ���������
}

// ����ѡ����
void SortAlgorithm::Switch(int choice)
{
    switch (choice)
    {
    case 1: BubbleSort(); break;
    case 2: SelectSort(); break;
    case 3: InsertSort(); break;
    case 4: ShellSort(); break;
    case 5: QuickSort(); break;
    case 6: HeapSort(); break;
    case 7: MergeSort(); break;
    case 8: RadixSort(); break;
    }
}

// �ж��Ƿ�����
bool SortAlgorithm::IsSorted(vector<int> & cur)
{
    for (int i = 0; i < cur.size() - 1; i++)
    {
        if (cur[i + 1] < cur[i])
        {
            return false;
        }
    }
    return true;
}

// ����
void SortAlgorithm::Swap(vector<int> & randNum, int i , int j)
{
    int temp = randNum[i];
    randNum[i] = randNum[j];
    randNum[j] = temp;
}


 int SortAlgorithm::partition(vector<int>& temp, int low, int high)
    {
        int i = low, j = high + 1;
        int v = temp[low];
        while (true)
        {
            while (temp[++i] < v) if (i == high) break;
            while (v < temp[--j]) if (j == low) break;
            if (i >= j)
                break;
            Swap(temp, i, j);
            ExchangeTimes++;
        }
        Swap(temp, low, j);
        ExchangeTimes++;
        return j;
    }

void SortAlgorithm::quickSort(vector<int>& temp, int low, int high)
 {
    if (high <= low)
    {
        return;
    }
    int j = partition(temp, low, high);
    quickSort(temp, low, j - 1);
    quickSort(temp, j + 1, high);
 }

void SortAlgorithm::sink(vector<int>& temp, int k, int N)
{
    while (2 * k <= N)
    {
        int j = 2 * k;
        if (j + 1 <= N && temp[j + 1] > temp[j])
        {
            ++j;
        }
        if (temp[k] > temp[j])
        {
            break;
        }
        Swap(temp, k, j);
        k = j;
        ExchangeTimes++;
    }
}

int SortAlgorithm::getDigit(const vector<int>& temp)
{
    int digit = 1;
    int base = 10;
    for (int i = 0; i < temp.size(); ++i)
    {
        while (base <= temp[i])
        {
            base *= 10;
            ++digit;
        }
    }
    return digit;
}

void SortAlgorithm::merge(vector<int>& temp, vector<int>& aux, int lo, int mid, int hi)
{
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; ++k)
    {
        aux[k] = temp[k];
    }
    for (int k = lo; k <= hi; ++k)
    {
        if (i > mid) temp[k] = aux[j++];
        else if (j > hi) temp[k] = aux[i++];
        else if (aux[j] < aux[i])
        {
            temp[k] = aux[j++];
            ExchangeTimes++;
        }
        else
        {
            temp[k] = aux[i++];
            ExchangeTimes++;
        }
    }
}

void SortAlgorithm::mergeSort(vector<int>& temp, vector<int>& aux, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }
    int mid = lo + (hi - lo) / 2;
    mergeSort(temp, aux, lo, mid);
    mergeSort(temp, aux, mid + 1, hi);

    merge(temp, aux, lo, mid, hi);
}


// ð������
void SortAlgorithm::BubbleSort()
{
    vector<int> temp(RandNumbers);

    clock_t start = clock();
    for (int i = 1; i < temp.size(); ++i)
    {
        for (int j = temp.size() - 1; j >= i; --j)
        {
            if (temp[j - 1] > temp[j])
            {
                Swap(temp, j, j - 1);
                ExchangeTimes++;
            }
        }
    }
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "ð����������ʱ�䣺 " << SortTime << endl;
        cout << "ð�����򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}

// ѡ������
void SortAlgorithm::SelectSort()
{
    vector<int> temp(RandNumbers);

    clock_t start = clock();
    for (int i = 0; i < temp.size() - 1; ++i)
    {
        int min = i;
        for (int j = i + 1; j < temp.size(); ++j)
        {
            if (temp[min] > temp[j])
            {
                min = j;
            }
        }
        Swap(temp, min, i);
        ExchangeTimes++;
    }
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;

    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "ѡ����������ʱ�䣺 " << SortTime << endl;
        cout << "ѡ�����򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}

// ֱ�Ӳ�������
void SortAlgorithm::InsertSort()
{
    vector<int> temp(RandNumbers);

    clock_t start = clock();
    for (int i = 1; i < temp.size(); ++i)
    {
        for (int j = i; j - 1 >= 0 && temp[j] < temp[j - 1]; --j)
        {
            Swap(temp, j - 1, j);
            ExchangeTimes++;
        }
    }
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;

    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "ֱ�Ӳ�����������ʱ�䣺 " << SortTime << endl;
        cout << "ֱ�Ӳ������򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}

// ϣ������
void SortAlgorithm::ShellSort()
{
    vector<int> temp(RandNumbers);

    clock_t start = clock();
    int gap = 1;
    while (gap < temp.size() / 3)
    {
        gap = 3 * gap + 1;
    }

    while (gap >= 1)
    {
        for (int i = gap; i < temp.size(); ++i)
        {
            for (int j = i; j - gap >= 0 && temp[j] < temp[j - gap]; j -= gap)
            {
                Swap(temp, j - gap, j);
                ExchangeTimes++;
            }
        }
        gap /= 3;
    }
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "ϣ����������ʱ�䣺 " << SortTime << endl;
        cout << "ϣ�����򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}

// ��������
void SortAlgorithm::QuickSort()
{
    vector<int> temp(RandNumbers);

    clock_t start = clock();
    quickSort(temp, 0, temp.size() - 1);
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "������������ʱ�䣺 " << SortTime << endl;
        cout << "�������򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}

// ������
void SortAlgorithm::HeapSort()
{
    vector<int> temp(RandNumbers);
    int N = temp.size();

    clock_t start = clock();
    temp.insert(temp.begin(), -1);//temp[0]����
    //�����
    for (int k = N / 2; k >= 1; --k)
    {
        sink(temp, k, N);
    }
    //����
    while (N > 1)
    {
        Swap(temp, 1, N--);
        ExchangeTimes++;
        sink(temp, 1, N);
    }
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "����������ʱ�䣺 " << SortTime << endl;
        cout << "�����򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}

// �鲢����
void SortAlgorithm::MergeSort()
{
    vector<int> temp(RandNumbers);

    clock_t start = clock();
    vector<int> aux(temp.size());//��������
    mergeSort(temp, aux, 0, temp.size() - 1);
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "�鲢��������ʱ�䣺 " << SortTime << endl;
        cout << "�鲢���򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}

// ��������
void SortAlgorithm::RadixSort()
{
    vector<int> temp(RandNumbers);

    clock_t start = clock();
    vector<int> aux(temp);
    int N = temp.size();
    int R = 10;            //һ��ֻ��0-9
    int digit = getDigit(temp);
    int base = 1;         //Ŀ���ǵõ�һ������ĳһλ����,��õ�123�е�2
    //0��ʾ��λ
    for (int d = 0; d < digit; ++d)
    {
        vector<int> count(R + 1);//������ֵ�Ƶ��
        for (int i = 0; i < N; ++i)
        {
            //������һЩ��λ������Ҳû�й�ϵ,��Ϊ��������0,���ǻ�����
            int index = temp[i] / base % 10;//��һ�εõ��Ǹ�λ,�ڶ�����ʮλ..
            count[index + 1]++;
        }
        for (int r = 0; r < R; ++r)//��Ƶ��ת��Ϊ����
        {
            count[r + 1] += count[r];
        }
        for (int i = 0; i < N; ++i)//��Ԫ�ط���
        {
            int index = temp[i] / base % 10;
            aux[count[index]++] = temp[i];
        }
        for (int i = 0; i < N; ++i)//��д
        {
            temp[i] = aux[i];
        }
        base *= 10;//���ϴ����λ
    }
    clock_t end = clock();

    SortTime = ((double)end - (double)start) / CLOCKS_PER_SEC;
    if (!IsSorted(temp))
        cout << "����ʧ��!" << endl;
    else
    {
        cout << "������������ʱ�䣺 " << SortTime << endl;
        cout << "�������򽻻�����: " << ExchangeTimes << endl;
    }
    SortTime = 0.0;     // ����
    ExchangeTimes = 0;
}


// ��ʼ������
void Interface()  
{
    cout << "*****************************************" << endl;
    cout << "**            �����㷨�Ƚ�             **" << endl;
    cout << "**                                     **" << endl;
    cout << "**            1---ð������             **" << endl;
    cout << "**            2---ѡ������             **" << endl;
    cout << "**            3---ֱ�Ӳ�������         **" << endl;
    cout << "**            4---ϣ������             **" << endl;
    cout << "**            5---��������             **" << endl;
    cout << "**            6---������               **" << endl;
    cout << "**            7---�鲢����             **" << endl;
    cout << "**            8---��������             **" << endl;
    cout << "**            0---������ǰ����ѭ��     **" << endl;
    cout << "*****************************************" << endl;
}


/*======================== ������ ==========================*/
int main()
{
    Interface();       // ��ʼ������

    char tag;

    do
    {
        cout << "������Ҫ������������ĸ���������0ѡ��ָ����һ�������������";
        int N;
        cin >> N;

        while (N < 0)
        {
            cout << "�������������� ";
            cin >> N;
        }

        SortAlgorithm sort(N);
        int choice;
        while (1)
        {
            cout << "\n��ѡ�������㷨�� ";
            cin >> choice;
            sort.Switch(choice);
            
            if (choice == 0)       // ������ǰ����ѭ��
                break;
        }

        cout << "\n�������ԣ�(y or n)�� ";
        cin >> tag;
    } while (tag == 'y');

    return 0;
}


#include<iostream>
using namespace std;
#include<string.h>
#include<stdlib.h>
#include<fstream>
typedef struct goods{
	string name;
	int sold;
	int price;
}goods;
typedef struct goodlink{
	goods *data; 
	int numbers;//ָ����Ʒ������  
}goodlink;//��Ʒ����
 

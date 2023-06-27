/*
[��������]
�ڻ������и�ħ���̵꣬ͨ��ħ���Ż�ȯ��ÿ���Ż�ȯ��ӡ��һ��������ֵK��
��ʾ�����ڹ���ĳ��Ʒʹ�������Ż�ȯ�����Եõ�K������Ʒ��ֵ�Ļر���
���̵껹�������һЩ�м�ֵ����Ʒ�������������ȡ�����Ʒ��ʱ��ʹ����ֵΪ�����Ż�ȯ��
����뵹������ƷK������Ʒ��ֵ�Ľ������ǲ�Ҫ����������ֵΪ�����Ż�ȯ�����á�
���磬����һ���Ż�ȯ����ֵ�ֱ�Ϊ1��2��4��-1����Ӧһ����Ʒ����ֵΪ���Ǳ�7��6��-2��-3��
���и��ļ�ֵ��ʾ����Ʒ�������Ʒ�����ǿ��Խ��Ż�ȯ3����ֵ4��������Ʒ1����ֵ7���ϣ��õ����Ǳ�28�Ļر���
�Ż�ȯ4����ֵ-1��������Ʒ4����ֵ-3���ϣ��õ����Ǳ�3�Ļر���
���ǣ����һ��С�İ��Ż�ȯ3����ֵ4���õ���Ʒ4����ֵ-3���ϣ�����뵹�����̵���Ǳ�12����
ͬ�������Ż�ȯ4����ֵ-1���õ���Ʒ1����ֵ7���ϣ�����뵹�����̵���Ǳ�7����
�涨ÿ���Ż�ȯ��ÿ����Ʒ��ֻ����౻ʹ��һ�Σ�������Եõ������ر��� 
[����Ҫ��]
��1������˵�������������С���һ�����ȸ����Ż�ȯ�ĸ���N��������N���Ż�ȯ��������ֵ�� 
	�ڶ������ȸ�����Ʒ�ĸ���M��������M����Ʒ��������ֵ��
	N��M��[1,106]֮�䣬���е����ݴ�С������230�����ּ��Կո�ָ��� 
��2�����˵����������Եõ������ر���
��3������������ 
����
4 1 2 4 -1
4 7 6 -2 -3

���
43

����
4 3 2 6 1 
3 2 6 3

���
49

����
7 3 36 -1 73 2 3 6
6 -1 -1 -1 -1 -1 -1

���
1
*/

#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

int main() 
{
	
	int couponCount=0;
	scanf("%d", &couponCount);
	int *coupon = (int*)malloc(sizeof(int) * couponCount);
	for (int i=0; i<couponCount; i++) 
	{
		scanf("%d", &coupon[i]);
	}
	
	int goodsCount = 0;
	scanf("%d", &goodsCount);
	int *goods = (int*)malloc(sizeof(int) * goodsCount);
	for (int i=0; i<goodsCount; i++) 
	{
		scanf("%d", &goods[i]);
	}
	
	for (int i=0; i<couponCount; i++) 
	{
		for (int j=i; j<couponCount; j++) 
		{
			if (coupon[j]>coupon[i]) 
			{
				int temp = coupon[i];
				coupon[i] = coupon[j];
				coupon[j] = temp;
			}
		}
	}
	
//	for (int i=0; i<couponCount; i++) printf("%d ", coupon[i]);
//	printf("\n");
	
	for (int i=0; i<goodsCount; i++) 
	{
		for (int j=i; j<goodsCount; j++) 
		{
			if (goods[j]>goods[i]) 
			{
				int temp = goods[i];
				goods[i] = goods[j];
				goods[j] = temp;
			}
		}
	}
	
//	for (int i=0; i<goodsCount; i++) printf("%d ", goods[i]);
//	printf("\n");
	
	int sum=0;
	
	int pCou=0, pGood=0;
	while (coupon[pCou]>0 && goods[pGood]>0) 
	{
		sum += coupon[pCou] * goods[pGood];
		pCou++;
		pGood++;
	}
	pCou = couponCount-1, pGood = goodsCount-1;
	while (coupon[pCou]<0 && goods[pGood]<0) 
	{
		sum += coupon[pCou] * goods[pGood];
		pCou--;
		pGood--;
	}
	printf("%d", sum);
	
	free(coupon);
	free(goods);
}

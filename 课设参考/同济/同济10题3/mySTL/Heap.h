#pragma once
#include "Functional.h"
#include "Vector.h"
#include "Algorithm.h"


//��*(end-1)���������ʵ�λ��, ʹ��[start,end)��ɶ�
template <class Iter>
void pushHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	siftFix(start, 0, end - start - 1, *(end - 1), Less<value_type>());
}

template <class Iter, class Compare>
void pushHeap(Iter start, Iter end, Compare &comp)
{
	siftFix(start, 0, end - start - 1, *(end - 1), comp);
}

//���ܣ���*(start)������*(end-1)��(�Ա�ɾȥ), [start,end-1)��ɶ�
template <class Iter>
void popHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	value_type value = *(end - 1);  //��ԭ����ĩβֵ��������
	*(end - 1) = *(start);  //��*(start)�ƶ���*(end-1),*(start)������hole
	sinkFix(start, end - start - 1, 0, value, Less<value_type>());
}
template <class Iter, class Compare>
void popHeap(Iter start, Iter end, Compare &comp)
{
	typedef typename Iter::value_type value_type;
	value_type value = *(end - 1);  //��ԭ����ĩβֵ��������
	*(end - 1) = *(start);  //��*(start)�ƶ���*(end-1),*(start)������hole
	sinkFix(start, end - start - 1, 0, value, comp);
}


//���ܣ���[start,end)��ɶ�

template <class Iter>
void makeHeap(Iter start, Iter end)
{
	typedef typename Iter::value_type value_type;
	ptrdiff_t len = end - start;
	if (len < 2) return;
	ptrdiff_t hole = (len - 2) / 2;
	while (hole >= 0) {
		//���� hole �ڵ�
		sinkFix(start, len, hole, *(start + hole), Less<value_type>());
		--hole;
	}
}

template <class Iter, class Compare>
void makeHeap(Iter start, Iter end, Compare comp)
{
	ptrdiff_t len = end - start;
	if (len < 2) return;
	ptrdiff_t hole = (len - 2) / 2;
	while (hole > 0) {
		//���� hole �ڵ�
		sinkFix(start, len, hole, *(start + hole), comp);
		--hole;
	}
}



//���ܣ����ϵ���hole��λ��, �ҵ����ʵ�λ�ý�value����

template <class Iterator, typename T, class Compare>
void siftFix(Iterator first,
	ptrdiff_t top,
	ptrdiff_t hole,
	T value,
	Compare comp)
{
	ptrdiff_t parent = (hole - 1) / 2;
	while (parent >= top && comp(*(first + parent), value)) {
		*(first + hole) = *(first + parent);
		hole = parent;
		parent = (hole + 1) / 2 - 1;
	}
	*(first + hole) = value;
}

//���ܣ����µ���hole��λ��, �ҵ����ʵ�λ�ý�value����

template <class Iterator, typename T, class Compare>
void sinkFix(Iterator first,
	ptrdiff_t len,
	ptrdiff_t hole,
	T value,
	Compare comp)
{
	/* 1.��hole���Ƶ�Ҷ�Ӵ� */
	ptrdiff_t bigChild = 2 * hole + 2;  //���Һ��ӿ�ʼ����
	while (bigChild < len) {
		if (comp(*(first + bigChild), *(first + bigChild - 1)))
			bigChild--;  //���Ӵ����Һ���
		*(first + hole) = *(first + bigChild);
		hole = bigChild;
		bigChild = 2 * hole + 2;
	}
	if (len % 2 == 0 &&
		bigChild == len) {  //������������һ���ڵ�Ϊ��ڵ�, û���ֵܽڵ�
		*(first + hole) = *(first + bigChild - 1);
		hole = bigChild - 1;
	}
	/* 2.ת��Ϊ���ϵ������� */
	siftFix(first, 0, hole, value, comp);
}
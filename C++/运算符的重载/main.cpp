#include<iostream>
/*
	����� 
	
	1.���ܸı����������  
	2.���ܸı���������ȼ�
	3.���ܴ��������      
	*/

template<typename T>
class Vector;
template<typename T>
class Iterator
{
public:
	Iterator(Vector<T>* pv, int idx) :
		pvec(pv), index(idx)
	{}
	bool operator!=(const Iterator left)
	{
		return index != left.index;
	}
	T& operator*()const;
	const Iterator operator++(int)
	{
		const Iterator tmp(*this);
		index++;
		return tmp;
	}
	const Iterator operator--(int)
	{
		const Iterator tmp(*this);
		index--;
		return tmp;
	}
	const Iterator operator-(int left)
	{
		return Iterator(pvec, index - left);
	}
private:
	Vector<T>* pvec;
	int index;
};
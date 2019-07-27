#include<iostream>
/*
	运算符 
	
	1.不能改变运算符规则  
	2.不能改变运算符优先级
	3.不能创造运算符      
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
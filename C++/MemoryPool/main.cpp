#include<iostream>
/*
	内存池：自主的内存管理方式  
	new
		1.operator new
		2.构造
	delete 
		1.析构
		2.operator delete 

	1.函数重载
	2.静态链表
	3.自主的内存管理
	4.单例模式  
*/

const int MEM_SIZE = 10;
template<typename T>
class MEM_Pool
{
public:
	static MEM_Pool<T>* getInstance()
	{
		if (mmp == NULL)
		{
			mmp = new MEM_Pool<T>();
		}
		return mmp;
	}
	void* alloc(size_t size)
	{
		if (pool == NULL)
		{
			pool = (Node*)new char[(size + 4)*MEM_SIZE]();
			Node* pCur = pool;
			for (pCur; pCur < pool + MEM_SIZE - 1; pCur = pCur + 1)
			{
				pCur->pnext = pCur + 1;
			}
			pCur->pnext = NULL;
		}
		void* rt = pool;
		pool = pool->pnext;
		return rt;
	}
	void dealloc(void* ptr)
	{
		if (ptr == NULL)
		{
			return;
		}
		Node* pptr = (Node*)ptr;
		pptr->pnext = pool;
		pool = pptr;
	}
private:
	MEM_Pool()
	{
		pool = NULL;
	}
	MEM_Pool(const MEM_Pool<int>&);
	class Node
	{
	public:
		Node(T val = T()) :mdata(val), pnext(NULL){}
	public:
		T mdata;
		Node* pnext;
	};
	Node* pool;
	static MEM_Pool<T>* mmp;
};
template<typename T>
MEM_Pool<T>* MEM_Pool<T>::mmp = NULL;
class CGoods
{ 
public:
	CGoods(std::string name, float price, int amount)
		:mname(name), mprice(price), mamount(amount)
	{}
	void* operator new(size_t size)
	{
		return pmm->alloc(size);
	}
	void operator delete(void* ptr)
	{
		pmm->dealloc(ptr);
	}
private:
	std::string mname;
	float mprice;
	int mamount;
	static MEM_Pool<CGoods>* pmm;
};
MEM_Pool<CGoods>* CGoods::pmm = MEM_Pool<CGoods>::getInstance();

int main()
{
	CGoods* pgood1 = new CGoods("面包", 4.5, 100);
	CGoods* pgood2 = new CGoods("矿泉水", 2.0,100);

	delete pgood1;
	return 0;
}
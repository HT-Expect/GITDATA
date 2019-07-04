#include<iostream>

/*
	auto_ptr
		一块堆内存 只要有一个智能指针拥有所有权  

*/
/*
	shared_ptr  #include<memory>
	weak_ptr
*/
class Ref_Management
{
private:
	Ref_Management() :index(0){}
	Ref_Management(const Ref_Management&);
public:
	static Ref_Management* getInstance()
	{
		return &rm;
	}
public:
	void addRef(void* ptr)
	{
		int idx = FindAddr(ptr);
		if (idx < 0)
		{
			//node[index].ptr = ptr;
			//node[index++].ref = 1;
			Node tmp(ptr, 1);
			node[index++] = tmp;
		}
		else
		{
			node[idx].ref++;
		}
	}
	void delRef(void* ptr)
	{
		int idx = FindAddr(ptr);
		if (idx < 0)
		{
			throw std::exception("addr is not exist!");
		}
		else
		{
			if (node[idx].ref != 0)
			{
				node[idx].ref--;
			}
		}
	}
	int getRef(void* ptr)
	{
		int idx = FindAddr(ptr);
		if (idx < 0)
		{
			throw std::exception("addr is not exist!");
		}
		return node[idx].ref;
	}
private:
	int FindAddr(void* ptr)
	{
		int rt = -1;
		for (int i = 0; i < 10; i++)
		{
			if (node[i].ptr == ptr)
			{
				rt = i;
				break;
			}
		}
		return rt;
	}
	class Node
	{
	public:
		Node(void* p = NULL, int r = 0) :ptr(p), ref(r){}
	public:
		void* ptr;//堆内存的地址
		int ref;  //对应的引用计数
	};
	Node node[10];
	int index;
	static Ref_Management rm;
};
Ref_Management Ref_Management::rm;
template<typename T>
class Shared_Ptr
{
public:
	Shared_Ptr(T* ptr) :mptr(ptr)
	{
		prm->addRef(mptr);
	}
	Shared_Ptr(const Shared_Ptr<T>& rhs) :mptr(rhs.mptr)
	{
		prm->addRef(mptr);
	}
	Shared_Ptr<T>& operator=(const Shared_Ptr<T>& rhs)
	{
		if (this != &rhs)
		{
			prm->delRef(mptr);
			if (prm->getRef(mptr) == 0)
			{
				delete mptr;
			}
			mptr = rhs.mptr;
			prm->addRef(mptr);
		}
		return *this;
	}
	~Shared_Ptr()
	{
		prm->delRef(mptr);
		if (prm->getRef(mptr) == 0)
		{
			delete mptr;
		}
		mptr = NULL;
	}
	T& operator*()
	{
		return *mptr;
	}
	T* operator->()
	{
		return mptr;
	}
private:
	T* mptr;
	static Ref_Management* prm;
};
template<typename T>
Ref_Management* Shared_Ptr<T>::prm = Ref_Management::getInstance();

int main()
{
	int* p = new int;
	Shared_Ptr<int> sp1(p);
	Shared_Ptr<int> sp2(p);
	Shared_Ptr<int> sp3(p);
	return 0;
}
#if 0
template<typename T>
class Scope_Ptr
{
public:
	Scope_Ptr(T* ptr) :mptr(ptr){}
	~Scope_Ptr()
	{
		delete mptr;
	}
	T& operator*()
	{
		return *mptr;
	}
	T* operator->()
	{
		return mptr;
	}
private:
	Scope_Ptr(const Scope_Ptr<T>&);
	Scope_Ptr<T>& operator=(const Scope_Ptr<T>&);
	T* mptr;
};

int main()
{
	int* p = new int;
	Scope_Ptr<int> sp1(p);
	Scope_Ptr<int> sp2(p);
	Scope_Ptr<int> sp3(p);
	//Scope_Ptr<int> sp1 = new int;
	//Scope_Ptr<int> sp2 = sp1;
	return 0;
}

template<typename T>
class SmartPtr
{
public:
	SmartPtr(T* ptr) :mptr(ptr)
	{
		flag = true;
	}
	~SmartPtr()
	{
		if (flag)
		{
			delete mptr;
		}
		mptr = NULL;
	}
	/*
		旧的有释放权   ==》  新的就有
		旧的无释放权   ==》  新的无
		旧的赋后肯定没有释放权  
		this->flag = rhs.flag;
		rhs.flag = false;
	*/
	SmartPtr(const SmartPtr<T>& rhs)
	{
		this->mptr = rhs.mptr;

		this->flag = rhs.flag;
		rhs.flag = false;
	}
	SmartPtr<T>& operator=(const SmartPtr<T>& rhs)
	{
		if (this != &rhs)
		{
			if (flag)
			{
				delete mptr;
			}
			mptr = rhs.mptr;
			this->flag = rhs.flag;
			rhs.flag = false;
		}
		return *this;
	}
	T& operator*()
	{
		return *mptr;
	}
	T* operator->()
	{
		return mptr;
	}
private:
	T* mptr;
	mutable bool flag;//是否拥有释放权   true  有   false 无 
};

void Fun(SmartPtr<int> psp)
{
	
}
int main()
{
	SmartPtr<int> sp1 = new int;
	SmartPtr<int> sp2 = sp1;
	Fun(sp2);
	*sp1 = 20;
	return 0;
}

template<typename T>
class Auto_Ptr
{
public:
	Auto_Ptr(T* ptr) :mptr(ptr){}
	Auto_Ptr(const Auto_Ptr<T>& rhs)
	{
		mptr = rhs.mptr;
		rhs.Release();
	}
	Auto_Ptr<T>& operator=(const Auto_Ptr<T>& rhs)
	{
		if (this != &rhs)
		{
			delete mptr;//delete NULL;
			mptr = rhs.mptr;
			rhs.Release();
		}
		return *this;
	}
	~Auto_Ptr()
	{
		if (mptr != NULL)
		{
			delete mptr;
		}
		mptr = NULL;
	}
	T& operator*()
	{
		return *mptr;
	}
	T* operator->()
	{
		return mptr;
	}
private:
	void Release()const
	{
		(T*)mptr = NULL;
	}
	T* mptr;
};
int main()
{
	Auto_Ptr<int> ap1 = new int;
	Auto_Ptr<int> ap2 = ap1;

	*ap1 = 20;
	return 0;
}
#endif
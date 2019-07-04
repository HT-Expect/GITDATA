#include<iostream>
#include<string>
#include<memory>
/*
	工厂模式   ==>   依赖倒置     开放封闭   
		产产品  ==>   生成对象  
		1.不需要关注对象的名称
		2.不需要关注对象的生成过程  
		
	工厂方法模式	
*/
/*
	C++异常处理机制
	try  包含可能发生异常的代码 
	catch  捕获并处理异常
	throw  抛出异常  
*/
/*
	智能指针  
		C++内存回收机制   
	C++11前  auto_ptr  
	C++11    unique_ptr    shared_ptr  weak_ptr     <==    boost   
	RAII   
*/
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
	std::auto_ptr<int> ap1(new int);
	std::auto_ptr<int> ap2(ap1);

	*ap1 = 20; //



	int a = 10;
	int* p = &a;
	int* q = p;
	*p = 20;
	//Auto_Ptr<int> ap1 = new int;
	//Auto_Ptr<int> ap2 = ap1;
	//int* p = new int;
	//delete p;
	//*p = 10;
	//Auto_Ptr<int> ap = new int;
	//*ap = 20;
	return 0;
}
#if 0
class Exception
{
public:
	Exception(std::string err) :errinfo(err){}
	virtual std::string what()
	{
		return errinfo;
	}
protected:
	std::string errinfo;
};
class StackFullException :public Exception
{
public:
	StackFullException(std::string err) :Exception(err){}
	virtual std::string what()
	{
		return errinfo;
	}
};
class StackEmptyException :public Exception
{
public:
	StackEmptyException(std::string err) :Exception(err){}
	virtual std::string what()
	{
		return errinfo;
	}
};

const int SIZE = 10;
template<typename T>
class Stack
{
public:
	Stack() :tp(0){}
	void push(T val)
	{
		if (full)
		{
			throw StackFullException("stack  has been full");
		}
		arr[tp++] = val;
	}
	void pop()
	{
		if (empty())
		{
			throw StackEmptyException("stack has been empty!");
		}
		tp--;
	}
	T top()
	{
		if (empty())
		{
			StackEmptyException("stack has been empty!");
		}
		return arr[tp - 1];
	}
	bool empty()
	{
		return tp == 0;
	}
private:
	bool full()
	{
		return tp == SIZE;
	}
	T arr[SIZE];
	int tp;
};
void Func()
{
	throw std::exception("error!");//double
}
//abort() has been called
int main()
{

	//try{
	//	Func();
	//}
	//catch (int a)
	//{
	//	//throw;  //异常的重新抛出
	//	std::cout << a << std::endl;

	//}
	//catch (double b)
	//{
	//	std::cout << b << std::endl;
	//}
	//catch (std::exception& err)
	//{
	//	std::cout << err.what() << std::endl;
	//}
	//catch (...) //catch_all  最后的catch模块  
	//{
	//	std::cout << "catch_all" << std::endl;
	//}
	//std::cout << "hello world!" << std::endl;

	Stack<int> st;
	try{
		st.pop();
	}
	catch (StackEmptyException& err)
	{
		std::cout << err.what() << std::endl;
	}
	return 0;
}

class ProductA
{
public:
	ProductA(std::string name) :mname(name){}
	virtual void operation() = 0;
	virtual ~ProductA(){}
protected:
	std::string mname;
};
class ProductA1:public ProductA
{
public:
	ProductA1(std::string name) :ProductA(name){}
	void operation()
	{
		std::cout << "this is a " << mname << std::endl;
	}
};
class ProductA2 :public ProductA
{
public:
	ProductA2(std::string name) :ProductA(name){}
	void operation()
	{
		std::cout << "this is a " << mname << std::endl;
	}
};
class ProductB
{
public:
	ProductB(std::string name) :mname(name){}
	virtual void operation() = 0;
	virtual ~ProductB(){}
protected:
	std::string mname;
};
class ProductB1 :public ProductB
{
public:
	ProductB1(std::string name) :ProductB(name){}
	void operation()
	{
		std::cout << "this is a " << mname << std::endl;
	}
};
class ProductB2 :public ProductB
{
public:
	ProductB2(std::string name) :ProductB(name){}
	void operation()
	{
		std::cout << "this is a " << mname << std::endl;
	}
};

class AbstractFactory
{
public:
	virtual ~AbstractFactory(){}
	virtual ProductA* createProductA() = 0;
	virtual ProductB* createProductB() = 0;
};
class Factory1 :public AbstractFactory
{
public:
	virtual ~Factory1(){}
	ProductA* createProductA()
	{
		return new ProductA1("a1");
	}
	ProductB* createProductB()
	{
		return new ProductB1("b1");
	}
};
class Factory2 :public AbstractFactory
{
public:
	virtual ~Factory2(){}
	ProductA* createProductA()
	{
		return new ProductA2("a2");
	}
	ProductB* createProductB()
	{
		return new ProductB2("b2");
	}
};
int main()
{
	AbstractFactory* pa = new Factory1();
	ProductA * ppa = pa->createProductA();
	ProductB * ppb = pa->createProductB();
	ppa->operation();
	ppb->operation();
	delete pa;
	delete ppa;
	delete ppb;
	return 0;
}

class Product
{
public:
	Product(std::string name) :mname(name){}
	virtual void operation() = 0;
	virtual ~Product(){}
protected:
	std::string mname;
};
class ProductA :public Product
{
public:
	ProductA(std::string name) :Product(name){}
	void operation()
	{
		std::cout << "this is " << mname << std::endl;
	}
};
class ProductB :public Product
{
public:
	ProductB(std::string name) :Product(name){}
	void operation()
	{
		std::cout << "this is " << mname << std::endl;
	}
};
class Factory
{
public:
	virtual Product* createProduct() = 0;
	virtual ~Factory(){}
};
class FactoryA :public Factory
{
public:
	Product* createProduct()
	{
		return new ProductA("Product A");
	}
};
class FactoryB :public Factory
{
public:
	Product* createProduct()
	{
		return new ProductB("Product B");
	}
};
class ProductC :public Product
{
public:
	ProductC(std::string name) :Product(name){}
	void operation()
	{
		std::cout << "this is " << mname << std::endl;
	}
};

class FactoryC :public Factory
{
	Product* createProduct()
	{
		return new ProductC("Product C");
	}
};
int main()
{
	Factory* pf = new FactoryC();
	Product* pp = pf->createProduct();
	pp->operation();
	delete pf;
	delete pp;
	return 0;
}

class Fruit
{
public:
	Fruit(std::string nm) :name(nm){}
	virtual void operation() = 0;//
	virtual ~Fruit(){}
protected:
	std::string name;
};
class Apple :public Fruit
{
public:
	Apple(std::string nm) :Fruit(nm){}
	void operation()
	{
		std::cout << "this is a " << name << std::endl;
	}
};
class Banana :public Fruit
{
public:
	Banana(std::string nm) :Fruit(nm){}
	void operation()
	{
		std::cout << "this is a " << name << std::endl;
	}
};

class Factory
{
public:
	Fruit* createProduct(int flag)
	{
		switch (flag)
		{
		case 1: 
			return new Apple("apple");
			break;
		case 2:
			return new Banana("banana");
			break;
		default:
			std::cout << "factory does not product this product!" << std::endl;
			break;
		}
	}
};
int main()
{
	Factory f;
	Fruit* pf = f.createProduct(2);
	pf->operation();
	delete pf;
	return 0;
}
#endif
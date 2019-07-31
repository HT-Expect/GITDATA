#include<iostream>
//虚函数
class Base
{
public:
	Base(int a) :ma(a)
	{
		std::cout << "Base::Base(int)" << std::endl;
	}
	virtual ~Base()
	{
		std::cout << "Base::~Base()" << std::endl;
	}
	virtual void Show()
	{
		std::cout << "Base::Show ==> ma:" << ma << std::endl;
	}
protected:
	int ma;

};
class Derive : public Base
{
public:
	Derive(int b) :Base(b), mb(b)
	{
			std::cout << "Derive::Derive(int)" << std::endl;
	}
	~Derive()
	{
		std::cout << "Derive::~Derive()" << std::endl;
	}
	void Show() //virtual可加可不加
	{
		std::cout << "Derive::Show ==> mb:" << mb << std::endl;
	}
private:
	int mb;
};
int main()
{
	Base* pb = new Derive(10);
	delete pb;//pb->~Base() // call Base::~Base();
	//pb->destor pb->~Derive() //  
	return 0;
}
/*
int main()
{
	std::cout << sizeof(Base) << std::endl;//4
	std::cout << sizeof(Derive) << std::endl; //8
	Base* pb = new Derive(10);
	std::cout << typeid(pb).name() << std::endl;// Base* 
	std::cout << typeid(*pb).name() << std::endl;//class Base
	pb->Show();//Base::Show
	return 0;
}
*/

class Base
{
public:
	Base(int a) :ma(a){}
	void Show()
	{
		std::cout << "Base::Show ==> ma:" << ma << std::endl;
	}
	void Show(int a)
	{
		std::cout << "Base::Show(int) ==> a" << a << std::endl;
	}
protected:
	int ma;

};
class Derive : public Base
{
public:
	Derive(int b) :Base(b), mb(b){}
	void Show()
	{
		std::cout << "Derive::Show ==> mb:" << mb << std::endl;
	}
private:
	int mb;
};
int main()
{
	Base* pb = new Derive(10);//基类指针指向派生类对象  v
	Derive* pd = new Base(10);//派生类指针指向基类对象  x
	return 0;
}

int main()
{
	Derive d(10);
	d.Show();
	d.Base::Show(10);
	return 0;
}

class Base
{
public:
	Base(int a) :mb(a){}
	static void Show()
	{
		std::cout << "hello world!" << std::endl;
	}
	typedef int ELEM_TYPE;
	//static int mc;
protected:
	int mb;

};
//int Base::mc = 10;
class Derive : public Base
{
public:
	Derive(int b) :Base(b), mb(b){}
private:
	int mb;
};
int main()
{
	Derive d(10);
	//d.mc;
	//d.Show();
	Derive::ELEM_TYPE ma;
	return 0;
}
#include<iostream>
#include<string>

template<typename T>
class CLink
{
public:
	CLink()
	{
		phead = new Node();
	}
	void insertHead(T val)
	{
		Node* pnewnode = new Node(val);
		pnewnode->pnext = phead->pnext;
		phead->pnext = pnewnode;
	}
	class Node;
	Node* find(T val);
	void Show()
	{
		Node* pCur = phead->pnext;
		while (pCur != NULL)
		{
			std::cout << pCur->mdata << " ";
			pCur = pCur->pnext;
		}
		std::cout << std::endl;
	}
private:
	class Node
	{
	public:
		Node(T val = T()) :mdata(val), pnext(NULL){}
	public:
		T mdata;
		Node* pnext;
	};
	Node* phead;
};
template<typename T>
typename CLink<T>::Node* CLink<T>::find(T val)//typename
{
	Node* pCur = phead->pnext;
	while (pCur != NULL)
	{
		if (pCur->mdata == val)
		{
			return pCur;
		}
		pCur = pCur->pnext;
	}
	return NULL;
}
int main()
{
	CLink<int> cl;
	for (int i = 0; i < 10; i++)
	{
		cl.insertHead(i + 1);
	}
	cl.Show();
	auto rt = cl.find(6);
	return 0;
}
#if 0
template<typename T, int SIZE>
void Sort(T arr[])
{
	//SIZE = 5;
	T tmp = T();
	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}
template<typename T>
void Show(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
int main()
{
	//int arr[] = { 12, 332, 4556, 89, 872, 3 };
	//int len = sizeof(arr) / sizeof(arr[0]);
	//Sort<int, len>(arr);
	//Show<int>(arr, 6);

	int a = 10;
	const int b = 20;
	const int c = a;//常量退化成常变量    
	return 0;
}

/*
	bool Compare(int a, int b)
	{
		return a > b;
	}
	bool Compare(double a, double b)
	{
		return a > b;
	}
*/
template<typename T>
bool Compare(T a, T b)//const char* a  const char* b
{
	std::cout << "bool Compare(T,T)" << std::endl;
	return a > b;
}
template<>
bool Compare(const char* a, const char* b)
{
	return strcmp(a, b) > 0 ? true : false;
}
int main()
{
	Compare<int>(10, 20);
	Compare(10.1, 20.1);//double  double 
	Compare("hello", "world");
	return 0;
}

class Test
{
public:
	Test(int a) //:ma(a)
	{
	}
	static void Show()//_cdecl  
	{
		std::cout << "mb:" << mb << std::endl;
		Print();
	}
	void Print()//_thiscall 
	{
		std::cout << "hello world!" << std::endl;
	}
	//void Show()const //Test* const this;
	//{
	//	std::cout << "ma:" << ma << std::end;
	//}
public:
	//int ma;
	//const int ma;
	static int mb;
};
int Test::mb = 10;
int main()
{
	std::cout << sizeof(Test) << std::endl;
	Test test(10);
	test.Show();
	Test::Show();
	//const Test test(10);
	//test.Show();//const Test*  ==> const Test* const
	return 0;
}

class  Test
{
public:
	Test()
	{
		ma = 0;
		std::cout << "Test::Test()" << std::endl;
	}
	Test(int a) :ma(a)
	{
		std::cout << "Test::Test(int)" << std::endl;
	}
	Test(const Test& rhs) :ma(rhs.ma)
	{
		std::cout << "Test::Test(const Test&)" << std::endl;
	}
	Test& operator=(const Test& rhs)
	{
		std::cout << "Test::operator=(const Test&)" << std::endl;
		if (this != &rhs)
		{
			ma = rhs.ma;
		}
		return *this;
	}
	~Test()
	{
		std::cout << "Test::~Test()" << std::endl;
	}
private:
	int ma;
};
Test gtest1(10);//data
int main()
{
	Test ltest1(10);
	Test ltest2(ltest1);

	ltest1 = 20;
	Test ltest3 = 20;

	Test* ptest = new Test();
	delete ptest;
	Test* ptest2 = new Test[10];
	delete[] ptest2;
	std::cout << "-------------------" << std::endl;
	Test& rt = Test(10);
	std::cout << "-------------------" << std::endl;
	Test* ptest3 = &Test(20);
	std::cout << "-------------------" << std::endl;
	return 0;
}
Test gtest(20);//data


int main()
{
	//Test test1;
	//test1 = 20;// Test  <== int   //Test <== Test
	//test1 = Test(20);

	Test test2 = 20;//Test <== int   //Test <== Test
	//临时对象的生成   int构造
	//新对象的生成   拷贝构造
	//临时对象的销毁   析构

	//Test test1(20);
	//Test test2(test1);

	//Test test3;

	//test3 = test1;
	return 0;
}

class String
{
public:
	String()
	{
		mptr = new char[1]();
	}
	String(char* ptr)
	{
		mptr = new char[strlen(ptr) + 1]();
		strcpy_s(mptr, strlen(ptr) + 1, ptr);
	}
	String(const String& rhs)
	{
		mptr = new char[strlen(rhs.mptr) + 1]();
		strcpy_s(mptr, strlen(rhs.mptr) + 1, rhs.mptr);
	}
	String& operator=(const String& rhs)
	{
		if (this != &rhs)
		{
			delete[] mptr;
			mptr = new char[strlen(rhs.mptr) + 1]();
			strcpy_s(mptr, strlen(rhs.mptr) + 1, rhs.mptr);
		}
		return *this;
	}
	~String()
	{
		delete[] mptr;
		mptr = NULL;
	}
private:
	char* mptr;
};
int main()
{
	String str1("hello");
	String str2(str1);
	str1 = str2;
	return 0;
}

class Student
{
public:
	Student()
	{}
	Student(std::string id, std::string name, bool sex, int age)
		:mid(id), mname(name), msex(sex), mage(age)
	{}
	Student(const Student& rhs)
	{
		mid = rhs.mid;
		mname = rhs.mname;
		msex = rhs.msex;
		mage = rhs.mage;
	}
	//stu1 = stu2;
	Student& operator=(const Student& rhs)
	{
		if (this != &rhs)
		{
			mid = rhs.mid;
			mname = rhs.mname;
			msex = rhs.msex;
			mage = rhs.mage;
		}
		return *this;
	}
	~Student()
	{
		std::cout << "Student::~Student()" << std::endl;
	}
	void eat(std::string meal)
	{
		std::cout << this->mname << " is eatting " << meal << std::endl;
	}
	void sleep(std::string& time)
	{
		std::cout << mname << "is sleeping at " << time << std::endl;
	}
	void solve(std::string& math)
	{
		std::cout << mname << "is doing " << math << std::endl;
	}
private:
	std::string mid;
	std::string mname;
	bool msex;
	int mage;
};

int main()
{
	Student stu1("001", "zhangsan", true, 19);
	Student stu2 = stu1;//
	stu1 = stu2;

	return 0;
}

int main()
{
	Student stu1;
	Student stu2;
	stu1.eat("肉");
	stu1.~Student();
	return 0;
}
#endif
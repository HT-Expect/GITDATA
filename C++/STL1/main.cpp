#include<iostream>

/*
	STL	ÈÝÆ÷
*/
#include<algorithm>
//template<typename _Iter>
//void Show(_Iter _First, _Iter _Last)
//{
//	for (_First; _First != _Last; _First++)
//	{
//		std::cout << *_First << " ";
//	}
//	std::cout << std::endl;
//}
template<typename Container>
void Show(Container& con)
{
	Container::iterator it = con.begin();
	while (it != con.end())
	{
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}
#include<deque>

int main()
{
	std::deque<int> dqu;
	for (int i = 0; i < 10; i++)
	{
		dqu.push_front(i + 1);
	}
	Show(dqu);

	dqu.erase(dqu.end() - 3);
	Show(dqu);
	dqu.sort();
	return 0;
}
#if 0
#include<list>
int main()
{
	std::list<int> lst;
	for (int i = 0; i < 10; i++)
	{
		lst.push_front(i + 1);
	}
	Show(lst);
	lst.pop_front();
	Show(lst);

	lst.erase(++++lst.begin());
	Show(lst);
	//std::sort(lst.begin(), lst.end());
	lst.sort();
	Show(lst);
	return 0;
}

#include<vector>

int main()
{
	std::vector<std::vector<int>> vec;
	std::vector<int> ivec1;
	std::vector<int> ivec2;
	vec.push_back(ivec1);
	vec.push_back(ivec2);

	std::vector<std::vector<int>> vec2(10);
	vec2[0].push_back(1);
	std::cout << vec2[0][0] << std::endl;
	return 0;
}

int main()
{
	std::vector<int> vec1;
	std::vector<int> vec2(10);
	std::vector<int> vec3(10, 20);
	int arr[] = { 123, 2, 3456, 7 };
	int len = sizeof(arr) / sizeof(arr[0]);
	std::vector<int> vec4(arr, arr + len);
	//Show(vec4);

	for (int i = 0; i < 10; i++)
	{
		vec1.push_back(i + 1);
	}
	Show(vec1);
	vec1.insert(vec1.begin() + 5,100);
	Show(vec1);
	std::sort(vec1.begin(), vec1.end());
	Show(vec1);
	vec1.pop_back();
	vec1.erase(vec1.end() - 2);
	Show(vec1);

	std::cout << vec1.front() << std::endl;
	std::cout << vec1.back() << std::endl;
	return 0;
}
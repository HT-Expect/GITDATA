
//������������ͬ�����β����Ͳ�ͬ�����ɺ�������
bool Compare(int a, int b)
{
	return a > b;
}
bool Compare(double a, double b)
{
	return a > b;
}
bool Compare(char* pa, char* pb)
{
	return strcmp(pa, pb) > 0 ? true: false;
}
int a = 10.1;
int main()
{
	bool Compare(int, int);
	Compare(10, 20);
	Compare(10.2, 20.2);
	Compare("hello", "world");
	return 0;
}
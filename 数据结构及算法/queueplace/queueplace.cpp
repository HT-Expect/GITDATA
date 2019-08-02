//—°‘ÒŒª÷√
bool Place(int *ar,int k)
{
	for(int j = 1;j<k;++j)
	{
		if(ar[k] == ar[j] || abs(k-j) == abs(ar[k] - ar[j]))
		{
			return false;
		}
	}
	return true;
}
void PrintAr(int *ar,int n)
{
	for(int i = 1;i<=n;++i)
	{
		for(int j= 1;j<=n;++j)
		{
			if(ar[j] == i)
			{
				cout<<"@ ";
			}
			else
			{
				cout<<"# ";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}
int main()
{
	const int n = 4;
	int ar[n+1]={0,0,0,0,0};
	int k = 1;
	ar[k] = 0;
	while(k >= 1)
	{
		ar[k]+=1;
		while(ar[k] <= n && !Place(ar,k)) ar[k]+=1;
		if(ar[k] < n)
		{
			if(k > n)
			{
				PrintAr(ar,n);
			}
			else
			{
				k+=1; 
				ar[k] = 0;
			}
		}
		else
		{
			--k;
		}
	}
	return 0;
}
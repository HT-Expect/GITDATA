#include <stdio.h>
#include <stdlib.h>

void InsertSort1(int *arr,int len)//O(n^2),O(1),稳定,该算法不好
{
    int i;
    int j;
    int tmp;
    int k;
    for(i=1;i<len;i++)
    {
	tmp = arr[i];
	for(j=0;j<i;j++)//找位置，这种实现不好，在有序情况下还是O(n^2)
	{
	    if(arr[j] > tmp)
	    {
		break;
	    }
	}
	for(k=i-1;k>=j;k--)//移数据
	{
	    arr[k+1] = arr[k];
	}
	arr[j] = tmp;//插入
    }
}

void InsertSort(int *arr,int len)//O(n^2),O(1),稳定，完全有序则时间复杂度为O(n)
{
    int i;
    int j;
    int tmp;
    for(i=1;i<len;i++)
    {
	tmp = arr[i];
	for(j=i-1;j>=0;j--)
	{
	    if(arr[j] <= tmp)
	    {
		break;
	    }
	    arr[j+1] = arr[j];
	}
	arr[j+1] = tmp;
    }
}


int main()
{

    int arr[] = {5,9,0,23,45,78,65,4,2,1,9,8};
    InsertSort(arr,sizeof(arr)/sizeof(arr[0]));
    Show(arr,sizeof(arr)/sizeof(arr[0]));

    return 0;
}










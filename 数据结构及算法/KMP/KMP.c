#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//从str的pos位置开始查找子串sub，返回找到的下标
int BF(const char *str,const char *sub,int pos)//O(n*m),O(1)
{
    if(str==NULL || sub==NULL || pos<0)
    {
	return -1;
    }
    int i = pos;
    int j = 0;
    int lenstr = strlen(str);
    int lensub = strlen(sub);
    while(i<lenstr && j<lensub)
    {
	if(str[i] == sub[j])
	{
	    i++;
	    j++;
	}
	else//匹配失败
	{
	    i = i-j+1;//i走到起始位子的下一个
	    j = 0;
	}
    }
    if(j < lensub)//子串是否完成
    {
	return -1;//没有找到
    }
    else
    {
	return i-j;
    }

}

void GetNext(const char*sub,int *next)
{
    next[0] = -1;
    next[1] = 0;
    int j = 1;
    int k = 0;
    int lensub = strlen(sub);
    while((j+1) < lensub)
    {
	if((k==-1) || (sub[k]==sub[j]))
	{
	    next[++j] = ++k;
	    //next[j+1] = k+1;
	   // j++;
	   // k++;
	}
	else
	{
	    k = next[k];////*****
	}
    }
}

int KMP(const char *str,const char *sub,int pos)//O(n+m),O(m)
{  //省略参数检查
    int i = pos;
    int j = 0;
    int lenstr = strlen(str);
    int lensub = strlen(sub);
    int *next = (int *)malloc(lensub*sizeof(int));
    GetNext(sub,next);
    while(i<lenstr && j<lensub)
    {
	if((j==-1) || (str[i]==sub[j]))
	{
	    i++;
	    j++;
	}
	else//和BF算法不同
	{
	    j = next[j];//KMP,i不回退，j退到k即next[j]
	    //BF 算法
	    //i = i-j+1;
	    //j = 0;
	}
    }
    free(next);
    if(j >= lensub)
    {
	return i-j;
    }
    else
    {
	return -1;
    }
}

int main()
{
    printf("%d\n",KMP("ababcabcdabcde","abcd",6));
    return 0;
}








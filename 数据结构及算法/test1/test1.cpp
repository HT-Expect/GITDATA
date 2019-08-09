#include <iostream>
#include <vector>
using namespace std;


//小易在学校中学习了关于字符串的理论, 于是他基于此完成了一个字典的项目。
//小易的这个字典很奇特, 字典内的每个单词都包含n个'a'和m个'z', 并且所有单词按照字典序排列。
//小易现在希望你能帮他找出第k个单词是什么。

int main()
{
    int n,m;
    long long k;
    cin >> n >> m >> k;
    vector<char> str;
    
    while(n&&m)
    {
        long long count = 1;
        for(int i = 0;i < n-1;i++)
        {
            count *= n-1+m-i;
            count /= (i+1);
            if(count > k)break;
        }
        if(k <= count)
        {
            str.push_back('a');
            n--;
        }
        else
        {
            str.push_back('z');
            m--;
            k -= count;
        }
    }
    
    if(k != 1)
    {
        //printf("-1");
        cout << -1;
        return 0;
    }
    while(n--)str.push_back('a');
    while(m--)str.push_back('z');

    for(int i=0;i<str.size();i++)
    {
        cout << str[i];
    }
    
}
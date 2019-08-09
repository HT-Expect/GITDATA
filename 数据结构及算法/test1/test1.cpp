#include <iostream>
#include <vector>
using namespace std;


//С����ѧУ��ѧϰ�˹����ַ���������, ���������ڴ������һ���ֵ����Ŀ��
//С�׵�����ֵ������, �ֵ��ڵ�ÿ�����ʶ�����n��'a'��m��'z', �������е��ʰ����ֵ������С�
//С������ϣ�����ܰ����ҳ���k��������ʲô��

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
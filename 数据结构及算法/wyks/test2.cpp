#include <iostream>
#include <cstdio>
#include <math.h>
#include <vector>

using namespace std;
//ÍøÒ×À×»ð£¬Ìâ4
int score(vector<int>& arr,int len)
{
    int sum = abs(arr[0]-0);
    int i;
    for(i = 1; i < len;i++)
    {
        sum += abs(arr[i]-arr[i-1]);
    }
    
    return sum;
}

int main()
{
    int n;
    cin >> n;
    vector<int>arr;
    int i = 0;
    while(i < n)
    {
        int tmp;
		cin >> tmp;
		arr.push_back(tmp);
        i++;
    }
    
    vector<int>player1;
    vector<int>player2;
    
    int j = n - 1;
    int times = 1;
    for(i = 0,j;(i != j )|| (i+j != j);)
    {
        if(times%2 != 0)
        {
            player1.push_back(arr[j--]);
            player2.push_back(arr[j--]);
        }
        else
        {
            player1.push_back(arr[i++]);
            player2.push_back(arr[i++]);
        }
    }
    
    int len1 = player1.size();
    int len2 = player2.size();
    cout << score(player1,len1) << score(player2,len1);
    
    return 0;
}

// 面试题16：数值的整数次方
// 题目：实现函数double Power(double base, int exponent)，求base的exponent
// 次方。不得使用库函数，同时不需要考虑大数问题。

#include <iostream>
#include <cmath>
class Solution {
public: 
    double Power(double base, int exponent) {
    double result = 0;
    if(exponent > 0)
    {
        if(exponent == 1)
        return base;
        result = Power(base,exponent/2);
        result *= result;
        if(exponent%2 == 1)
        {
            result *= base;
        }      
    }      
    if(exponent == 0)
    return 1;
        
    if(exponent < 0)
    {
        result = 1/Power(base,0-exponent);
    }
    return result;
    }
};
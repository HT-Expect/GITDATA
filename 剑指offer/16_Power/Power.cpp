
// ������16����ֵ�������η�
// ��Ŀ��ʵ�ֺ���double Power(double base, int exponent)����base��exponent
// �η�������ʹ�ÿ⺯����ͬʱ����Ҫ���Ǵ������⡣

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
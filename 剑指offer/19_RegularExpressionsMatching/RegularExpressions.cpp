//��19��������ʽƥ��
// ��Ŀ����ʵ��һ����������ƥ�����'.'��'*'��������ʽ��ģʽ�е��ַ�'.'
// ��ʾ����һ���ַ�����'*'��ʾ��ǰ����ַ����Գ�������Σ���0�Σ����ڱ���
// �У�ƥ����ָ�ַ����������ַ�ƥ������ģʽ�����磬�ַ���"aaa"��ģʽ"a.a"
// ��"ab*ac*a"ƥ�䣬����"aa.a"��"ab*a"����ƥ�䡣

#include <cstdio>

bool match(char* str, char* pattern){
        if(str==NULL || pattern==NULL)
            return false;
        return match(str,pattern);
    }
    bool matchCore(char* str,char* pattern){
        if(*str=='\0'&&*pattern=='\0')
            return true;
        if(*str!='\0'&&*pattern=='\0')
            return false;
        if(*(pattern+1)=='*'){
            if(*str==*pattern||(*str!='\0'&&*pattern=='.')){
                return matchCore(str+1,pattern+2) || matchCore(str+1,pattern) || matchCore(str,pattern+2);
            }
            else{
                return matchCore(str,pattern+2);
            }
        }
        if(*str==*pattern||(*str!='\0'&&*pattern=='.'))
            return matchCore(str+1,pattern+1);
    }
/**
*  模式匹配
*  给定一段文本，给定一段模式，定位出模式在文本中的第一个位置
*  和strstr()函数类似
**/
/**
* KMP算法
* 先match下pattern找出pattern里面首尾的最大匹配的子串
* match(j) = 满足p0……pi = pj-i……pj的最大i
*
**/
#include <stdio.h>
char *strstr(char *string, char *pattern)
{
    char *start_p = pattern;
    char *start_s = string;
    while(*string != '\0')
    {
        while(*pattern != '\0')
        {
            if(*string == *pattern)
            {
                string++;
                pattern++;
                if(*pattern == '\0')
                    return string;
            }
            else
                break;
        }
        pattern = start_p;
        string = start_s;
        start_s++;
    }
    return NULL;
}
int strlen(char *string)
{
    int i = 0;
    while(string[i] != '\0')
    {
        i++;
    }
    return i;
}

void build_match(char *pattern, int *match)
{
    int i, j;
    int m = strlen(pattern);
    match[0] = 0;
    for(j = 1; j < m; j++)
    {
        i = match[j-1];
        while( (i>=1) && (pattern[i+1] != pattern[j]) )
            i = match[i];
        if(pattern[i+1] == pattern[j])
            match[j] = i+1;
        else
            match[j] = 0;
    }
}
char *KMP(char *string, char *pattern)
{
    int n = strlen(string);
    int m = strlen(pattern);
    int s, p, *match;
    if(n < m)
        return NULL;
    match = (int *)malloc(sizeof(int) * m);
    build_match(pattern, match);
    s = p = 0;
    while(s<n && p<m)
    {
        if(string[s] == pattern[p])
        {
            s++; p++;
        }
        else if(p > 0)
            p = match[p-1];
        else
            s++;
    }
    return (p==m)? (string+s-m) : NULL;

}
int main()
{
    printf("%s\n",KMP("ababcdabcd12abcd123","abcd1"));
}

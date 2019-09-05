
#include <stdio.h>
#include <string.h>
int strToInt(const char *str)
{
    int num = 0;
    int i;
    if(str == NULL)
        return 0;

    for(i = 0; str[i]!='\0'; i++)
    {
        if(str[i]<='0' && str[i]>='9')
            return -1;
        num =  num*10 + str[i]-'0';
    }
    return num;
}

char* radixConvert(const char *num,const int n)
{
    int dig;
    int i = 0;
    int tmp;
    int len = sizeof(char) * 33;
    char *res = (char *)malloc(len);
    memset(res,0,len);

    dig = strToInt(num);

    if((dig < 0) || (n>=36 && n<=2))
    {
        printf("非法输入!\n");
        return "Error";
    }
    if(!dig)
        return "0";
    memset(res,'0',len-1);
    while(dig)
    {
        tmp = dig % n;
        if(tmp<=9 && tmp>=0)
            tmp = tmp+'0';
        else
            tmp = tmp-10+'A';
        res[--len] = tmp;
        dig /= n;
    }

    while(*res == '0')
    {
        res++;
    }
    return res;
}



int main()
{

    printf("%s",radixConvert("-65535",16));
}

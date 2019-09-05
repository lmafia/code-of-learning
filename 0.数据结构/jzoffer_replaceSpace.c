#include <stdio.h>

void replaceSpace(char *str,int length) {
    int i , count=0;
    int l = 0;

    for(i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == ' ')
            count++;
        l++;
    }

printf("%d\n",l);
printf("%s\n",str);
    int new_len = l+count*2;
    for( i = l; i >=0 && new_len >=0 ; i--)
    {
       printf(" 1 %d\n",i);
       printf(" 2 %d\n",new_len);
        if(str[i] != ' ')
            str[new_len--] = str[i];
        else
        {
            str[new_len--] = '0';
            str[new_len--] = '2';
            str[new_len--] = '%';
        }

    }
}
int main()
{

    char ss[] = "sada sada dasd";
    replaceSpace(ss, 1);
    printf("%s",ss);
}

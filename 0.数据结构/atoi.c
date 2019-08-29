#include <stdio.h>
#include <stdlib.h>
int str_to_int(char *str) {
        int temp = 0;
        int i = 0, first = 1;
        if( str[i]>'9' || (str[i]<'0' && str[i]!='+' && str[i]!= '-'))
            return 0;
        if( str[i]<='9' && str[i]>='0' )
            first = 0;
        for(i=first; (str[i])!='\0'; i++)
        {
            if( str[i]>'9' || str[i]<'0' )
                return 0;
            temp = temp*10 + str[i]-'0';
            //temp = (temp<<1) + (temp<<3) + (str[i]&0xf);
        }
        if(str[0] == '-') return 0-temp;
        else  return temp;
    }

int main()
{
    char str[] = "+11131";
    printf("%s\n",str);
    printf("%d\n",str_to_int(str));
}

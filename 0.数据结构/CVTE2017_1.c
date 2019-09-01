#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *nums[7] = {"12","11","354","844","1000","999999","123456789"};
int str_to_int(char *str)
{
    int i = 0;
    int des = 0;
    while(str[i] != '\0')
    {
        des = des*10 + (str[i]-'0');
        i++;
    }
    return des;
}

char *mini_num(const char **nums, int length)
{
    int len[length];
    int i, pos, min;
    len[0] = str_to_int( nums[0] );
    min = len[0];
    pos = 0;
    for(i = 1; i < length; i++)
    {
        len[i] = str_to_int( nums[i] );
        if(len[i] < min)
        {
            min = len[i];
            pos = i;
        }
    }
   return nums[pos];
}

int main()
{
    printf("%s\n", mini_num(nums, 7));
    return 0;
}

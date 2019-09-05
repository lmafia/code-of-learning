
#include <string>

string ReverseSentence(string str) {
        string des(str);
        int j, i;
        int len = str.length();

        for(i = 0; str[i]!='\0'; i++)
        {
            if(str[i] == ' ')
            {
                j = i-1;
                while(j>=0 && str[j]!=' ' && str[j]!='.')
                {
                    des[len--] = str[j--];
                }
                des[len--] = ' ';
            }
            else if(str[i] == '.')
            {
                j = i;
                while(j>=0 && str[j]!=' ')
                {
                    des[len--] = str[j--];
                }
                 des[len--] = ' ';
            }
            else if(str[i+1] == '\0')
            {
                j = i;
                while(j>=0 && str[j]!=' ')
                {
                    des[len--] = str[j--];
                }
            }
        }
        return des;
int main()
{
 string str("asd.asd asd a");
 cout << ReverseSentence(str) <<endl;
}

#include <stdafx.h>
#include <string.h>
#include <stdlib.h>

#define TEST(X) X#X

char * deleteSpace(char *src)
{
	if (!src)
		return NULL;
	int word = 0;
	int len = 0;
	len = strlen(src);
	char *res = (char *)malloc(len);
	memset(res, 0, len);
	char *cp = res;
	for (int i = 0; i<len; i++)
	{
		if (src[i] != ' ')
		{
			*cp++ = src[i];
			if (src[i + 1] == ' ')
				*cp++ = ' ';
		}
	}
	*--cp = '\0';
	return res;
}

char *intToString(int src)
{
	int len = 0;
	int dig = src;
	while (dig % 10)
	{
		len++;
		dig /= 10;
	}
	printf("%d\n", len);
	char *res = (char *)malloc(len + 1);
	memset(res, 0, len + 1);
	for (int i = len-1; i >= 0; i--, src /= 10)
	{
		res[i] = src % 10 + '0';
	}


	return res;

}
char *reverString(char *str)
{
	int len = strlen(str);
	char temp;
	for (int i = 0; i<len / 2; i++)
	{
		temp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = temp;
	}

	return str;
}
int main(int argc, char **argv[])
{
	char a[] = "abcd";
	reverString(a);
	printf("%4.1f", (3.12));


	return 0;
}



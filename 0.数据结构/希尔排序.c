#include <stdio.h>
#include <stdlib.h>
#define LEN 15
int arry[15] = {7,1,5,7,0,2,4,8,8,3,12,14,1,5,6};
/**
* 希尔排序
* 就是把插入排序变为抽牌间隔递减至1的形式：
* 原来的插入排序是按顺序每次抽一个往下抽,然后从后往前，依次比较挪位插空
* 希尔排序最开始按照规定间隔抽牌,从前往后（间隔的），依次（间隔的）挪威插空，（就是隔了多少张来比较插空）
* 然后这个间隔是根据规则来依次减少，最后直至变为1，可能在成为1之前已经排序完成，或者在1的时候不需要比较多少次了
**/
void shell_sort(int *arry, int n)
{
    int times, i, flag, temp , deta;
   for(deta = n/2; deta > 0; deta /= 2) /*间隔的规则 deta = deta/2 */
    for(times = deta; times < n ; times+=deta) /*每一轮：假设第0牌已经在手里，一共要摸 (n-1)/deta 次牌*/
    {
        temp = arry[times];  /*摸牌*/
        for(i = times; (i > 0) && (arry[i-deta] > temp); i -= deta) /*从后往前比较(有间隔的)，新牌小于当前牌，手牌就往后挪*/
        {
            arry[i] = arry[i-deta]; /*往后挪位(有间隔的)*/
        }
        arry[i] = temp;/*手牌比新牌小了，或者新牌是最小的，插入进去*/
    }
}

int main()
{
    shell_sort(arry, LEN);
    for(int i = 0; i < LEN; i++)
        printf("%d --- %d\n",i,arry[i]);
}

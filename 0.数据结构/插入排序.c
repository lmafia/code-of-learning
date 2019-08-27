#include <stdio.h>
#include <stdlib.h>
#define LEN 10
int arry[10] = {1,3,5,7,9,2,4,6,8,0};
/**
* 插入排序：假设第0个元素为手里的牌， 依次从牌堆按顺序抽取，插入手中的牌序中。
* 新牌在手中的排序：新牌最大，直接放在最后面;新牌最小，需要从后往前，每张牌往后挪一个位置，然后插进去;
* 所以插入排序的思路就是，新牌从后往前比较，如果新牌比较小，手牌就要往后挪，直到发现手牌比新牌小，就插进去挪出来的空位中
**/
void insert_sort(int *arry, int n)
{
    int times, i, flag, temp;
    for(times = 1; times < n; times++) /*假设第0牌已经在手里，一共要摸n-1次牌*/
    {
        temp = arry[times];  /*摸牌*/
        for(i = times; (i > 0) && (arry[i-1] > temp); i--) /*从后往前比较，新牌小于当前牌，手牌就往后挪*/
        {
            arry[i] = arry[i-1]; /*往后挪位*/
        }
        arry[i] = temp;/*手牌比新牌小了，或者新牌是最小的，插入进去*/
    }
}

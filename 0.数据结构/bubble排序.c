#include <stdio.h>
#include <stdlib.h>
#define LEN 10
int arry[10] = {1,3,5,7,9,2,4,6,8,0};
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
/**
冒泡排序：是进行相邻元素的置换，对于数组和链表都可以操作
每一趟:都让这一趟最大的沉到最底下，或着让让最小的沉到最底下。每一趟都回少一个元素进行排序
**/
void bubble_sort(int *arry, int n)
{
    int rides, i, flag;
    for(rides = n-1; rides >= 0; rides--) /*泡泡需要排序的趟数，一共要n-1趟，最后一颗已经被安排了*/
    {
        flag = 0; /*作为是否需要排序的标志*/
        for(i = 0; i < rides; i++) /*真正在置换的过程*/
            if(arry[i] > arry[i+1]) /*从小到大排序，需要进行 大->小 置换,  如果是从大到小，那么>改成<就好了 不要=，可以保持序列的稳定性*/
            {
                swap(arry+i, arry+i+1); /*进行置换*/
                flag = 1; /*如果发生了一次置换，说明这个序列是需要排序的*/
            }
        if(!flag) break; /*如果一趟下来，一次置换都没发生，那么说明这个序列本来就是排好序的*/
    }
}


int main()
{
    bubble_sort(arry, LEN);
    for(int i = 0; i < LEN; i++)
        printf("%d --- %d\n", i, arry[i]);
}

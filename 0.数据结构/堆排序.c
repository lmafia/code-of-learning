#include <stdio.h>
#include <stdlib.h>
#define LEN 14
/**
* 堆排序
* 在这里麻烦的是因为之前创建最小堆 最大堆是用结构体的形式，数组的0号为哨兵，在这里我们直接用数组，
* 所以size用来找最后一个元素 的时候需要格外注意，还有通过parent找孩子的时候也不同
**/
int arry[15] = {7,1,5,7,0,2,4,8,3,12,14,1,5,6};
void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
/*下滤函数*/
void pre_down(int *heap, int p, int size)
{
    int parent, child;
    int temp;
    size -= 1;/*没有哨兵，从0开始，所以size要-1;size是拿来界定最尾元素的下标*/
    temp = heap[p];
    for(parent = p; parent*2+1 <= size; parent = child) /*这里寻找孩纸的方式也要改变*/
    {
        child = parent*2 + 1;
        if((child != size) &&
            (heap[child] < heap[child+1]))
            child++;
        if(temp >= heap[child])
            break;
        else
            heap[parent] = heap[child];
    }
    heap[parent] = temp;
}

void build_maxheap(int *heap, int size)
{
    int i;
    for(i = size/2; i>=0; i--)
        pre_down(heap, i, size);
}

void heap_sort(int *heap, int size)
{
    build_maxheap(heap, size);
    int i;
    for(i = size-1; i>0; i--) /*这里的size是拿来找最尾节点*/
    {
        swap(heap+i, heap);
        /*这时候要把最后一个元素滤除*/
        pre_down(heap, 0, i);/*pre_down已经帮我把size = i-1了*/
        //堆排序很适合在N个数据中找出最大（小）的K个;
        //只要在一般break出来就好啦;
    }
}

int main()
{
    heap_sort(arry, LEN);
    for(int i = 0; i < LEN; i++)
        printf("%d --- %d\n",i,arry[i]);
}

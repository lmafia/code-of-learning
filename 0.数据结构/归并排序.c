#include <stdio.h>
#include <stdlib.h>
#define LEN 17
int arry[17] = {7,1,5,7,0,2,4,8,3,12,14,1,5,6,22,9,15};

/*递归的归并排序*/
void merge(int *arry, int *temp_arry,
                int ptr_left, int ptr_right, int end_right)
{
    int end_left = ptr_right - 1;
    int ptr_temp = ptr_left;
    int elem_nums = end_right - ptr_left + 1;
    while( (ptr_left <= end_left)            /*循环终止的条件是两个指针到过了对应的end*/
            && (ptr_right <= end_right) )    /*说明有一边子列已经copy完了，剩下就由另外一边剩下的全部copy过来*/
    {
        if( arry[ptr_left] <= arry[ptr_right] )
        {
            //temp_arry[ptr_temp++] = arry[ptr_left++];
            temp_arry[ptr_temp] = arry[ptr_left];
            ptr_temp++;
            ptr_left++;
        }
        else
            temp_arry[ptr_temp++] = arry[ptr_right++];
    }
    while(ptr_left <= end_left)
        temp_arry[ptr_temp++] = arry[ptr_left++];
    while(ptr_right <= end_right)
        temp_arry[ptr_temp++] = arry[ptr_right++];
    for(int i=0; i<elem_nums; i++, end_right--)
        arry[end_right] = temp_arry[end_right];
}

void recursive_sort(int *arry, int *temp_arry, int ptr_left, int end_right)
{
    int  middle = (ptr_left+end_right) / 2;
    if(ptr_left < end_right)
    {
        recursive_sort(arry, temp_arry, ptr_left, middle);
        recursive_sort(arry, temp_arry, middle+1, end_right);
        merge(arry, temp_arry, ptr_left, middle+1, end_right);
    }
}
void recursive_merge_sort(int *arry, int size)
{
    int temp[size];
    recursive_sort(arry, temp, 0, size-1);
}

/*迭代的归并排序*/
void merge_noncpy(int *arry, int *temp_arry,
                int ptr_left, int ptr_right, int end_right)
{
    int end_left = ptr_right - 1;
    int ptr_temp = ptr_left;
    int elem_nums = end_right - ptr_left + 1;
    while( (ptr_left <= end_left)            /*循环终止的条件是两个指针到过了对应的end*/
            && (ptr_right <= end_right) )    /*说明有一边子列已经copy完了，剩下就由另外一边剩下的全部copy过来*/
    {
        if( arry[ptr_left] <= arry[ptr_right] )
        {
            //temp_arry[ptr_temp++] = arry[ptr_left++];
            temp_arry[ptr_temp] = arry[ptr_left];
            ptr_temp++;
            ptr_left++;
        }
        else
            temp_arry[ptr_temp++] = arry[ptr_right++];
    }
    while(ptr_left <= end_left)
        temp_arry[ptr_temp++] = arry[ptr_left++];
    while(ptr_right <= end_right)
        temp_arry[ptr_temp++] = arry[ptr_right++];
//    for(int i=0; i<elem_nums; i++, end_right--)
//        arry[end_right] = temp_arry[end_right];
}

void merge_pass(int *arry, int *temp_arry, int size, int length)
{
    int i,j;
    for(i = 0; i <= size-length*2; i += length*2)
        merge_noncpy(arry, temp_arry, i, i+length, i+length*2-1);

        merge_noncpy(arry, temp_arry, i, i+length, size-1);

}
void iteration_merge_sort(int *arry, int size)
{
    int length = 1;
    int temp_arry[size];
    while(length < size)
    {
        merge_pass(arry, temp_arry, size, length);
        length *= 2;
        merge_pass(temp_arry, arry, size, length);
        length *= 2;
    }
}



int main()
{
    iteration_merge_sort(arry, LEN);
    for(int i=0; i<LEN; i++)
        printf("%d --- %d\n", i, arry[i]);
}

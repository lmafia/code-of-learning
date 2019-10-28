#include <stdio.h>

int partition( int *array, int low, int high)
{
    int pivot;
    pivot = array[low];
    while(low < high)
    {
        while(low < high && array[high] >= pivot)
            high--;
        swap(pivot, array[high]);
        while(low < high && array[low] <= pivot)
            low++;
        swap(pivot, array[low]);
    }
    return low;
}

void qSort( int *array, int low, int high)
{
    int pivot;
    if( low < high )
    {
        pivot = partition(array, low, high);
        qSort(array, pivot+1, high);
        qSort(array, low, pivot-1);
    }
}

void quickSort(int *array, int length)
{
    qSort( array, 0, length);
}


int data[10] = {1,3,5,7,9,2,4,6,8};



int main()
{
    quickSort(data, 10);
    for(int i = 0; i < 10; i++)
        printf("%d  -- %d\n",i,data[i]);
    return 0;
}

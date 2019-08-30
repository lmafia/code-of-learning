/**
* 快速排序：
* 也是采用分治算法。
* 先在序列中挑取一个主元，把序列除去主元分为2大块（主元最好是中间值）（两块就可以平均分）
* 排序完成的序列：递归左边大块 U 主元 U 递归右边大块
* 递归边界条件：当序列只有一个元素
**/
/**
* 主元的选取：取头 中 尾的三个的中位数
 （可以多取几个数取中位数）
**/
#define LEN 20
int array[LEN] = {1,3,5,7,9,2,4,6,8,0,1,3,5,7,9,2,4,6,8,0};
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int median_3(int *array, int left, int right)
{
    int middle = (left + right) / 2;
    if (array[left] > array[middle])
    {
        swap(array + left, array + middle);
    }
    if (array[left] > array[right])
    {
        swap(array + left, array + right);
    }
    if (array[middle] > array[right])
    {
        swap(array + middle, array + right);
    }
    swap(array + middle, array + right - 1);
    return array[right - 1];
}

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

void quicksort(int *array, int left, int right)
{
    int threshold = 10;
    if(threshold <= right - left) /*因为有了这个阈值，小于阈值的做插入排序，所以当元素为1的时候本来要return， 现在不用了*/
    {
        int pivot = median_3(array, left, right);    //
        int i = left; /*left right已经在median内排好序了，而且主元在right-1位置*/
        int j = right - 1;
        while(1) /*子集划分*/
        {
            while (array[++i] < pivot); /*在left之后，right-1之前进行子集划分*/
            while (array[--j] > pivot); /*array[--j],是先减1，才取值*/
            if (i < j)
                swap(array + i, array + j);
            else
                break;
        }
        swap(array+i, array+right-1);
        quicksort(array, left, i-1);
        quicksort(array, i+1, right);
    }
    else
    insert_sort(array+left, right-left+1) ;   /*other sort*/
}

void quick_sort(int *array, int size)
{
    quicksort(array, 0, size-1);
}

int main()
{
    quick_sort(array, LEN);
    for(int i=0; i<LEN; i++)
        printf("%d --- %d\n", i, array[i]);
}

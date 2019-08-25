/**
*堆的两个特性：
* 1.结构性：用数组表示#完全#二叉树  这样就可以通过数组下标来寻址父子关系 完全二叉树的高度和结点树关系 height = log(N)
* 2.有序性：任意结点的data是其子树所有结点的最大值（或最小值）
*           最大堆：max_heap
*           最小堆：min_heap
*           从根结点到任意结点的路径上的序列都是有序的（大->小  小->大）
**/

/********最大堆**********/
typedef int elem_t;
typedef struct heap_stcut
#define MAXDATA
{
    elem_t *elem_arry; /*用数组存储堆的元素*/
    int size;          /*当前的大小*/
    int capacity;      /*最大容量*/
} heap_stcut, *max_heap, *min_heap;

max_heap max_heap_create(int max_sie)
{
    max_heap heap = (max_heap)malloc(sizeof(heap_stcut));
    heap->elem_arry = (elem_t *)malloc( sizeof( elem_t)*max_sie + 1 );
    heap->size = 0;
    heap->capacity = max_sie;
    /*安放哨兵*/
    heap->elem_arry[0] = MAXDATA;
}

void max_heap_insert(max_heap heap, elem_t item)
{
    int i;
    if( max_heap_isfull(heap) )
    {
        printf("max heap is full\n");
        return;
    }
    i = heap->size;
    heap->size++;
    while( heap->elem_arry[i/2] < item )
    {
        heap->elem_arry[i] = heap->elem_arry[i/2]
        i /= 2;
    }
    heap->elem_arry[i] = item;
}

elem_t delete_max(max_heap heap)
{
    int parent, child;
    elem_t maxitem, temp;
    if ( max_heap_isempty(heap) )
    {
        printf("the max heap is empty\n");
        return -1;
    }
    maxitem = heap->elem_arry[1];
    temp = heap->elem_arry[heap->size];
    heap->size--;
    for(parent=1; parent*2 <= heap->size; parent=child)
    {
        child = parent*2;
        if( (child != heap->size)&&
            (heap->elem_arry[child] < heap->elem_arry[child+1]) )
            child++;
        if(temp >= heap->elem_arry[child])
            break;
        else
            heap->elem_arry[parent] = heap->elem_arry[child];
    }
    heap->elem_arry[parent] = temp;
    return maxitem;
}

void pre_down(max_heap heap, int p)
{
    int parent, child;
    elem_t temp;
    temp = heap->elem_arry[p];
    for(parent=p; parent*2 <= heap->size; parent = child)
    {
        child = parent*2;
        if( (child != heap->size) &&
            (heap->elem_arry[child] < heap->elem_arry[child+1]))
            child++;
        if(temp >= heap->elem_arry[child])
            break;
        else
            heap->elem_arry[parent] = heap->elem_arry[child];
    }
    heap->elem_arry[parent] = temp;
}


void build_maxheap(max_heap heap)
{
    int i;
    for(i = heap->size/2; i>0; i--)
        pre_down(heap, i);
}

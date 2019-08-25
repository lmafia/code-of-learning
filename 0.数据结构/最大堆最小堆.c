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

/**
* 最大堆的创建
* 就是填充数据结构的值
* 注意：记得在完全二叉树的数组的起始置放哨兵,完全二叉树的根节点是从标号#1#开始的
* 一般哨兵的数值为在问题中不会接触到的最大值（最小堆就是最小值了）
* 为了在比较大小遍历或another操作的时候作为临界,把访问者压回去
**/
max_heap max_heap_create(int max_sie)
{
    max_heap heap = (max_heap)malloc(sizeof(heap_stcut));/*给最大堆分配内存*/
    heap->elem_arry = (elem_t *)malloc( sizeof( elem_t)*max_sie + 1 );/*给动态数组分配内存，因为根节点是从1开始的，maxsize会比数组大小少一个*/
    heap->size = 0;/*当前堆的大小初始化*/
    heap->capacity = max_sie;/*最大容量*/
    /*安放哨兵*/
    heap->elem_arry[0] = MAXDATA;
}
/**
* 最大堆的插入操作
* 插入新值，怎么找位置呢？
* 把新值作为堆的最后一个元素，然后再不断和父结点比较，一步一步往上比较，到达自己的位置。
*                             真的很有人生哲理，谁刚进来都是在最底层，一步一步往上爬，才能到达与自己最匹配的位置。
**/
void max_heap_insert(max_heap heap, elem_t item)
{
    int i;
    if( max_heap_isfull(heap) )/*当堆满时，退出*/
    {
        printf("max heap is full\n");
        return -1;
    }
    i = heap->size;/*找到尾端的叶子结点的标号，右子树的最右叶子*/
    heap->size++;/*要做插入操作，当前size就++*/
    while( heap->elem_arry[i/2] < item ) /*要插入的值不断和堆的子树的父结点做作#比较#遍历，为了给新值找位置嘛（从下往上）*/
    {
        heap->elem_arry[i] = heap->elem_arry[i/2]/*而且父结点还被比下去了，往下降一等*/
        i /= 2;
    }
    heap->elem_arry[i] = item;/*找着了就赋值呗*/
}

/**
* 最大堆的删除最大元素，也就删除根节点
*
**/
elem_t delete_max(max_heap heap)
{
    int parent, child;
    elem_t maxitem, temp;
    if ( max_heap_isempty(heap) )/*判断堆是否为空*/
    {
        printf("the max heap is empty\n");
        return -1;
    }
    maxitem = heap->elem_arry[1]; /*把根节点取出来，下面就要想办法把树弄好*/
    temp = heap->elem_arry[heap->size]; /*找到尾端的叶子结点作为比较的对象*/
    /*可以理解成反正要删除一个，拿它当牺牲出来先，代替下根节点，这时候肯定下面的可以篡位*/
    /*然后一个一个去比较，给他找位置，顺便把适合成为根节点的节点找出来*/

    heap->size--;/*当前堆的大小减一*/
    for(parent=1; parent*2 <= heap->size; parent=child) /*从根节点开始，判断当前parent是否有儿子结点（从上往下）*/
    {
        child = parent*2;/*child为当前parent的左孩子的标号嘛*/
        if( (child != heap->size)&&/*是否到达了堆的最后，因为想确定有没有右child*/
            (heap->elem_arry[child] < heap->elem_arry[child+1]) )/*不是在堆的最后，判断左右child的大小，选出最大的*/
            child++;/*上面判断出右child大，就让child为右孩子*/
        if(temp >= heap->elem_arry[child])/*那个最尾孩子如果大于等于这个当前parent最大的child，就要break咯，前期肯定很难找到安放最尾孩子的地方，一般都在else*/
            break;
        else/*else咯，这时候就要让那些篡位的上来咯，因为现在可以说是最尾孩子一开始作为根节点，*/
            /*帮助下面的篡位，然后篡位的把位置给本来的最尾孩子,一直操作下去，最尾孩子可能还会作为最后（可能有回报在一个较好的位置），但是他却奉献出来帮助别人上位了*/
            heap->elem_arry[parent] = heap->elem_arry[child];/*本来的父结点上去了，当前父结点换成了其最大孩子，就是替换填充呗*/
                                                             /*不仅数组换，在for里面的标号也要换*/
    }
    heap->elem_arry[parent] = temp;/*最后给最尾孩子这个可怜人安置了，受尽了这么多折磨*/
    return maxitem;/*返回最开始就被带走的最大根节点*/
}
/**
* 输入一个完全二叉树，变成最大堆
* 有2个函数，数组的元素迭代安放，变成一个最大堆
**/
void pre_down(max_heap heap, int p)
{
    int parent, child;
    elem_t temp;
    temp = heap->elem_arry[p];/*delete是temp是最尾结点，也就是要被安放的结点，那么这里也是为了给元素按照规则安放位置*/
    for(parent=p; parent*2 <= heap->size; parent = child)/*和delete差不多（这里的parent是从输入的标号p开始），为temp找位置，并且顺便把（从上往下）,*/
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

/*把完全二叉树的每个元素都遍历一下*/
void build_maxheap(max_heap heap)
{
    int i;
    for(i = heap->size/2; i>0; i--)
        pre_down(heap, i);
}

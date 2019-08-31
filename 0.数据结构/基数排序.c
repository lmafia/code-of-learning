#include <stdio.h>
#include <stdlib.h>
#define RADIX 10 /*进制数*/
#define MAXDIGIT 4 /*几位数*/

#define LEN 15
int arry[15] = {7,1,5,7,0,2,4,8,8,3,12,3114,1,11115,16};
/*数据结构*/
typedef struct node_t /*链表结点结构*/
{
    int key;
    struct node_t *next;
}node_t, *ptr_node;

typedef struct headnode_t /*桶结点的结构*/
{
    ptr_node head; /*桶头*/
    ptr_node tail; /*桶尾*/
}headnode_t, bucket[RADIX];/*数组类型，那么定义的时候 bucket B; B就是一个静态（不需要malloc）数组的首元素地址*/

 /*取每一位的数字*/
int get_digit(int key, int digit)
{
    int i, tmp;
    for(i = 1; i <= digit; i++)
    {
        tmp = key % RADIX;
        key /= RADIX;
    }
    return tmp;
}
/*次位优先的 基数排序*/
void lsd_radix_sort(int *array, int size)
{
    int digit, digit_num, i;
    bucket bucket_d; /*桶*/
    ptr_node tmp ;
    ptr_node list = NULL;
    for(i = 0; i < RADIX; i++) /*清空桶*/
        bucket_d[i].head  = bucket_d[i].tail = NULL;
    for(i = 0; i < size; i++) /*把序列填充到链表*/
    {
        tmp = (ptr_node)malloc(sizeof(node_t)); /*分配一个结点内存*/
        tmp->key = array[i]; /*填充序列值进去*/
        tmp->next = list; /*从头插入结点*/
        list = tmp;
    }
    for(digit = 1; digit <= MAXDIGIT; digit++) /*开始进行排序，对每个位桶 来装填*/
    {
        while(list) /*把list的分配到桶里面*/
        {
            digit_num = get_digit(list->key, digit); /*取出当前位的数字，0-9*/
            tmp = list; /*想要把每个结点弄出，并分给桶*/
            list = list->next;
            tmp->next = NULL;
            if(bucket_d[digit_num].head == NULL) /*桶本来是空的话，就把head，tail都指向新加入的元素*/
                bucket_d[digit_num].head = bucket_d[digit_num].tail = tmp;
            else                                    /*桶原本不是空的，就间接操作链表添加结点*/
            {
                bucket_d[digit_num].tail->next = tmp; /*这里其实是操作了tail指向的的节点---上一个插入进来的结点*/
                bucket_d[digit_num].tail = tmp;       /*这个tail就是为了下一次做间接操作，这应该就是尾巴指针的作用*/
            }
        }
        /*开始把桶里的收集起来，慢慢排到list中*/
        list = NULL; /*清空下list，因为接下来是从头插入，最后一个结点指向的一定要是NULL*/
        for(digit_num = RADIX-1; digit_num >= 0; digit_num--) /*10进制的话就是有9个桶0-9，分别要把内容 填充到一个链表中*/
        {
            if(bucket_d[digit_num].head) /*有些桶没有用到就不要装*/
            {
                bucket_d[digit_num].tail->next = list; /*把桶和list连接起来*/
                list = bucket_d[digit_num].head; /*把list等效成桶+list = 连接起来的list*/
                bucket_d[digit_num].head = bucket_d[digit_num].tail = NULL; /*清空桶*/
            }
        }
    }
    for(i=0; i < size; i++) /*把list回填到序列中*/
    {
        array[i] = list->key;
        tmp = list;       /*顺便做destroy操作*/
        list = list->next;
        free(tmp);

    }
}

int main()
{
    lsd_radix_sort(arry, LEN);
    for(int i=0; i < LEN; i++)
        printf("%d --- %d\n", i, arry[i]);
}

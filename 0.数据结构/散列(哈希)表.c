/**
* 通过对关键词进行 相应的运算（散列函数）出 对应的符号/关键词（key）
* 可能会产生关键词（key） 相同的冲突问题，需要解决 ------->  1.关键词（key）相同对应属性可以增加表格
* 符号表："关键词" --- "属性"对的集合
* 装填因子：填入的个数/整张表的个数
**/
/**
*  数字--散列函数的设计：
        1.直接定址法：取关键词的某个线性函数值作为散列地址
        2.除留余数（取模）法：key mod P    P一般为素数（没有因数）
        3.数字分析法： 分析数字关键词在各位上的变化情况，取比较随机的位作为散列地址
        4.折叠法：把关键词分割成位数相同的几个部分，然后折叠（相加，等运算）
        5.平方取中法：把数平方后产生一个大数，取其中的中间几位。

*   字符--散列函数的设计：
        1.ASCII码相加法：h(key) = (∑key[i]) mod (size)
        2.移位法(32进制)：h(key) = (∑key[n-i-1]*32^i) mod (size)
        注意：*32---相当于把字符做左移5位的运算， 不做次方运算，而是迭代相乘可以减少*运算次数
        while(*(char *)key != '\0')
        {
            h = (h<<5) + *key;
            key++;
        }
        return (h%size);
**/
/**
* 处理冲突的方法：1.换个位置：开放地址法 2.同一个位置组织：分离链接法（数组（存个链表的头节点）+链表（用来解决冲突））
*       开放地址法：一旦产生来冲突就按照某种规则去寻找下一个位置，直到找到空位置
*                   若发生i次冲突，试探的下一个地址将增加di ；冲突以后公式：hi(key)=(h(key)+di) mod size
*                   di的取值有几种方案：线性探测 --- di=i
*                                       平方探测 --- di=正负i^2（先加i^2, 后减i^2, 然后i才加一）###注意：size = 4k+3（size是素数）整个表都能被探测到
*                                       双散列   ---  di=i * h2(key)  ### h2(key) = p - (key mod p) p为素数
**/

#include <stdio.h>
#include <stdlib.h>
#define square(x) ((x)*(x))
int sqrt(int n)
{
    int low = 0;
    int high = n;
    while (low <= high)
    {
        //防止溢出
        long mid = (low + high) / 2;
         printf("\n%d\n", mid);
        if (mid*mid == n)
            return mid;
        else if (mid*mid < n)
            low = (mid + 1);
        else
            high = mid - 1;
    }
    return high;
}

#define MAXTABLESIZE 100000
typedef int position_t;
typedef enum {FILLED, EMPTY, DELETED} entry_t;

typedef struct hash_node_t
{
    int data;
    int status;
}hash_node_t, *hash_t;

typedef struct h_table_node_t
{
    int size;
    hash_t hash_nodes;
} h_table_node_t, *hash_table_t;

int next_prime(int num)
{
    int i;
    int p = (num%2)? num+1 : num+2;
    while(p <= MAXTABLESIZE)
    {
        for(i=(int)sqrt(p); i > 2; i--)
            if( !(p%i))
                break;
        if(i == 2)
           break;
        else
            p += 2;
    }
    return p;
}
int hash(int key, int size)
{
    int tmp = key%size;
    return tmp;
}
hash_table_t create_table(int size)
{
    hash_table_t hash_table;
    int i;
    hash_table = (hash_table_t) malloc(sizeof(h_table_node_t));
    hash_table->size = size;
    hash_table->hash_nodes = (hash_t)malloc(sizeof(hash_node_t) * hash_table->size);
    for(i = 0; i < hash_table->size; i++)
    {
        hash_table->hash_nodes[i].status = EMPTY;
    }
    return hash_table;
}

position_t hash_find(hash_table_t hash_table, int elem)
{
    position_t current_pos, new_pos;
    int count = 0;
    new_pos = current_pos = hash(elem, hash_table->size);
    while(hash_table->hash_nodes[new_pos].status != EMPTY && /*空表示不存在元素*/
          hash_table->hash_nodes[new_pos].data != elem)
    {
        count++;
        if(count%2)
        {
            new_pos = current_pos +  square( (count+1)/2 );
            if(new_pos >= hash_table->size)
                new_pos = new_pos % hash_table->size;
        }
        else
        {
            new_pos = current_pos - square( count/2 );
            while(new_pos < 0)
                new_pos += hash_table->size;
        }
    }
    return new_pos;
}

int hash_insert( hash_table_t hash_table, int elem)
{
    position_t pos = hash_find(hash_table, elem);
    if(hash_table->hash_nodes[pos].status != FILLED)
    {
        hash_table->hash_nodes[pos].status = FILLED;
        hash_table->hash_nodes[pos].data = elem;
        return 0;
    }
    else
    {
        printf("the element is exist\n");
        return -1;
    }
}

int hash_delete(hash_table_t hash_table, int elem)
{
    position_t pos = hash_find(hash, elem);
    if(hash_table->hash_nodes[pos].status == FILLED)
    {
        hash_table->hash_nodes[pos].status = DELETED;
        return 0;
    }
    else
    {
        printf("the elemnt is empty or deleted\n");
        return -1;
    }
}




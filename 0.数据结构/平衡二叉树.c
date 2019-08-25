/**
* 名称：平衡二叉树 AVL
* 性质：由于搜索二叉树会因为结点的插入而导致树的深度、ASL不同（树的深度越小，查找的平均时间越小，所以树越平衡越好）。
*       为了使得树平衡，引入平衡因子BF。BF=height_of_left - height_of_right
*        任一结点的|BF| <= 1
*        当插入新结点破坏了平衡结构，出现|BF|>1 就需要做平衡二叉树的调整
*        有四种调整方式1.RR 右右单旋 2.LL 左左单旋 3.RL 右左双旋 4.LR 左右双旋
*        1.右右：破坏者在被破坏者的右子树的右子树上
*        2.左左：破坏者在被破坏者的左子树的左子树上
*        3.左右：破坏者在被破坏者的左子树的右子树上
*        3.右左：破坏者在被破坏者的右子树的左子树上
*
**/
    typedef struct AVLNode *Position;
    typedef Position AVLTree; /* AVL树类型 */
    struct AVLNode{
        ElementType Data; /* 结点数据 */
        AVLTree Left;     /* 指向左子树 */
        AVLTree Right;    /* 指向右子树 */
        int Height;       /* 树高 */
    };

    int Max ( int a, int b )
    {
        return a > b ? a : b;
    }

    AVLTree SingleLeftRotation ( AVLTree A )
    { /* 注意：A必须有一个左子结点B */
      /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

        AVLTree B = A->Left;
        A->Left = B->Right;
        B->Right = A;
        A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
        B->Height = Max( GetHeight(B->Left), A->Height ) + 1;

        return B;
    }

    AVLTree DoubleLeftRightRotation ( AVLTree A )
    { /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
      /* 将A、B与C做两次单旋，返回新的根结点C */

        /* 将B与C做右单旋，C被返回 */
        A->Left = SingleRightRotation(A->Left);
        /* 将A与C做左单旋，C被返回 */
        return SingleLeftRotation(A);
    }

    /*************************************/
    /* 对称的右单旋与右-左双旋请自己实现 */
    /*************************************/

    AVLTree Insert( AVLTree T, ElementType X )
    { /* 将X插入AVL树T中，并且返回调整后的AVL树 */
        if ( !T ) { /* 若插入空树，则新建包含一个结点的树 */
            T = (AVLTree)malloc(sizeof(struct AVLNode));
            T->Data = X;
            T->Height = 0;
            T->Left = T->Right = NULL;
        } /* if (插入空树) 结束 */

        else if ( X < T->Data ) {
            /* 插入T的左子树 */
            T->Left = Insert( T->Left, X);
            /* 如果需要左旋 */
            if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )
                if ( X < T->Left->Data )
                   T = SingleLeftRotation(T);      /* 左单旋 */
                else
                   T = DoubleLeftRightRotation(T); /* 左-右双旋 */
        } /* else if (插入左子树) 结束 */

        else if ( X > T->Data ) {
            /* 插入T的右子树 */
            T->Right = Insert( T->Right, X );
            /* 如果需要右旋 */
            if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )
                if ( X > T->Right->Data )
                   T = SingleRightRotation(T);     /* 右单旋 */
                else
                   T = DoubleRightLeftRotation(T); /* 右-左双旋 */
        } /* else if (插入右子树) 结束 */

        /* else X == T->Data，无须插入 */

        /* 别忘了更新树高 */
        T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;

        return T;
    }

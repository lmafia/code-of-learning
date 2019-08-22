/*非递归
* 使用堆栈
* 遇到一个结点，就压栈，并遍历左子树。
* 当左子树遍历结束后，从栈顶弹出结点并访问
* 然后在访问右子树
*/

void in_order_traver(bin_tree tree)
{
	bin_tree b_tree = tree;
	stack_t stack = create_stack(MAX_SIZE);
	while(b_tree || !is_empty(stack) ) /*树不为空 或者 堆栈不为空;树为空而且堆栈空了就跳出循环*/
	{
		while(b_tree)
		{
			stack_push(stack, b_tree);
			b_tree = b_tree->left_child;
		}
		if(!is_empty(stack))
		{
			b_tree = stack_pop(stack); /*弹出来，以弹出的结点用来用作后面的一系列操作，因为后面需要把弹出的结点的右子树替换进去*/
			print("%d\n",b_tree->data);/*访问结点*/
			b_tree = b_tree->right_child;/*转而去遍历右子树*/
		}

	}
}

/*遍历叶子结点*/
void pre_order_traver(bin_tree tree)
{
	if(!tree)
		return;
	if(!tree->left_child && !tree->right_child)
		print("%d\n", tree->data);
	pre_order_traver(tree->left_child);
	pre_order_traver(tree->right_child);
}

/*求二叉树高度*/
void post_order_traver(bin_tree tree)
{
	int height_left, height_right, height_max;
	if(tree)
	{
		height_left = post_order_traver(tree->left_child);
		height_right = post_order_traver(tree->right_child);
		height_max = (height_left > height_right)? height_left:height_right;
		return height_max+1; /*每次递归，就加一*/
	}
	else 
		return 0;
}

/*层序遍历,要借助队列和图的广度优先遍历类似*/
void level_order_traver(bir_tree tree)
{
    queue_t queue;
	bir_tree t;
	if(!tree)
		return;
	queue = create_queue();
	add_queue(queue, tree);
	while(!is_empty(queue)
	{
		t = delete_queue(queue);
		printf("%d\n",t->data);
		if(t->left_child)
			add_queue(queue, t->left_child);
		if(t->right_child)
			add_queue(queue, t->right_child);
	}
}


/*用一个数组实现两个堆栈*/
struct di_stack
{
	int data[MAX_SIZE];
	int top1;
	int top2;
}

void di_push(struct di_stack *stack, int item, int tag)
{
	if(stack->top1 - stack->top2 == 1)
	{
		printf("fulled\n");
		return -1;
	}
	if(tag == 1)
		stack->data[++(stack->top1)] = item;
	else if(tag == 2)
		stack->data[--(stack->top2)] = item;
}

int di_pop(struct di_stack *stack, int tag)
{
	if(tag == 1)
	{
		if(stack->top1 == -1)
		{
			printf("empty\n");
			return -1;
		}
		return (stack->data[(stack->top1)--]);
	}
	else if(tag == 2)
	{
		if(stack->top2 == MAX_SIZE)
		{
			printf("empty\n");
			return -1;
		}
		return (stack->data[(stack->top2)++]);
	}
	
	
}
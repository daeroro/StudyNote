#include <stdio.h>
#include <stdlib.h>

typedef struct __stack
{
	void *data;
	struct __stack *link;
} stack;

typedef struct __tree
{
	int data;
	struct __tree *left;
	struct __tree *right;
} tree;

stack *get_stack_node(void)
{
	stack *tmp = (stack *)malloc(sizeof(stack));
	tmp->link = NULL;

	return tmp;
}

void push(stack **top, void *data)
{
	if(data == NULL)
		return;

	stack *tmp = *top;
	*top = get_stack_node();
	(*top)->data = malloc(sizeof(void *));
	(*top)->data = data;
	(*top)->link = tmp;	
}
/*
void push(stack **top, tree *node)
{
	stack *tmp = *top;

	*top = get_stack_node();
	(*top)->data = node;
	(*top)->link = tmp;
}
*/
void *pop(stack **top)
{
	stack *tmp = *top;
	void *data = NULL;

	if(*top == NULL)
	{
		printf("Stack is empty!\n");
		return NULL;
	}

	data = (*top)->data;
	*top = (*top)->link;
	free(tmp);

	return data;
}
/*
void pop(stack **top)
{
	stack *tmp = *top;
	
	if(!tmp)
		return;

	*top = (*top)->link;
	free(tmp);
}
*/
tree *get_tree_node(void)
{
	tree *tmp = (tree *)malloc(sizeof(tree));
	tmp->left = NULL;
	tmp->right = NULL;
	
	return tmp;
}
// 재귀함수가 아닌 tree_ins
void tree_ins(tree **root, int data)
{
	tree **tmp = root;

	while(*tmp)
	{
		if((*tmp)->data > data)
			tmp = &(*tmp)->left;
		else
			tmp = &(*tmp)->right;
	}

	*tmp = get_tree_node();
	(*tmp)->data = data;
}

void chg_node(tree **node)
{
	tree *tmp = *node;
 
     if(!(*node)->right)
         *node = (*node)->left;
     else if(!(*node)->left)
         *node = (*node)->right;
 
     free(tmp);
}
/* 강사님 chg_node
tree *chg_node(tree *root)
{
	tree *tmp = root;

	if(!root->right)
		root = root->left;
	else
		root = root->right;

	free(tmp);
	
	return root;
}
*/
void find_max(tree **node, int *max)
{
	while((*node)->right != NULL)
		*node = (*node)->right;
	
	*max = (*node)->data;
	chg_node(node);
}
/* 강사님 find_max non recall
void find_max(tree **node, int *data)
{
	tree **tmp = root;

	while(*tmp)
	{
		if((*tmp)->right)
			tmp = &(*tmp)->right;
		else
		{
			*data = (*tmp)->data;
			*tmp = chg_node(*tmp);
			break;
		}
	}
}
*/
void del_tree(tree **root, int data)
{
	tree **tmp = root;
	int max;

	if(*tmp == NULL)
	{
		printf("There are no node!\n");
		return;
	}
	
	while((*tmp)->data != data)
	{
		if((*tmp)->data > data)
			tmp = &(*tmp)->left;
		else 
			tmp = &(*tmp)->right;
	}

	printf("Find data %d\n", (*tmp)->data);

	if((*tmp)->left && (*tmp)->right)
		find_max(&(*tmp)->left, &(*tmp)->data);
	else
		chg_node(tmp);
}
/*
 강사님 non_recall del tree
void del_tree(tree **root, int data)
{
	tree **tmp = root;
	int num;

	while(*tmp)
	{
		if((*tmp)->data > data)
			tmp = &(*tmp)->left;
		else if((*tmp)->data < data)
			tmp = &(*tmp)->right;
		else if((*tmp)->left && (*tmp)->right)
		{
			find_max(&(*tmp)->left, &num);
			(*tmp)->data = num;
			return;
		}
		else
		{
			(*tmp) = chg_node(*tmp);
			return;
		}
	printf("Not Found\n");
}
*/
/*
void print_tree_patten(tree *root)
{
	if(root)
	{
		printf("data = %4d, ",root-> data);

		if(root->left)
			printf("left = %4d, ", root->left->data);
		else
			printf("left = NULL, ");
	
		if(root->right)
			printf("right = %4d\n", root->right->data);
		else
			printf("right = NULL\n");
 
//		print_tree(root->left);
//		print_tree(root->right);
	}
}

void print_tree(tree **root)
{
	tree **tmp = root;
	stack *top = NULL;
 
	push(&top, *tmp);

	while(top != NULL)
	{
		print_tree_patten(*tmp);
		if((*tmp)->left){
			push(&top, (*tmp)->left);
			tmp = &(*tmp)->left;
		}
		else if((*tmp)->right){
			push(&top, (*tmp)->right);
			tmp = &(*tmp)->right;
		}
		else{
			pop(&top);
		}
	}
}
*/
int main(void)
{
	int data[] = {50, 100, 25, 17, 23, 15, 20, 75, 80, 0};
	int i;
	tree *root = NULL;
	
	for(i = 0; data[i]; i++)
		tree_ins(&root, data[i]);

	print_tree(&root);

//	printf("\nDelete 17\n");
//	del_tree(&root, 17);
//	print_tree(root);

	return 0;
}

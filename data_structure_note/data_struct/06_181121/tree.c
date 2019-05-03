#include <stdio.h>
#include <stdlib.h>

typedef struct __tree
{
	int data;
	struct __tree *left;	//left
	struct __tree *right;	//right;
} tree;

tree *get_tree_node(void)
{
	tree *tmp = (tree *)malloc(sizeof(tree));
	tmp->left = NULL;
	tmp->right = NULL;
	
	return tmp;
}

void push_data(tree **node, int data)
{
	if(!(*node))
	{
		*node = get_tree_node();
		(*node)->data = data;
	}
	else if(data > (*node)->data)
		push_data(&((*node)->right), data);
	else
		push_data(&((*node)->left), data);	
}

void print_tree(tree *node)
{
	if(node)
	{
		printf("%d ", node->data);
		print_tree(node->left);
		print_tree(node->right);
	}
}

int main(void)
{
	int num[] = {50, 100, 25, 17, 23, 15, 20, 75, 80};
	int i;
	tree *node = NULL;

	for(i = 0; i < sizeof(num)/sizeof(int); i++)
		push_data(&node, num[i]);
	
	printf("**Tree Data print**\n");
	print_tree(node);
	printf("\n");

	return 0;
}

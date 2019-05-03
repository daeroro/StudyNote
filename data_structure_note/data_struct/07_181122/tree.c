#include <stdio.h>
#include <stdlib.h>

int cnt;

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
/*
void search_node(tree **node, tree *node)
{
	tree *tmp = *node;
	if(tmp->data < (*node)->data)
	{
	}
	else
		search_node(tmp->right, node);	
}
*/
void push_node(tree **node, int data)
{
	++cnt;

	if(*node == NULL)
	{
		*node = get_tree_node();
		(*node)->data = data;
		printf("data = %d, How much call recall Function = %d\n", data, cnt);
		cnt = 0;
		return;
	}
	else if(data > (*node)->data)
		push_node(&((*node)->right), data);
	else
		push_node(&((*node)->left), data);	
}

void del_node(tree **node, int data)
{
	if(*node != NULL)
	{
		if((*node)->data > data)
			del_node(&(*node)->left, data);
		else if((*node)->data < data)
			del_node(&(*node)->right, data);

		else if((*node)->data == data)
		{
			if(((*node)->left == NULL) && ((*node)->right == NULL))
			{ 
				tree *tmp = *node;
				*node = NULL;
				free(tmp);
		//		free(*node);
			}
			else if((*node)->right == NULL)
			{
				tree *tmp = *node;
				*node = (*node)->left;
				free(tmp);
			}
			else if((*node)->left == NULL)
			{
				tree *tmp = *node;
				*node = (*node)->right;
				free(tmp);
			}
			else
			{	//What is condition.....
				printf("OMG\n");
			// 트리의 왼쪽에서는 가장 큰 값, 트리의 오른쪽은 가장 작은 값을 찾아서
			// 부모에게 올려준다
			//	search_node(&(*node)->left, (*node)->data);
			}
		}
	}
}

void print_tree(tree *node)
{
	if(node != NULL)
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
		push_node(&node, num[i]);
	
	printf("**Tree Data print**\n");
	print_tree(node);
	printf("\n");
	
	del_node(&node, 23);

	print_tree(node);
	printf("\n");
	return 0;
}

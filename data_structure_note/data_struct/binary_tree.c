#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TRUE	1
#define FALSE	0

typedef struct __node
{
	int value;
	struct __node * left;
	struct __node * right;

}node;

node * get_node(void);
bool insert_tree(node ** top, int value);
int delete_tree(node ** top, int value);
void find_max(node ** top, int * max);
node * change_node(node ** top); 

void print_preorder(node * top);
void print_inorder(node * top);
void print_postorder(node * top);

int main(void)
{
	int arr[7] = {5, 3, 7, 1, 2, 9, 6};
	int i;
	node * top = NULL;
	
	for(i=0; i<7; i++)
		insert_tree(&top, arr[i]);
	
	print_preorder(top);
	printf("\n");
	/*
	print_inorder(top);
	printf("\n");
	
	print_postorder(top);
	printf("\n");
	*/
	delete_tree(&top, 2);

	print_preorder(top);
	printf("\n");

	return 0;
}

node * get_node(void)
{
	node * new = (node *)malloc(sizeof(node));
	new->left = NULL;
	new->right = NULL;

	return new;
}

bool insert_tree(node ** top, int value)
{
	node ** dptr = top;

	while(*dptr)
	{
		if(value < (*dptr)->value)
		{
			dptr = &((*dptr)->left);
		}
		else
		{
			dptr = &((*dptr)->right);
		}
	}

	*dptr = get_node();
	(*dptr)->value = value;

	return TRUE;
}

int delete_tree(node ** top, int value)
{
	int max;
	node ** dptr = top;

	while(*dptr)
	{
		if(value < (*dptr)->value)
			dptr = &((*dptr)->left);
		else if(value > (*dptr)->value)
			dptr = &((*dptr)->right);
		else
			break;
	}

	if(!(*dptr))
	{
		printf("No matching node\n");
		return 0;
	}

	printf("delete value = %d\n", (*dptr)->value);

	if((*dptr)->left)
	{
		find_max(&(*dptr)->left, &max);
		(*dptr)->value = max;
	}
	else
	{
		(*dptr) = (*dptr)->right;
	}
}

void find_max(node ** top, int * max)
{
	node ** tmp = top;

	while((*tmp)->right)
	{
		tmp = &((*tmp)->right);
	}

	*max = (*tmp)->value;
	change_node(tmp);

}

node * change_node(node ** top)
{
	node ** tmp = top;

	if((*top)->left)
		top = &(*top)->left; 
	else
		top = &(*top)->right;

	*tmp = *top;

	free(*top);
	return *tmp;
}

void print_preorder(node * top)
{
	node * tmp = top;

	if(!tmp)
		return;

	printf("%d ", tmp->value);
	print_preorder(tmp->left);
	print_preorder(tmp->right);
}

void print_inorder(node * top)
{
	node * tmp = top;

	if(!tmp)
		return;

	print_inorder(tmp->left);
	printf("%d ", tmp->value);
	print_inorder(tmp->right);

}

void print_postorder(node * top)
{
	node * tmp = top;

	if(!tmp)
		return;

	print_postorder(tmp->left);
	print_postorder(tmp->right);
	printf("%d ", tmp->value);

}

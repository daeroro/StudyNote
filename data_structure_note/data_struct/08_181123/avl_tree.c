#include <stdio.h>
#include <stdlib.h>

int level_cnt;

typedef struct __avl
{
	int data;				// 들어오는 데이터
	int level;
//	int L_level;
//	int R_level;
	struct __avl *L_child;	// 좌측
	struct __avl *R_child;	// 우측
} avl_tree;

avl_tree *get_node_tree(void)
{
	avl_tree *tmp = (avl_tree *)malloc(sizeof(avl_tree));
	tmp->L_child = NULL;
	tmp->R_child = NULL;
	return tmp;
}
void avl_tree_ins(avl_tree **root, int data)
{
	level_cnt++;

	if(*root == NULL)
	{
		*root = get_node_tree();
		(*root)->data = data;
		(*root)->level = level_cnt;
		level_cnt = 0;
		return;
	}
	if((*root)->data > data)
	{
		avl_tree_ins(&(*root)->L_child, data);
//		(*root)->L_level += 1;
	}
	else
	{
		avl_tree_ins(&(*root)->R_child, data);
//		(*root)->R_level += 1;
	}
}
void print_avl_tree(avl_tree *root)
{
	if(root)
	{
		printf("data = %4d, ",root-> data);
//		printf("L_level = %d, ", root->L_level);
//		printf("R_level = %d, ", root->R_level);
		printf("Level = %d, ", root->level); 
		if(root->L_child)
			printf("L_child = %4d, ", root->L_child->data);
		else
			printf("L_child = NULL, ");
 
		if(root->R_child)
			printf("R_child = %4d\n", root->R_child->data);
		else
			printf("R_child = NULL\n");
 
		print_avl_tree(root->L_child);
		print_avl_tree(root->R_child);
	}
}

int main(void)
{
	int i = 0;
//	int arr[] = {10, 20, 30};
	int arr[] = {10, 20, 30, 40, 50, 44, 41, 17};
	avl_tree *avl = NULL;

	for(i = 0; i < sizeof(arr)/sizeof(int); i++)
		avl_tree_ins(&avl, arr[i]);

	print_avl_tree(avl);
	return 0;
}

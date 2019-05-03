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

void two_node(tree **succ, tree **node)
{
	if((*succ)->left == NULL)
	{
		tree *tmp = *succ;
		(*node)->data = (*succ)->data;
		*succ = (*succ)->right;
		free(tmp);
	}
	else
		two_node(&(*succ)->left, node);
}

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
			// 가장 하위 노드, 밑에 아무 것도 가지지 않는다.
			if(((*node)->left == NULL) && ((*node)->right == NULL))
			{ 
				tree *tmp = *node;
				*node = NULL;
				free(tmp);
		//		free(*node);
			}
			// 우측에 가지지 않는 경우, 왼쪽만 노드가 달린 경우
			// 상위 노드는 좌측 노드를 가리켜야 한다.
			else if((*node)->right == NULL)
			{
				tree *tmp = *node;
				*node = (*node)->left;
				free(tmp);
			}
			// 좌측을 가지지 않는 경우, 오른쪽만 노드가 달린 경우
			// 상위 노드는 우측 노드를 가리켜야 한다.
			else if((*node)->left == NULL)
			{
				tree *tmp = *node;
				*node = (*node)->right;
				free(tmp);
			}
			else
			{	//What is condition.....
			// 트리의 왼쪽에서는 가장 큰 값, 트리의 오른쪽은 가장 작은 값을 찾아서
			// 부모에게 올려준다
			// node 의 주소를 던져줘서 node->data에 접근한다.
				two_node(&(*node)->right, node);
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


	printf("Delete Data 50\n");	
	del_node(&node, 50);

	print_tree(node);
	printf("\n");
	return 0;
}

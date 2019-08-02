/*W 개발자에게 있어서 머리 속 생각을 프로그램 코드로 바꾸는 것이 무엇보다 중요
	이것이 불가능하다면 단순한 코더가 되고 이것이 가능해진다면 비로소 그 때 개발자가 될 수 있다.
	자료구조를 학습하는 이유는 
	머리 속에서 생각한 내용을 
	코드로 변환하는 훈련련을 하는 일련의 절차.
	익숙해지면 이후에는 생각한 대부분을 프로그램 코드로 바꿀 수 있다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct __queue
{
	int data;
	struct __queue *link;
} queue;

queue *get_queue_node(void)
{
	queue *tmp = (queue *)malloc(sizeof(queue));
	tmp->link = NULL;

	return tmp;
}

void enqueue(queue **head, int data)
{
//	queue *tmp = *head;
//	*head = get_queue_node();

	if(*head == NULL)
	{
		*head = get_queue_node();
		(*head)->data = data;
	}
	else
		enqueue(&((*head)->link), data);
}
/*
void del_data(queue **head, int data)
{
	queue *tmp;
	if(data != (*head)->data)
	{
		del_data((&(*head)->link), data);
	}
	else
	{
		printf("Find Data = %d\n\n", data);
		tmp = *head;
		*head = (*head)->link;
		free(tmp);
	}
}
*/


//강사님 코드

void dequeue(queue **head, int data)
{
	queue *tmp = *head;

	if((*head)->data == data)
	{
		printf("**Find data %d**\n", (*head)->data);
		*head = (*head)->link;
		free(tmp);
		return;
	}
	dequeue(&(*head)->link, data);
}

void print_queue(queue *head)
{
	queue *tmp = head;
	
	while(tmp)
	{
		printf("tmp->data = %d\n", tmp->data);
		tmp = tmp->link;
	}
}

int main(void)
{
	int i;
	int arr[5] = {10, 30, 20, 40};
	queue *head = NULL;
	
	for(i = 1; i <= 4; i++)
		enqueue(&head, i * 10);

	print_queue(head);
	printf("\n");

//	printf("\n**Delete data 30**\n\n");

//	del_data(&head, 30);
	for(i = 0; i < 4; i++)
	{
		dequeue(&head, arr[i]);
		print_queue(head);
	}
	
	return 0;
}

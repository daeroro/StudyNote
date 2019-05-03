#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct __queue queue;

struct __queue
{
    int data;
    queue *link;
    void (*q)(queue **, int); // 구조체안에 함수포인터 선언
    queue (*(*get_q)(void)); 
    void (*dq)(queue **, int);
    void (*pq)(queue *);
};

queue *get_queue_node(void);
void dequeue(queue **, int);
void enqueue(queue **, int);
void print_queue(queue *);

queue *get_queue_node(void)
{
    queue *tmp = (queue *)malloc(sizeof(queue));

    tmp->q = enqueue;
    tmp->dq = dequeue;
    tmp->pq = print_queue;
    tmp->get_q = get_queue_node;

    tmp->link = NULL;

    return tmp;
}

void enqueue(queue **head, int data)
{
    cout << "enqueue called!" << endl;


    if(!(*head))
    {
        *head = get_queue_node();

        (*head)->data = data;
        return;
    }
    (*head)->q(&(*head)->link, data);

#if 0
    queue **tmp = head;

    while(*tmp)
        tmp = &(*tmp)->link;

    *tmp = get_node();
    (*tmp)->data = data;
#endif
}

void dequeue(queue **head, int data)
{
    queue *tmp = *head;
    if((*head)->data == data)
    {
        *head = (*head)->link;
        cout << "Delete Data : " << tmp->data << endl;
        // printf("data : %d\n",tmp->data);
        free(tmp);
        return;
    }
    (**head).dq(&(*head)->link, data);
}

void print_queue(queue *head)
{
    queue *tmp = head;

    while(head)
    {
        cout << "head->data = " << head->data << endl;
        head = head->link;
    }
}

int main(void)
{
    int i;
    int arr[5] = {10, 30, 20, 40};

    queue *head = (queue *)malloc(sizeof(queue));

    head->data = 10;
    head->get_q = get_queue_node; // 구조체 안에 함수포인터의 이름을 맵핑 해주는거에요 함수처럼 사용하기위해서 유사클래스에요 .
    head->dq = dequeue;
    head->q = enqueue;
    head->pq = print_queue;
    head->link = NULL;

    for(i = 2; i < 6; i++)
        head->q(&head, i * 10);

    head->pq(head);
    for(i = 0; i < 2; i++)
        head->dq(&head, arr[i]);

    cout << "After Delete" << endl;

    head->pq(head);

    return 0;
}

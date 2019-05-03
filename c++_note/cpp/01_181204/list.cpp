#include <iostream>

using namespace std;

typedef struct __list
{
    int data;
    struct __list *link;
    int (*a)(void); // 구조체 안에 함수포인터를 넣어서 함수를 불러내는 거에요.
    //(struct __list *)(*p)(void);
} list;

int test(void)
{
   cout << "test" << endl;
}

int main(void)
{
    list p = {0, NULL, test};
    p.a();

    return 0;
}

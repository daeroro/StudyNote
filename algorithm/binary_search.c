/*
  배열 arr[]에서 원하는 값을 binary search로 찾는 예제

  ## 미리 정렬이 되어 있어야 한다!

  _binary_search() :

  - 인자로 들어가는 수를 찾는다.
  - 존재하지 않으면 -1, 존재하면 인덱스를 반환
*/

#include <stdio.h>

int arr[10] = {0, 1, 2, 5, 6, 7, 8, 9, 10, 11};

int _binary_search(int left, int right, int fnum)
{
  if(left == right)
  {
    if(arr[left] == fnum)
      return left;
    else return -1;
  }
  else if(left > right) return -1;
  else
  {
    int mid = (left + right) / 2;

    if(arr[mid] == fnum) return mid;
    else if(arr[mid] < fnum) _binary_search(mid+1, right, fnum);
    else _binary_search(left, mid-1, fnum);
  }
}

int main(void)
{
  printf("find 5, index %d\n",_binary_search(0, 9, 5));
  printf("find 4, index %d\n",_binary_search(0, 9, 4));

  return 0;
}

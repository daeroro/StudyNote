#include <iostream>
#include <stack>

#include <cstdio>

using namespace std;

int main(void)
{
	stack<int> st;

	st.push(7);
	st.push(5);
	st.push(4);
	
	while(!st.empty())
	{
		printf("%d ", st.top());
		st.pop();
		printf("\n");
	}	

	return 0;
}

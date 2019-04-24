#include<stdio.h>
#include<stack>

void move(int data, char from, char to)
{
	printf("move disk#%d from %c to %c\n", data, from, to);
}

// 将1~a借助bri从src移动到dst，保持小的数在大的数上面
void hanoi(int a, char src, char bri, char dst)
{
	// (1~a, 0, 0)
	if(a==1)
	{
		move(1, src, dst);
		return;
	}
	hanoi(a-1, src, dst, bri);
	// (a, 1~a-1, 0)
	move(a, src, dst);
	// (0, 1~a-1, a)
	hanoi(a-1, bri, src, dst);
	// (0, 0, 1~a)
}

struct op{
	int start, end;
	char src, bri, dst;
	op(int st, int e, char s, char b, char d):start(st),end(e),src(s),bri(b),dst(d){}
};

void hanoi2(int n, char src, char bri, char dst)
{
	std::stack<struct op> st;
	st.push(op(1, n, src, bri, dst));
	while(!st.empty())
	{
		struct op tmp=st.top();
		st.pop();
		
		if(tmp.end==tmp.start)
		{
			move(tmp.end, tmp.src, tmp.dst);
		}
		else
		{
			st.push(op(tmp.start, tmp.end-1, tmp.bri, tmp.src, tmp.dst));
			st.push(op(tmp.end, tmp.end, tmp.src, tmp.bri, tmp.dst));
			st.push(op(tmp.start, tmp.end-1, tmp.src, tmp.dst, tmp.bri));
		}
	}
}

int main()
{
	{
		hanoi(3, 'A', 'B', 'C');
		hanoi2(3, 'a', 'b', 'c');
	}
	return 0;
}
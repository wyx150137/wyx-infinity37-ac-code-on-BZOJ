
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <queue>
#define N 200000+5
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data
{
	int pos;
	int val;
	bool operator < (const data &z)const
	{
		return val < z.val;
	}
	data () {}
	data (int _pos,int _val)
	:pos(_pos),val(_val){}
};

priority_queue<data>Q;

int L[N],R[N],a[N];
bool del[N];
int ans = 0;

void work()
{
	while(del[Q.top().pos])
		Q.pop();
	data tmp = Q.top();Q.pop();
	int tt = tmp.pos;
	ans += a[tt];
	a[tt] = a[L[tt]] + a[R[tt]] - a[tt];
	Q.push(data(tt,a[tt]));
	R[L[L[tt]]] = tt;
	L[R[R[tt]]] = tt;
	del[R[tt]] = del[L[tt]] = 1;
	L[tt] = L[L[tt]];
	R[tt] = R[R[tt]];
}

int main()
{
	int n = read(), m = read();
	if(m > (n>>1)){puts("Error!");return 0;}
	for(int i=1;i<=n;++i)
	{
		a[i] = read();
		Q.push(data(i,a[i]));
		L[i] = i-1;
		R[i] = i+1;
	}
	L[1] = n;
	R[n] = 1;
	while(m--)
		work();
	cout<<ans;
}

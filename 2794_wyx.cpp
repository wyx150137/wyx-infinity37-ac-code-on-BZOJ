
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6;
using namespace std;

struct ask
{
	int k,m,s;
	int id;
}q[N+5];

bool cmp1(const ask &a,const ask &b)
{
	return a.m < b.m;
}

int f[N];

struct data
{
	int a,b,c;
	bool operator < (const data &z)const
	{
		return a < z.a;
	}
}a[1000+5];

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool ans[N];

int main()
{
	int n = read();
	for(int i=1;i<=n;++i) a[i].c = read(),a[i].a = read(),a[i].b = read();
	int Q = read();
	for(int i=1;i<=Q;++i)
		q[i].m = read(), q[i].k = read(),q[i].s = read(), q[i].id = i;
	sort(q+1,q+Q+1,cmp1);
	sort(a+1,a+n+1);
	int j = 1;
	f[0] = 1e9;
	for(int i=1;i<=Q; ++i)
	{
		while(a[j].a <= q[i].m && j<=n)
		{
			for(int k = N; k >=a[j].c;--k)
				f[k] = max(f[k],min(f[k-a[j].c],a[j].b));
			j ++;
		}
		if(f[q[i].k]  > q[i].m + q[i].s)
			ans[q[i].id] = 1;
	}

	for(int i=1;i<=Q;++i)	
		printf("%s\n",ans[i] ? "TAK" : "NIE");
}

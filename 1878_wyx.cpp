
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define lowbit(x) ((x)&(-x))
#define N 1000000+5
#define M 200000+5
using namespace std;
int a[N],n;
int next[N],last[N];
int tmp[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch - '0';ch = getchar();}
	return x*f;
}

struct ask
{
	int l,r;
	int id;
	int ans;
	bool operator < (const ask &z)const
	{
		return l ^ z.l ? l < z.l : r < z.r;
	}
}q[M];

bool cmp(const ask &a,const ask &b)
{
	return a.id < b.id;
}

void updata(int x,int num)
{
	while(x<=n)
	{
		a[x]+=num;
		x+=lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += a[x];
		x-=lowbit(x);
	}
	return ans;
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i)
		tmp[i] = read();
	for(int i=n;i>=1;--i)
		next[i] = last[tmp[i]],last[tmp[i]] = i;
	int m = read();
	for(int i=1;i<=m;++i)
		q[i].l=read(),q[i].r=read(),q[i].id = i;
	sort(q+1,q+m+1);
	//puts("*************");
	for(int i=1;i<N;++i)
		if(last[i])
			updata(last[i],1);
	//puts("********");
	int l = 1;
	for(int i=1;i<=m;++i)
	{

		while(l<q[i].l)
		{
			if(next[l])
				updata(next[l],1);
			l++;
		//	puts("-------------");
		}
		q[i].ans = ask(q[i].r)-ask(q[i].l-1);
	}
	sort(q+1,q+m+1,cmp);
	for(int i=1;i<=m;++i)
		printf("%d\n",q[i].ans);
}


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
#define lowbit(x) ((x)&(-x))
const int N = 1e6;
using namespace std;
LL ans;
int tr[N+5];

void change(int x,int tt)
{
	while(x <= N)
	{
		tr[x] += tt;
		x += lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += tr[x];
		x -= lowbit(x);
	}
	return ans;
}

void Tchange(int x)
{
	while(x <= N)
	{
		tr[x] = 0 ;
		x += lowbit(x);
	}
}

struct data
{
	int x,times;
	int pos,tmp;
	bool operator < (const data &z)const
	{
		return pos < z.pos;
	}
}a[N+5];

bool cmp1(const data &a,const data &b)
{
	return a.times ^ b.times ? a.times > b.times : a.pos < b.pos;
}

bool cmp2(const data &a,const data &b)
{
	return a.times < b.times;
}

void solve(int L,int R)
{
	if(L==R) return;
	int mid = (L+R) >> 1;
	solve(L,mid);
	sort(a+L,a+mid+1);
	sort(a+mid+1,a+R+1);
	for(int i=L,j=mid+1;j<=R;++j)
	{
		while(a[i].pos < a[j].pos &&  i <= mid) 
		{
			change(a[i].x,1);
			i ++;
		}
		a[j].tmp += ask(N) - ask(a[j].x);
	}
	for(int i=L;i<=mid;++i) Tchange(a[i].x);
	for(int i=mid,j=R;j>=mid+1;--j)
	{
		while(a[i].pos > a[j].pos && i >= L)
		{
			change(a[i].x,1);
			i --;
		}
		a[j].tmp += ask(a[j].x);
	}
	for(int i=L;i<=mid;++i) Tchange(a[i].x);
	sort(a+L,a+R+1,cmp1);
	solve(mid+1,R);
}

int T[N+5];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read(), m = read();
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].times = m + 1, T[a[i].x] = a[i].pos = i;
	LL ans = 0;
	for(int i=1;i<=n;++i)
	{
		ans = ans + ask(N) - ask(a[i].x);
		change(a[i].x,1);
	}

	memset(tr,0,sizeof tr);
	for(int i=1;i<=m;++i)
	{
		int x = read();
		a[T[x]].times = i;
	}

	sort(a+1,a+n+1,cmp1);
	solve(1,n);
	sort(a+1,a+n+1,cmp2);
	for(int i=1;i<=m;++i)
	{
		printf("%lld\n",ans);
		ans -= a[i].tmp;
	}
}

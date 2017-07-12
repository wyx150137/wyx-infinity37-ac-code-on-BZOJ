
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 5001000
#define mod 9999991

typedef long long LL;
using namespace std;

int i,head[mod],nxt[N],cnt;
long long v[N];

inline void add(LL x)
{
	int T=x%mod,i;
	cnt++;nxt[cnt]=head[T];
	head[T]=cnt;v[cnt]=x;
}

LL q[N],h,t;

inline void check(LL x)
{
	int T=x%mod,i;
	for(int i=head[T];i;i=nxt[i]) if(v[i]==x) return;
	cnt++;nxt[cnt]=head[T]; head[T]=cnt;v[cnt]=x; t++;q[t]=x;
}

int n,k;

inline LL dec()
{
	LL x=0;char ch = getchar();
	while(ch < '0' || ch > '9'){ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+ch-'0';ch = getchar();}
	return x;
}

LL S,E;
LL a[N];

int main()
{

	scanf("%d%d",&n,&k);
	int nk=n*k+5;
	LL x,y;
	S=dec(), E=dec();

	for(i=1;i<=k;i++)
	{
		a[i]=dec();
		add(a[i]);
	}

	h=t=1;q[1]=S;
	add(S);

	while(h<=t&&t<=nk)
	{
		x = q[h++];
		if(x==E) {
			puts("TAK");
			return 0;
		}
		for(i=0;i<n;i++)
			check(x^(1LL<<i));
	}

	if(t<=nk) {
		puts("NIE");
		return 0;
	}

	h=t=1;q[1]=E;
	cnt=0;
	for(i=0;i<mod;i++) head[i]=0;
	for(i=1;i<=k;i++) add(a[i]); add(E);

	while(h<=t&&t<=nk)
	{
		x = q[h++];
		if(x==S) {
			puts("TAK");
			return 0;
		}
		for(i=0;i<n;i++) check(x^(1LL<<i));
	}

	if(t<=nk) puts("NIE");
	else puts("TAK");
}

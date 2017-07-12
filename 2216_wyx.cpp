
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>
const int N = 500000+5;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n;
int a[N];
double f[N],g[N];

inline double calc(int j,int i)
{
	return a[j]+sqrt(abs(i-j))-a[i];
}

struct data
{
	int l,r,p;
}q[N];

int find(data t,int x)
{
	int l = t.l,r = t.r;
	while(l<=r)
	{
		int mid = (l+r) >> 1;
		if(calc(t.p,mid) > calc(x,mid)) l = mid + 1;
		else r = mid - 1;
	}
	return l;
}

void dp(double *f)
{
	int l = 1;
	int r = 0;
	for(int i=1;i<=n;++i)
	{
		q[l].l ++;
		if( l<=r && q[l].r < q[l].l) l++;
		if( l>r || calc(i,n) > calc(q[r].p,n))
		{
			while(l<=r && calc(q[r].p,q[r].l) < calc(i,q[r].l)) r--;
			if(l>r) q[++r] = (data){i,n,i};
			else
			{
				int t = find(q[r],i);
				q[r].r = t - 1;
				q[++r] = (data){t,n,i};
			}
		}
		f[i] = calc(q[l].p,i);
	}
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i) a[i] = read();
//	puts("*******");
	dp(f);
	for(int i=1;i<=n/2;++i) swap(a[i],a[n-i+1]);
	dp(g);
	for(int i=1;i<=n;++i)
	{
		int tt = (int)ceil(max(f[i],g[n-i+1]));
		if(tt < 0) tt = 0;
		printf("%d\n",tt);
	}
}

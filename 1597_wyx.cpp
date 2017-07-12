
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf = 0x7fffff;
const int N = 50000+5;
typedef long long LL;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data
{
	LL x,y;
	bool operator < (const data &z)const
	{
		return x ^ z.x ? x < z.x : y < z.y;
	}
}a[N];

LL f[N];
int q[N],l=1,r;

inline double delta(int x,int y)
{
	return (double)(f[x-1]-f[y-1]) / (double) (a[x].y - a[y].y);
}

int main()
{
	int n = read();
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].y = read();
	
	sort(a+1,a+n+1);
	int tt = 0;

	for(int i=1;i<=n;++i)
	{
		while(a[tt].y <= a[i].y && tt) tt--;
		a[++tt] = a[i];
	}

	for(int i=1;i<=tt;++i)
	{
		while(l<r && delta(q[r-1],q[r]) < delta(q[r],i)) --r;q[++r] = i;
		while(l<r && delta(q[l],q[l+1]) > (double)(-a[i].x)) ++l;
		f[i] = f[q[l]-1] + a[q[l]].y* a[i].x;
	}

	cout << f[tt] << endl;
}


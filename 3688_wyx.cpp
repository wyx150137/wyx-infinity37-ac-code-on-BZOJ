
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define mod 100007
#define N 1000000+5
#define lowbit(x) ((x)&(-x))
using namespace std;
struct Point
{
	int x,y;
	bool operator < (const Point &z)const
	{
		return x < z.x;
	}
}a[N];

int f[11][N],g[11][N],n,k;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void updataf(int x,int k,int num)
{
	while(x<=N)
	{
		(f[k][x] += num)%=mod;
		x += lowbit(x);
	}
}

void updatag(int x,int k,int num)
{
	while(x<=N)
	{
		(g[k][x] += num)%=mod;
		x += lowbit(x);
	}
}

int askf(int x,int k)
{
	int ans = 0;
	while(x)
	{
		(ans += f[k][x])%=mod;
		x -= lowbit(x);
	}
	return ans;
}

int askg(int x,int k)
{
	int ans = 0;
	while(x)
	{
		(ans += g[k][x])%=mod;
		x -= lowbit(x);
	}
	return ans;
}

int main()
{
	n = read();k = read();
	int MAX = 0;
	for(int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read(),MAX = max(MAX,a[i].y);

	sort(a+1,a+n+1);
	//for(int i=1;i<=n;++i)
	//	cout<<a[i].x<<" "<<a[i].y<<endl;
	for(int i=1;i<=n;++i)
	{
		updataf(a[i].y,0,1),updatag(a[i].y,0,1);
		for(int j=1;j<=k;j++)
		{
			int fx = askg(a[i].y-1,j-1)+askf(a[i].y-1,j);
			int gx = askf(MAX,j-1)-askf(a[i].y,j-1)+askg(MAX,j)-askg(a[i].y,j);
			fx %= mod , (gx+=mod) %= mod;
			updataf(a[i].y,j,fx);
			updatag(a[i].y,j,gx);
		}
	}

	int tt = askg(MAX,k);
	//cout<<tt<<endl;
	int tx = askf(MAX,k);
	//cout<<tx<<endl;
	tt += tx;
	(tt += mod)%=mod;
	tt %= mod;
	cout<<tt;
}

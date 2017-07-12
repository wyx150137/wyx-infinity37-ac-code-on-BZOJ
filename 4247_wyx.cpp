
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 2000+5
using namespace std;
typedef long long LL;
const LL inf = -10000000000ll;
int n;
LL f[N][N];

struct data
{
	int lmt;
	LL val;
	bool operator < (const data &z)const
	{
		return lmt > z.lmt;
	}	
}a[N];

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x * f;
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i)
		a[i].lmt = read(),a[i].val = read();
	sort(a+1,a+n+1);
	for(int i=0;i<=n;++i)
		for(int j=0;j<=n;++j)
			f[i][j] = inf;
	LL ans = 0ll;
	f[0][0] = f[0][1] = 0;
	for(int i=1;i<=n;++i)
		for(int j=0;j<=n;++j)
			if(f[i-1][j]!=inf)
			{
				f[i][j] = max(f[i][j],f[i-1][j]);
				ans = max(ans,f[i][j]);
				if(j && j+a[i].lmt-1 >= 0)
				{
					if(j+a[i].lmt-1<=n)
						f[i][j+a[i].lmt-1] = max(f[i-1][j]+a[i].val,f[i][j+a[i].lmt-1]);
					else
						f[i][n] = max(f[i][n],f[i-1][j]+a[i].val);
					ans = max(ans,f[i][min(j+a[i].lmt-1,n)]);
				}
			}
	cout<<ans;
}

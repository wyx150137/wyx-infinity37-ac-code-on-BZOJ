
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 50000+5
#define M 200000+5
const int mod = 10007;
using namespace std;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N];
int sum[N];
int n ,m;
int f[2][N];
int g[N];

bool check(int mid)
{
	int ans = 0 ;
	int cnt = 0;
	for(int i=1;i<=n;++i)
	{
		ans += a[i];
		if(ans > mid)
			ans = a[i],++cnt;
		if(cnt >= m)return false;
		if(ans > mid)return false;
	}
	return  true;
}

int main()
{
	n = read(),m = read();++m;
	for(int i=1;i<=n;++i)
		a[i] = read(),sum[i] = sum[i-1]+a[i];
	int l = 0 , r = sum[n];
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(mid))
			r = mid;
		else l = mid + 1;
	}
	cout<<l<<" "; 

	for(int i=1;i<=n;++i)
		if(sum[i]<=l)
			f[1][i] = 1;

	int ans2 = 0;
	for(int j=2;j<=m;++j)
	{
		int o = j & 1;
		int op = (j+1)&1;
		memset(f[o],0,sizeof f[o]);
		memset(g,0,sizeof g);
		int k = n + 1;
		for(int i=n;i>1;--i)
		{
			if(i>k)
				(f[o][i] += (g[k]-g[i]+mod)%mod)%=mod;
			else k = i;
			while(k>1 && sum[i]-sum[k-1] <= l)
			{
				k --;
				(f[o][i] += f[op][k])%=mod;
				(g[k] = g[k+1] + f[op][k])%=mod;
			}
		}
		(ans2 += f[o][n])%=mod;
	}
	cout<<ans2;

}

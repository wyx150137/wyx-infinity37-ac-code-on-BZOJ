
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
using namespace std;

long long a[N];
long long f[N];
long long sum[N];
long long q[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read(), k = read();
	for(int i=1;i<=n;++i)a[i] = read(),sum[i]=sum[i-1]+a[i];
	int  l=0,r=0;
	for(int i=1;i<=n;++i)
	{
		while(r-l>=1&&f[i-2]-sum[i-1]>f[q[r]-1]-sum[q[r]])
			r--;
		q[++r] = i-1;
		while(i-q[l+1]>k)
			l++;
		f[i] = max(f[i-1],f[q[l+1]-1]+sum[i]-sum[q[l+1]]);
	}
	cout<<f[n];
}

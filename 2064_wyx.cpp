
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
using namespace std;
const int Maxn = (1<<21)+5;
int F[Maxn],sum[Maxn];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read();for(int i=1;i<=n;++i) sum[1<<(i-1)] = read();
	int m = read();for(int i=1;i<=m;++i) sum[1<<(i+n-1)] = -read();
	n += m;
	int Max = (1<<n) - 1;
	for(int i=1;i<=Max;++i)
	{
		int x = lowbit(i);
		sum[i] = sum[x] + sum[i^x];
		for(int j=0;j<n;++j)
			if(i&(1<<j))
				F[i] = max(F[i],F[i^(1<<j)]);
		if(!sum[i]) F[i]++;
	}
	cout << n - 2*F[Max];
}

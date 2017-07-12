
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e4+5;
int ans = 0x7fffffff;
int a[N];
int F[N],G[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
	int n = read();
	for(int i=0;i<n;++i) a[i] = read()*2;
	sort(a,a+n);int tt = 1;
	for(int i=1;i<n;++i) if(a[i] != a[i-1]) a[tt++] = a[i];n = tt;
	memset(F,0x7f,sizeof F);
	memset(G,0x7f,sizeof G);
	int l = 0;F[l] = -2;
	int r = 1;

	while(r < n)
	{
		while(l+1 < r && a[r] - a[l+1] > F[l+1] + 2) l ++;
		F[r] = min(a[r]-a[l],F[l+1] + 2); ++r;
	}

	r = n - 1;G[r] = -2;
	l = n - 2;

	while(l >= 0)
	{
		while(l+1 < r && a[r-1] - a[l] > G[r-1] + 2) r--;
		G[l] = min(a[r]-a[l],G[r-1] + 2); l --;
	}
	for(l=0,r=n-1;l < r;)
	{
		ans = min(ans,max((a[r]-a[l])/2,2+max(F[l],G[r])));
		if(F[l+1] < G[r-1]) l++;
		else r --;
	}
	printf("%.1lf",(double)ans/2);
}
 

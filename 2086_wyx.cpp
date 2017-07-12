
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 1000000+5
const long long inf = 100000000000000+5;
using namespace std;

int n,m;
int a[N];
int stack[N];
long long sum[N];
int top;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch >'9' ){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void solve(int x)
{
	int ans=0;
	for(int i=1;i<=n;i++)
		sum[i]=sum[i-1]+a[i]-x;
	top=0;
	for(int i=1;i<=n;i++)
		if(sum[stack[top]]>sum[i])
			stack[++top]=i;
	for(int i=n,j = top;i>=0;i--)
	{
		while(j && sum[i]>=sum[stack[j-1]])
			j--;
		ans=max(ans,i-stack[j]);
	}
	printf("%d",ans);
}

int main()
{
	n = read(),m = read();
	for(int i=1;i<=n;++i)
		a[i] = read();
	for(int i=1;i<=m;++i)
	{
		int tt = read();
		solve(tt);
		if(i!=m)
			cout<<" ";
		else puts("");
	}
}

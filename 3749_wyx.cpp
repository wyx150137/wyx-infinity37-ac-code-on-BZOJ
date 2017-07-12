
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1000000+5;
using namespace std;

int n;
int a[N];

int path[N][5],ans[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool work(int x)
{
	memset(path,0,sizeof path);
	path[1][x] = 1;
	for(int i=2;i<=n;++i)
	{
		if(path[i-1][1] && (a[i-1] <= (a[i] << 1))) path[i][1] = 1;
		if(path[i-1][4] && (a[i-1] <= a[i])) path[i][1] = 4;
		if(path[i-1][2] && (a[i-1]<<1) >= a[i]) path[i][2] = 2;
		if(path[i-1][3] && (a[i-1] >= a[i])) path[i][2] = 3;
		if(path[i-1][1] && (a[i-1] <= a[i])) path[i][3] = 1;
		if(path[i-1][4] && (a[i-1]<<1) <= a[i]) path[i][3] = 4;
		if(path[i-1][2] && (a[i-1]>=a[i])) path[i][4] = 2;
		if(path[i-1][3]&&(a[i-1]>=a[i]*2))path[i][4]=3;
	}
	if(path[n][x] == 0) return  0;
	for(int i=n;i>=1;--i)
	{
		if(x == 1) ans[i-1] = (i-1) %(n-1) + 1;
		if(x == 2) ans[i] = (i-1) %(n-1) + 1;
		if(x == 3) ans[i-1] = ans[i] = (i-1)%(n-1) + 1;
		x = path[i][x];
	}
	for(int i=1;i<n-1;++i) printf("%d ",ans[i]);
	return printf("%d\n",ans[n-1]), 1;
}

int main()
{
	n = read();
	for(int i=1;i<=n;++i) a[i] = read();
	a[++n] = a[1];
	for(int i=1;i<=4;++i) if(work(i)) return 0;
	puts("NIE");
	return 0;
}

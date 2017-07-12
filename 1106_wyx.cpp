
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 100000+5
using namespace std;
#define lowbit(x)  ((x)&(-x))
int a[N];
int last[N];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

void updata(int x,int num)
{
	while(x < N)
	{
		a[x] += num;
		x += lowbit(x);
	}
}

int ask(int x)
{
	int ans = 0;
	while(x)
	{
		ans += a[x];
		x -= lowbit(x);
	}
	return ans;
}

int main()
{
	int n = read();
	int ans = 0;
	n<<=1;
	for(int i=1;i<=n;++i)
	{
		int x = read();
		if(last[x])
		{
			ans += ask(i) - ask(last[x]-1)-1;
			updata(last[x],-1);
			last[x] = 0;
		}
		else
			last[x] = i,updata(i,1);
	}
	cout<<ans;
}

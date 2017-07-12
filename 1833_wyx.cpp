
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
using namespace std;

LL ans[10],F[10];

inline void divide(LL x,LL times)
{
	while(x)
	{
		ans[x%10] += times;
		x /= 10;
	}
}

void solve(LL x,int flag)
{
	LL pos=10;
	int i;
	for(i=1;pos<x;pos*=10,++i)
	{
		for(int j=0;j<=9;++j) ans[j] += F[i-1]*9*flag;
		for(int j=1;j<=9;++j) ans[j] += pos/10*flag;
	}
	LL now = (pos/=10); --i;
	while(now < x)
	{
		while(pos + now <= x)
		{
			LL tmp = now / pos;
			divide(tmp,pos*flag);
			for(int j=0;j<=9;++j) ans[j] += F[i]*flag;
			now += pos;
		}
		pos /= 10; -- i;
	}
}

int main()
{
	LL a,b,pos;cin >> a >> b;
	F[1] = 1; int i;
	for(i=2,pos=10;i<=12;++i,pos*=10) F[i] = F[i-1]*10 + pos;
	solve(b+1,1);
	solve(a,-1);
	for(int i=0;i<9;++i)
		printf("%lld ",ans[i]);
	cout << ans[9];
}

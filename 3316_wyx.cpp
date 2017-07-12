
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define N 200000+5
#define eps 2e-5
typedef long long LL;
typedef long double LD;
using namespace std;
LD sum[N];
LD down,up;
int que[2][N],n;
int zuo[2],you[2];
int a[N];
int L,R;

LL gcd(LL a,LL b)
{
	return b ? (gcd(b,a%b)) : a;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool check(LD x)
{
	for(int i=1;i<=n;++i)
		sum[i] = sum[i-1] + a[i] - x;
	you[0] = you[1] = zuo[0] = zuo[1] = 0;
	for(int i=L;i<=n;++i)
	{
		int *q = ::que[i&1];
		int &r = ::you[i&1];
		int &l = ::zuo[i&1];
		int x = i - L;
		while(r-l>=1&&sum[q[r]]>sum[x])
			r --;
		q[++r] = x;
		while(i-q[l+1]>R)
			l ++;
		if(sum[i]-sum[q[l+1]]>=0)
		{down = i - q[l+1];return true;}
	}
	return false;
}

int main()
{
	n = read(),L = read() , R = read();
	if(L&1)L++;if(R&1)R--;
	for(int i=1;i<=n;++i)a[n+i] = a[i] = read();
	n<<=1;
	LD tmpl = 0;
	LD tmpr = 1e10;
	while(tmpr-tmpl>eps)
	{
		LD mid = (tmpl+tmpr)/2;
		if(check(mid))
			tmpl = mid;
		else tmpr = mid;
	}
	LD ans = (tmpl+tmpr)/2;
	ans = ans * down + 0.5;
	long long tmp = gcd((LL)ans,(LL)down);
	LL tmp1 = (LL)ans;
	LL tmp2 = (LL)down;
	tmp2 /= tmp;
	tmp1 /= tmp;
	if(tmp2 == 1)
		printf("%lld",tmp1);
	else
		printf("%lld/%lld",tmp1,tmp2);
}

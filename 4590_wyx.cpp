
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
#define N 100000+5
using namespace std;

long long a[N],l,k;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

long long check(long long mid)
{	
	long long ans = 0;
	long long cnt = 0;
	for(int i=1;i<=l;++i)
	{
		ans += a[i];
		if(ans >= mid)
			ans = 0,cnt++;
		ans = max(ans,0);
	}
	return cnt;
}

int main()
{
	int tmp = 0;
	l = read(),k=read();
	for(int i=1;i<=l;++i)a[i] = read(),tmp+=a[i];
	long long l = 1 ,r = 1e15;
	while(l<r)
	{
		long long mid = (l + r)>>1;
		if(check(mid)<=k)
			r = mid;
		else l = mid + 1;
	}
	long long ans1 = l;
	l = 1 , r = 1e15;
	while(l<r)
	{
		long long mid = (l+r)>>1;
		int tt = check(mid);
		if(tt==k)
			l = mid + 1;
		else if(tt<k)
			r = mid;
		else l = mid + 1;
	}
	long long ans2 = l-1;
	if(check(ans1)!=k || check(ans2)!=k || ans1 <=0 || ans2 <=0)
		puts("-1");
	else
		cout<<ans1<<" "<<ans2;
}	

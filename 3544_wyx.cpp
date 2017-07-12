
#include <set>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200000+5;
typedef long long LL;
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL sum[N];
set <LL> s;

int main()
{
	int n = read(); LL m = read();
	LL ans = 0,p;
	for(int i=1;i<=n;++i) sum[i] = (read() % m + m )% m;
	for(int i=1;i<=n;++i) sum[i] = (sum[i-1] + sum[i]) % m,ans = max(ans,sum[i]);
	s.insert(0ll);
	for(int i=1;i<=n;++i)
	{
		if(s.upper_bound(sum[i])!= s.end())
		{
			p = *s.upper_bound(sum[i]);
			ans = max(ans,(sum[i]-p+m)%m);
		}
		s.insert(sum[i]);
	}
	cout << ans << endl;
}

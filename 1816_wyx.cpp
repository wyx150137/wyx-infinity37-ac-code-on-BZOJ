
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define N 50+5
using namespace std;
#define min(a,b) ((a)<(b)?(a):(b))
long long a[N],n,m;
bool check(long long mid)
{
	long long t = min (mid,m);
	for(int i=1;i<=n;++i)
		if(a[i]<=mid)
			t -= mid - a[i];
	if(t<0) return false;
	return true;
}
int main()
{
	cin>>n>>m;	
	for(int i=1;i<=n;++i)cin>>a[i];
	long long l = 0 , r = 10000000000;
	while(l<r)
	{
		long long mid = (l+r)>>1;
		if(check(mid))
			l = mid+1;
		else r = mid;
	}
	cout << l-1;
}

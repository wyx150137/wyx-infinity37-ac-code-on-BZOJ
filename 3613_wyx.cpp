
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

int a[5000000+5];
long long A,B,C,D,n;
int mod;

long long calc(long long x)
{
	long long ans = D;
	long long tmp = x;
	(ans += tmp*C)%=mod;
	(tmp*=x)%=mod;
	(ans += tmp*B)%=mod;
	(tmp*=x)%=mod;
	(ans += tmp*A)%=mod;
	return ans;
}

void init()
{
	for(int i=2;i<=n;++i)
		a[i] = (calc(a[i-1])+calc(a[i-2]))%mod;
}

bool check(int mid)
{
	long long MAX = 0;
	for(int i=1;i<=n;++i)
	{
		MAX = max(MAX,a[i]-mid);
		if(MAX > a[i] + mid)
			return false;
	}
	return true;
}

int main()
{
	cin>>n>>A>>B>>C>>D>>a[1]>>mod;
	init();
	int l = 0;
	int r = mod - 1;
	//for(int i=1;i<=n;++i)
	//	cout<<a[i]<<" ";
	//puts("");
	while(l<r)
	{
		int mid = (long long)(l+r)>>1;
		if(check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	cout<<l<<endl;

}

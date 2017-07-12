
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
long long a[250001],cnt;
bool check(long long x)
{
	long long i;
	for(i=1;i<=cnt;i++)
		if(a[i]%x==0) 
			return false;
	return true;
}
long long gcd(long long a,long long b)
{
	if(a==0) return b;
	return gcd(b%a,a);
}
int main()
{
	long long n,k; cin >> n >> k;
	for(int i=1;i<=k;i++)
		scanf("%lld",&a[i]);
	long long ans=n;
	long long i = 1;
	for(i=1;i<=k;i++)
		a[i]=gcd(n,a[i]);
	sort(a+1,a+k);
	for(i=1;i<k;i++)
		if(a[i]!=a[i-1])
			a[++cnt] = a[i];

	for(i=1;i<=sqrt(a[k]);i++)
		if(a[k]%i==0)
		{
			if(check(i)) {ans=n/i;break;}
			else if(check(a[k]/i)) ans=n/a[k]*i;
		}
	cout << ans << endl;
}

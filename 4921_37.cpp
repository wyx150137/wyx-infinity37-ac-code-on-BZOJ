
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int mod = 998244353;
int f[N],ls[N],a[N];
int gcd(int x,int y)
{
	if(y==0)return x;
	return gcd(y,x%y);
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		f[i] = gcd(f[i-1],a[i]);
	}
	for(int i = 2;i<= n;i++)
		if(f[i]==f[i-1])ls[i] = ls[i-1];
		else ls[i] = i-1;
	ls[0] = -1;
	int ans = 0,now = 0;
	for(int i = n;i>= 2;i--)
	{
		now = gcd(now,a[i]);
		for(int j = i-2;j>= 0;j=ls[j])
			ans = (ans+(ll)(j-ls[j])*gcd(now,f[j])%mod)%mod;
		if(i==n)ans = (ans-now+mod)%mod;
	}
	for(int i = 2;i<= n-1;i++)
		(ans+=f[i])%=mod;
	printf("%d\n",ans);
	return 0;
}
﻿

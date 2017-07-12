
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 10000000+5;
const int mod = 100000001;
typedef long long LL;
using namespace std;

int n,a,b,c,A[N];

int main()
{
	double ans = 0;
	cin >> n >> a >> b >> c >> A[1];
	for(int i=2;i<=n;++i) A[i] = ((LL)A[i-1]*a+b)%mod;
	for(int i=1;i<=n;++i) (A[i] %= c) += 1;
	A[0] = A[n];
	for(int i=1;i<=n;++i)
		ans += 1.0/max(A[i-1],A[i]);
	printf("%.3lf",ans);
}

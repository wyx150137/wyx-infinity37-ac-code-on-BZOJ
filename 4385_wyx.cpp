
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 2000000+5;
using namespace std;
typedef long long LL;

LL q[N];
int l,r;
LL sum[N];
LL f[N],a[N];

inline LL read()
{
	LL x = 0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main()
{
//	freopen("ks.in","r",stdin);
//	freopen("ks.out","w",stdout);
	int n = read();
	LL p = read();
	int d = read();
	for(int i=1;i<=n;++i) a[i] = read(), sum[i] = a[i] + sum[i-1];
	for(int i=1;i<=n;++i) f[i] = sum[i+d-1] - sum[i-1];
	int ans = d;
	l = 1;
	r = 1;
	q[r] = 1;
	LL sum = f[1];
	for(int i=1,j=1;j<=n-d+1;)
	{
		while(sum - f[q[l]] <= p && j <= n-d+1){
			j ++;
			while(l <= r && f[q[r]] <= f[j] )--r;
			q[++r] = j; 
			sum += a[j+d-1];
		}
//		cout << i <<  " " << j << endl;
		ans = max(ans,j-i+d-1);
		while(sum - f[q[l]] > p && i<=j){
			while(l<=r && q[l]<=i) ++l;
			sum -= a[i++];
		}
	}
	cout << ans << endl;
}

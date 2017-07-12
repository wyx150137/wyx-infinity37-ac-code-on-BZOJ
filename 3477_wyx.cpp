
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const double eps = 1e-5;
const double inf = 100000000.0;
const int N = 100000+5;
int a[N],n;
double b[N];


inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch=='-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

bool check(double tmp)
{
	double sum = 0;
	for(int i=1;i<=n;++i)
		b[i] = 1.0*a[i] - tmp,sum+=b[i];
	double ans = -inf,tt = 0;
	for(int i=2;i<n;++i)
	{
		tt += b[i];
		ans = max(tt,ans);
		if(tt < 0)tt = 0;
	}
	if(ans > sum)return true;
	else return false;
}

int sum[N];

void cheat()
{
	for(int i=1;i<=n;++i)
		a[i] = read(),sum[i] = sum[i-1] + a[i];
	double ans = 0x7ffff;
	for(int i=2;i<n;++i)
		for(int j=2;j<=i;++j)
		{
			double tmp = 1.0*(sum[i]-sum[j-1]);
			tmp = 1.0*sum[n] - tmp;
			tmp /=  (n-(i-j+1));
			ans = min(ans,tmp);
		}
	printf("%.3lf",ans);
}

int main()
{
	n = read();
	if(n<=1000)
	{
		cheat();
		return 0;
	}
	double tmp = 0;
	for(int i=1;i<=n;++i)
		a[i] = read(),tmp+=1.0*a[i];
	double l = 0,r = tmp/(1.0*n);
	int times = 0;
	while(r-l>eps)
	{
		double mid = (l+r)/2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.3lf",l);
}

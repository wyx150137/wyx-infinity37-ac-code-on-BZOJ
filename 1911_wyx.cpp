
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
typedef long long LL;
const int N = 1000000+5;
using namespace std;

inline LL P(int x)
{
	return (LL)(x)*x;
}

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL F[N];
int n,a,b,c;
LL sum[N];

inline double delta(int k,int j)
{
	return (((1.0*F[j]+1.0*a*P(sum[j]))-(1.0*F[k]+1.0*a*P(sum[k])))/(sum[j]-sum[k])-b)/(2.0*a);
}

int q[N];

int main()
{
	n = read(), a = read(), b = read(), c = read();
	for(int i=1;i<=n;++i) sum[i] = sum[i-1] + read();
	int l=0,r=0;
	for(int i=1;i<=n;++i)
	{
		while(l<r && delta(q[l],q[l+1]) < sum[i]) l++;
		F[i] = F[q[l]] + a*P(sum[i]-sum[q[l]]) + b*(sum[i]-sum[q[l]]) + c;
		while(l<r && delta(q[r-1],q[r]) > delta(q[r],i)) r --;
		q[++r] = i;
	}
	cout << F[n] << endl;
}

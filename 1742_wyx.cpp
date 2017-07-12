
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1000+5;
const LL inf = 1000000000000ll;
#define max(a,b) ((a)>(b)?(a):(b))

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

LL f[N][N][5],a[N];

int main()
{
	int n , x;
	cin  >> n >> x;
	for(int i=1;i<=n;++i)
		a[i] = read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i)
		f[i][i][0] = f[i][i][1] = abs(a[i]-x)*n;
	for(int len=2;len<=n;++ len)
		for(int i=1;i+len-1<= n;++ i)
		{
			int j=i+len-1;
			f[i][j][0] = f[i][j][1] = inf;
			f[i][j][0]=min(f[i][j][0],f[i+1][j][0]+(LL)(n-(j-i))*(a[i+1]-a[i]));
			f[i][j][0]=min(f[i][j][0],f[i+1][j][1]+(LL)(n-(j-i))*(a[j]-a[i]));
			f[i][j][1]=min(f[i][j][1],f[i][j-1][0]+(LL)(n-(j-i))*(a[j]-a[i]));
			f[i][j][1]=min(f[i][j][1],f[i][j-1][1]+(LL)(n-(j-i))*(a[j]-a[j-1]));
		}
	cout<<min(f[1][n][0],f[1][n][1]);
}

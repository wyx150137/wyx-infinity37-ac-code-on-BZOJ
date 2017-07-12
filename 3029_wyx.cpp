
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200+1;

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

double F[N][N][400+1],p[N];
int n,l,k,a[N];

inline void change(int i,int j,int k,double x)
{
	k = min(k,n);
	F[i][j][k+200] += x;
}

int main()
{
	n = read(), l = read(), k = read();
	for(int i=1;i<=n;++i) p[i] = 1.0*read()/100.0;
	for(int i=1;i<=n;++i) a[i] = read();
	k = min(k,n);
	F[0][0][k+200] = 1;
	for(int i=0;i<n;++i)
		for(int j=0;j<=i;++j)
			for(int k=-i;k<=n;++k)
				change(i+1,j+1,k+a[i+1],p[i+1]*F[i][j][k+200]),change(i+1,j,k,(1-p[i+1])*F[i][j][k+200]);
	double ans = 0.0;
	for(int i=0;i<=n;++i)
		for(int j=l;j<=n;++j)
			ans+=F[n][j][i+200];
	printf("%.6lf",ans);
}

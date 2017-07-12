
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 1e6+5;
using namespace std;
const LL inf = 1e18;
LL dis[N];
int F[N][2];

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int ans[N];

int main()
{
	int n = read(), k = read();LL  m = read(),i,j,o,op; 
	for(i=1;i<=n;++i) dis[i] = read();dis[n+1] = inf;
	int L = 1;
	int R = k + 1;
	F[1][0] = R;
	
	for(i=2;i<=n;++i)
	{
		while(dis[i] - dis[L] > dis[R+1] - dis[i] &&  R < n ) L ++,R++;
		F[i][0] = dis[i] - dis[L] >= dis[R] - dis[i] ? L : R;
	}
	
	for(i=1;i<=n;++i) ans[i] = i;
	
	for(j=0;m;++j)
	{
		o = j & 1;
		op = (j+1) & 1;
		if(m&1)
			for(i=1;i<=n;++i)
				ans[i] = F[ans[i]][o];
		for(i=1;i<=n;++i) 
			F[i][op] = F[F[i][o]][o];
		m >>= 1;		
	}
	
	for(i=1;i<n;++i)
		printf("%d ",ans[i]);
	cout <<ans[n] << endl;
}

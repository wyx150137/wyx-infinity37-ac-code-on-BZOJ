
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N =  20;
const int mod = 1000000001;
typedef long long LL;
const int Maxn = (1<<18)-1;
using namespace std;

bool used[Maxn];

inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int T[N][N],n;
int times[N];
int Max[N];
LL F[19][Maxn];

LL calc(int x)
{
	memset(Max,0,sizeof Max);
	memset(T,0,sizeof T);
	T[1][1] = x;
	for(int i=2;i<=18;++i) T[i][1] = T[i-1][1]*2 > n ? n+1 : T[i-1][1]*2;
	for(int i=1;i<=18;++i)
		for(int j=2;j<=11;++j)
			T[i][j] = T[i][j-1] * 3 > n ? n + 1 : T[i][j-1]*3;

	for(int i=1;i<=18;++i)
		for(int j=1;j<=11;++j)
			if(T[i][j]<=n)
				Max[i] += times[j-1],used[T[i][j]] = 1; 

	for(int i=0;i<=18;++i)
		for(int j=0;j<=Max[i];++j)
			F[i][j] = 0;

	F[0][0] = 1;

	for(int i=0;i<18;++i)
		for(int j=0;j<=Max[i];++j)
			if(F[i][j])
				for(int k=0;k<=Max[i+1];++k)
					if( ((j &k) == 0) && (( k&(k>>1)) == 0))
						(F[i+1][k] += F[i][j])%=mod;
	return F[18][0];
}

int main()
{
	n = read();
	LL ans = 1;
	times[0] = 1;
	for(int i=1;i<20;++i) times[i] = times[i-1] << 1;
	for(int i=1;i<=n;++i)
		if(!used[i])
			ans = ans * calc(i) % mod;
	cout << ans << endl;
	return 0;
}

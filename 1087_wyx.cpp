
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 600;
using namespace std;
#define lowbit(x) ((x)&(-x))
typedef long long LL;
inline int calc(int x){
	int cnt = 0;
	while(x){
		cnt ++ ;
		x -= lowbit(x);
	}
	return cnt;
}
LL F[10][82][560];
int num[N];
int main(){
	int n,K;
	cin >> n >> K;
	F[0][0][0] = 1;
	register int i,j,k;
	int t;
	for(j=0;j<(1<<n);++j) num[j] = calc(j);
	for(i=1;i<=n;++i)
		for(j=0;j<(1<<n);++j)
			for(t=0;t<=K;++t)
				if(F[i-1][t][j])
					for(k=0;k<(1<<n);++k){
						if(k&(k<<1)) continue;
						if(k&(k>>1)) continue;
						if(k&j) continue;
						if(k&(j<<1)) continue;
						if(k&(j>>1)) continue;
						F[i][t+num[k]][k] += F[i-1][t][j];
					}
	LL ans = 0;
	for(i=0;i<(1<<n);++i)
		ans += F[n][K][i];
	cout << ans << endl;
}

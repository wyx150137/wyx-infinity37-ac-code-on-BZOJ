
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int inf = 1e9;
typedef long long LL;
using namespace std;

int a[20];
LL F[65540][19];

int main(){
	int n,K;
	cin >> n >> K;
	register int i,j,k;
	for(i=0;i<n;++i) cin >> a[i];
	for(i=0;i<n;++i) F[1<<i][i] = 1;
	for(i=0;i<(1<<n);++i)
		for(j=0;j<n;++j)
			if((i&(1<<j)) && F[i][j])
				for(k=0;k<n;++k)
					if(!(i&(1<<k)) && abs(a[k]-a[j]) > K)
						F[i|(1<<k)][k] += F[i][j];
	LL ans = 0;
	for(i=0;i<n;++i) ans += F[(1<<n)-1][i];
	cout << ans << endl;
}

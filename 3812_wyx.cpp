
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 15;
const int mod = 1000000007;
using namespace std;

int out[N][1<<N],pow[N*N],bit[1<<N],tot[1<<N];
int F[1<<N],g[1<<N],h[1<<N];

inline int lowbit(int x){
	return (x & (-x));
}

int main(){
	int n,m;
	cin >> n >> m;
	register int i,j;
	for(i=0;i<n;++i) bit[1<<i] = i;
	pow[0] = 1;
	for(i=1;i<=m;++i) pow[i] = ((LL)pow[i-1] + pow[i-1]) % mod;
	
	int x,y;
	for(i=1;i<=m;++i){
		cin >> x >> y;
		-- x , -- y;
		++out[x][1<<y];
	}
	
	for(i=0;i<n;++i)
		for(j=0;j<(1<<n);++j){
			int k = lowbit(j);
			out[i][j] = out[i][j^k] + out[i][k];
		}
		
	for(i=0;i<(1<<n);++i)
		for(j=0;j<n;++j)
			if((i>>j)&1)
				tot[i] += out[j][i];
				
	int left;
	for(i=1;i<(1<<n);++i){
		if(i == lowbit(i)) {F[i] = g[i] = 1; continue;}
		else{
			h[0] = 0;
			F[i] = pow[tot[i]], g[i] = 0;
			x = bit[lowbit(i)];
			for(j=(i-1)&i;j;j=(j-1)&i){
				left = i - j;
				h[left] = h[left^lowbit(left)] + out[bit[lowbit(left)]][i];
				(F[i] += mod-(LL)pow[h[left]]*g[j]%mod) %= mod;
				if((j>>x)&1) (g[i] += mod - (LL)F[j] * g[left]%mod) %= mod;
			}
			(F[i] += mod - g[i]) %= mod;
			(g[i] += F[i]) %= mod;
		}
	}
	cout << F[(1<<n)-1];
}

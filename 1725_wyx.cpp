
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL mod = 1e9;
int F[13][4100];
int map[15];
int m,n;

bool check(int x){
	if((x & (x<<1)) || (x & (x >>1)))return false;
	return true;
}

int main(){
	cin >> n >> m;
	register int i,j,k;
	int tmp;
	for(i=1;i<=n;++i){
		for(j=0;j<m;++j){
			cin >> tmp;
			if(!tmp) map[i] |= (1<<j);
		}
	}
	F[0][0] = 1;
	for(i=0;i<n;++i)
		for(j=0;j<(1<<m);++j){
			if(!F[i][j])continue;
			for(k=0;k<(1<<m);++k){
				if(check(k) && (!(k&map[i+1])) && !(k&j))
					F[i+1][k] += F[i][j];
				if(F[i+1][k] >= mod) F[i+1][k] -= mod;
			}
		}
	LL ans = 0;
	for(i=0;i<(1<<m);++i) (ans += F[n][i]) %= mod;
	cout << ans << endl;
	return 0;
}

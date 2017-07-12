
#include <cstdio>
#include <string.h>
#include <iostream>
#include <algorithm>
#define lowbit(x) ((x)&(-x)) 
using namespace std;
const int N = 66000+5;
typedef long long LL;
LL F[N];
int a[N];

inline int calc(int x){
	int cnt = 0;
	while(x){
		cnt ++;
		x -= lowbit(x);
	}
	return cnt;
}

int main(){
	int n,d,k;
	cin >> n >> d >> k;
	register int i,j;
	LL ans = 0;
	for(i=1;i<=n;++i){
		int opt;cin >> opt;
		for(j=1;j<=opt;++j){
			int tt; cin >> tt;
			a[i] |= 1<<(tt-1);
		}
		for(j=(1<<d)-1;j;--j)
			if(calc(j|a[i]) <= k)
				ans = max((F[j|a[i]] = max(F[j|a[i]],F[j]+1)),ans);
	}
	cout << ans << endl;
}

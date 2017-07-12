
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 1e9+7;
const int N = 1e6;

LL pow(LL a,LL b){
	LL res = 1; a %= mod;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1)
			res = res * a % mod;
	return res;
}

LL F[N];

int main(){// freopen("number.in","r",stdin); freopen("number.out","w",stdout);
	LL N, K, L, R;
	int flag = 0;
	cin >> N >> K >> L >> R ;
	if(L <= K && K <= R) flag = 1; // 全是K
	L=(L-1)/K,R=R/K; 
	int mx = R - L ;
//	cout << mx << endl;
	for(int i = mx; i; i--){
		LL tmp1 = L / i, tmp2 = R / i, len = tmp2 - tmp1;
//		cout << tmp1 << " " << tmp2 << endl;
		if(tmp1<tmp2){
			F[i] = (pow(len,N)-len+mod) % mod;
			for(int j=i*2;j<=mx;j+=i) F[i] = (F[i] - F[j] + mod) % mod;
		}
//		cout << F[i] << endl;
	}
	cout << F[1] + flag << endl;
}


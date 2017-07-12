
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
const int Max = 1e6;
const int mod = 1e9+7;
typedef long long LL;
LL inv[N], F[N];
//(n+1) * a(n) = (6*n-3) * a(n-1) - (n-2) * a(n-2)
int main() {
	inv[0] = inv[1] = 1;
	for(int i=2;i<=Max+1;++i) 
		inv[i] = mod - (LL)mod/i*inv[mod%i]%mod;
	F[0] = F[1] = 1;
	for(int i=2;i<=Max;++i) 
		F[i] = ((6ll*i-3)*F[i-1]%mod+mod-(LL)(i-2)*F[i-2]%mod)*inv[i+1] % mod;
	int x; cin >> x; cout << F[x-2] << endl;
}


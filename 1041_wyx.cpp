
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const double eps = 1e-6;
const int N = 1e5+5;
LL r, ans, fac[N];
int cnt;

void get(LL x) {
	int i;
	for(i=1;(LL)i*i<x;++i) if(x%i==0) fac[++cnt] = i, fac[++cnt] = x/i;
	if((LL)i*i==x)  fac[++cnt] = i;
}

bool check(LL x) {
	double tmp = sqrt((double)x);
	if(fabs(floor(tmp+eps)-tmp)<eps) return true;
	return false;
}

int main() {
	cin >> r ;
	get(r<<1);
	for(int i=1;i<=cnt;++i) {
		LL left = (r+1)/fac[i];
		for(int j=1;(LL)j*j<left;++j){
			LL tmp1 = r*2/fac[i]-(LL)j*j;
			if(check(tmp1) && __gcd(tmp1,(LL)j*j)==1 && (LL)j*j != tmp1) ans ++;
		}
	}
	printf("%lld\n",(ans+1)*4);
}  


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod = 1e4;

inline int pow(int a,int b) {
	int res = 1;
	for(;b;b>>=1,a=a*a%mod)
		if(b&1) res = res * a % mod;
	return res;
}

int ans1,ans2,ans3,n,m,p,e;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	n = read(), m = 1;
	int tmp1,tmp2;
	for(int i=1;i<=n;++i) {
		p = read(), e = read();
		m = m * pow(p,e) % mod;
		if(p == 2) continue;
		tmp1 = (ans1 + ans2 * (p-1)) % mod;
		tmp2 = (ans2 + (ans1+1)*(p-1)) % mod;
		ans1 = tmp1, ans2 = tmp2;
	}
	ans3 = ((m-1-ans1-ans2)%mod+mod)%mod;
	printf("%d\n%d\n%d\n",ans1,ans2,ans3);
}


#include <set>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod = 1e9+61;
const int N = 1e5+5;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}


struct data {
	int val, pos;
	bool operator < (const data &z) const {
		return val ^ z.val ? val > z.val : pos < z.pos;
	}
} a[N];

set <int> s;
int Xor[N], v[N], L[N], R[N], sum[N], n,m, P[50], val[N];

LL cal(){
	int i;  
	LL re=0;
	int *s = sum;
	for(i=1;i<=n;i++) s[i]=s[i-1]+v[i];  
	for(i=1;i<=n;i++){
		LL s1 = i-L[i]+1, s2 = R[i]-i+1;
		LL t1 = s[i-1]-s[max(0,L[i]-2)],t2 = s[R[i]]-s[i-1];  
		(re += t1*(s2-t2)%mod*val[i])%=mod;
		(re += (s1-t1)*t2%mod*val[i])%=mod;  
	}
	return re;  
} 

int main() {
//	freopen("tt.in","r",stdin);
	int T = read();
	P[0] = 1;
	for(int j=1;j<31;++j) P[j] = (P[j-1]<<1) % mod;
	while(T --) {
		s.clear();
		n = read();
		s.insert(0);
		s.insert(n+1);
		for(int i=1;i<=n;++i) {
			a[i].val = read(), a[i].pos = i;
			Xor[i] = Xor[i-1] ^ a[i].val;
		}
		sort(a+1,a+n+1);
		set <int> :: iterator it; 
		LL ans = 0;
		for(int i=1;i<=n;++i) {
			it = s.upper_bound(a[i].pos);
			R[a[i].pos] = (*it) - 1;
			it --;
			L[a[i].pos] = (*it) + 1;
			val[a[i].pos] = a[i].val;
			s.insert(a[i].pos);
		}
		for(int i=0;i<31;i++){  
			for(int j=1;j<=n;j++){  
				v[j]=(Xor[j]>>i)&1;  
			}  
			(ans+=cal()*(1<<i))%=mod;
		}  
		printf("%lld\n",ans);
	}
}

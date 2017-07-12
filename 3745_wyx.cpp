
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 500000+5;
typedef long long LL;
const int mod = 1e9;
const int inf = 1e9-1;
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
int a[N], sum[7][N];

inline char getc() {
    static const int LEN = 1<<15;
    static char buf[LEN],*S=buf,*T=buf;
    if(S == T) {
        T = (S=buf)+fread(buf,1,LEN,stdin);
        if(S == T)return EOF;
    }
    return *S++;
}
 
inline int read() {
    static char ch;
    static int D;
    while(!isdigit(ch=getc()));
    for(D=ch-'0'; isdigit(ch=getc());)
        D=(D<<3)+(D<<1)+(ch-'0');
    return D;
}

inline int calc(int l,int r) {
	return (sum[0][r] - sum[0][l-1] + mod) % mod;
}

LL ans;

inline void solve(int L,int R) {
	if(L == R) {
		ans = (ans + (LL) a[L] * a[L] % mod) % mod;
		return;
	}
	int mid = (L+R) >> 1;
	int mx = -inf, mn = inf;
	register int i;
	for(i=1;i<=6;++i) sum[i][mid] = 0;
	for(i=mid+1;i<=R;++i) {
		mx = max(mx, a[i]);
		mn = min(mn, a[i]);
		sum[1][i] = (LL)mx * mn % mod;
		sum[2][i] = (LL)mx * mn % mod * i % mod;
		sum[3][i] = mn;
		sum[4][i] = (LL)mn * i % mod;
		sum[5][i] = mx;
		sum[6][i] = (LL)mx * i % mod;
		for(int j=1;j<=6;++j) (sum[j][i] += sum[j][i-1]) %= mod;
	}
	int j = mid, k = mid, s, t;
	int temp1 = a[mid], temp2 = a[mid];
	for(i = mid; i >= L; --i, temp1 = min(temp1, a[i]), temp2 = max(temp2, a[i])) {
		while(j + 1 <= R && a[j + 1] >= temp1) j ++;
		while(k + 1 <= R && a[k + 1] <= temp2) k ++;
		s = mid + 1, t = min(j, k);
		if(s <= t) 
			(ans += (LL) temp1 * temp2 % mod * calc(s - i + 1, t - i  + 1) % mod) %= mod;
		s = max(j, k) + 1, t = R;
		if(s <= t)  {
			(ans += (sum[2][t] - sum[2][s-1] + mod) % mod) %= mod;
			(ans += (LL) (1 - i) * ((sum[1][t] - sum[1][s-1] + mod) % mod) % mod) %= mod;
		}
		s = min(j, k) + 1, t = max(j, k);
		if(s <= t) {
			if(j <= k) {
				(ans += (LL) temp2 * (sum[4][t] - sum[4][s-1] + mod) % mod) %= mod;
				(ans += (LL) temp2 * (1 - i + mod) % mod * (sum[3][t] - sum[3][s-1]) % mod) %= mod;
			}
			else {
				(ans += (LL) temp1 * (sum[6][t] - sum[6][s-1] + mod) % mod) %= mod;
				(ans += (LL) temp1 * (1 - i + mod) % mod * (sum[5][t] - sum[5][s-1]) % mod) %= mod;
			}
		}
	}
	solve(L, mid);
	solve(mid+1, R);
}		

int main() {
	int n = read();
	for(int i=1;i<=n;++i) sum[0][i] = i;
	for(int i=1;i<=n;++i) (sum[0][i] += sum[0][i-1]) %= mod;
	for(int i=1;i<=n;++i) a[i] = read();
	solve(1,n);
	cout << ans << endl;
}

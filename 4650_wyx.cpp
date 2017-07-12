
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef unsigned long long LL;
int n;

char str[N];
LL has[N], pow[N];
LL temp1[N], temp2[N], ans;

inline LL get(int l,int r) {
	return has[l] - has[r] * pow[r-l];
}

inline void solve() {
	int T;
	cin >> T;
	pow[0] = 1;
	register int i;
	for(i=1;i<=30000;++i) pow[i] = pow[i-1] * 233;
	while(T--) {
		scanf("%s", str+1);
		int n = strlen(str+1);
		for(i=1;i<=n;++i) temp1[i] = temp2[i] = 0;
		has[n+1] = 0;
		for(i=n;i>=1;--i) has[i] = has[i+1] * 233 + str[i];
		for(int L=1;L+L<=n;++L) {
			for(i=L+L;i<=n;i+=L) {
				if(str[i] != str[i-L]) continue;
				int bef = i - L, st, ed;
				{
					int ans = 0;
					int l = 1, r = L;
					while(l <= r) {
						int mid = (l+r) >> 1;
						if(get(bef-mid+1,bef+1) == get(i-mid+1,i+1)) l = mid + 1, ans = mid;
						else r = mid - 1;
					}
					st = i - ans + 1;
				}
				{
					int ans = 0;
					int l = 1, r = L;
					while(l <= r) {
						int mid = (l+r) >> 1;
						if(get(bef,bef+mid) == get(i,i+mid)) l = mid + 1, ans = mid;
						else r = mid - 1;
					}
					ed = i + ans - 1;
				}
				st = max(i, st + L - 1);
				ed = min(ed, i + L - 1);
				if(st <= ed) {
					temp1[st - L * 2 + 1] ++;
					temp1[ed - L * 2 + 1 + 1] --;
					temp2[st] ++;
					temp2[ed + 1] --;
				}
			}
		}
		LL ans = 0;
		for(i=1;i<=n;++i) {
			temp1[i] += temp1[i-1];
			temp2[i] += temp2[i-1];
		}
		for(i=1;i<n;++i) ans += temp2[i] * temp1[i+1];
		cout << ans << endl;
	}
}
 
int main() {
	solve();
}


#include <bits/stdc++.h>
using namespace std;
const int N = 500+5;
char str[N];
int f[1<<21];
int nxt[N][N];
#define lowbit(x) ((x)&(-x))
int main() {
	int T; cin >> T; while(T--) {
		int n;
		scanf("%d%s",&n,str+1);
		int len = strlen(str+1);
		memset(f, 0, sizeof f);
		if(n > 21) {
			puts("NO");
			continue;
		}
		for(int j=0;j<n;++j) nxt[len][j] = nxt[len+1][j] = len + 1;
		for(int i=len;i;--i) {
			for(int j=0;j<n;++j) nxt[i-1][j] = nxt[i][j];
			nxt[i-1][str[i]-'a'] = i;
		}
		int Max = (1<<n)-1;
		for(int i=1;i<=Max;++i) {
			int temp = 0;
			for(int j = i; j; j -= lowbit(j)) {
				int k = __builtin_ctz(j);
				temp = max(temp, nxt[f[i^(1<<k)]][k]);
			}
			f[i] = temp;
		}
		puts(f[Max] > len ? "NO" : "YES");
	}
}

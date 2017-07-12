
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
const int Maxm = (1<<8)+5;
const int mod = 12345678;
const int dx[] = {-1,-1,-1,0,0,1,1,1,0};
const int dy[] = {-1,0,1,-1,1,-1,0,1,0};
typedef long long LL;
#define fir first
#define sec second
int n, m, ans;
char str[10][10];
pair <int,int> stack[10];
int top, cnt[Maxm], F[30][Maxm];

inline int calc() {
	memset(F, 0, sizeof F);
	memset(cnt, 0, sizeof cnt);
	int top = 0;
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(str[i][j] == 'X') {
				stack[++top] = make_pair(i,j);
			}
		}
	}
	int Max = (1 << top) - 1;
	bool vis[10][10] = {};
	for(int sta = 0; sta <= Max; ++ sta) {
		memset(vis, false,sizeof vis);
		for(int i=1;i<=top;++i) {
			if(((1<<(i-1))&sta) == 0) {
				vis[stack[i].fir][stack[i].sec] = 1;
			}
		}
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=m;++j) {
				bool flag = true;
				for(int k=0;k<9;++k) {
					if(vis[i+dx[k]][j+dy[k]]) {
						flag = false;
						break;
					}
				}
				if(flag) cnt[sta] ++;
			}
		}
	}
	F[0][0] = 1;
	for(int i=1;i<=n*m;++i) {
		for(int sta = 0 ; sta <= Max; ++ sta) {
			(F[i][sta] += (LL) F[i-1][sta] * max(cnt[sta]-i+1, 0) % mod) %= mod;
			for(int j=1;j<=top;++j) {
				if(sta & (1<<(j-1))) {
					(F[i][sta] += F[i-1][sta-(1<<(j-1))]) %= mod;
				}
			}
		}
	}
	return F[n*m][Max];
}

inline void DFS(int x,int y,int cnt) {
	if(y == m + 1) {
		DFS(x+1,1,cnt);
		return;
	}
	if(x == n + 1) {
		(ans += calc() * (cnt & 1 ? (-1) : 1)) %= mod;
		return;
	}
	DFS(x, y+1, cnt);
	bool flag = true;
	for(int i=0;i<9;++i) {
		if(str[x+dx[i]][y+dy[i]] == 'X') flag = false;
	}
	if(flag) {
		str[x][y] = 'X';
		DFS(x,y+1,cnt+1);
		str[x][y] = '.';
	}
}

int main() {
//	freopen("tt.in","r",stdin);
	cin >> n >> m;
	for(int i=1;i<=n;++i) scanf("%s", str[i]+1);
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			if(str[i][j] == 'X') {
				for(int k=0;k<8;++k) {
					if(str[i+dx[k]][j+dy[k]]=='X') return 0*puts("0");
				}
			}
		}
	}
	DFS(1,1,0);
	cout << (ans % mod + mod) % mod << endl;
}

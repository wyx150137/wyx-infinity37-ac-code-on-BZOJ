
#include <vector>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e5+10;
using namespace std;
vector <int> g[N];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9') {if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9') {x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int n,m,cnt;
bool vis[N];
int next[N],pre[N];
int num[N];

void erase(int x) {
	next[pre[x]] = next[x];
	pre[next[x]] = pre[x] ;
}

void solve(int x) {
	queue <int> q;
	q.push(x);
	vector <int> :: iterator it;
	while(!q.empty()) {
		int tt = q.front(); q.pop();
		for(it = g[tt].begin(); it != g[tt].end(); it ++) vis[*it] = 1;
		for(int i=next[0]; i<=n; i = next[i]) {
			if(!vis[i]) {
				erase(i);
				num[cnt] ++;
				q.push(i);
			}
 		}
 		for(it = g[tt].begin(); it != g[tt].end(); it ++) vis[*it] = 0;
	}
}

int main() {
	n = read(), m = read();
	for(int i=0;i<=n;++i) next[i] = i + 1 , pre[i+1] = i;
	for(int i=1;i<=m;++i) {
		int x = read(), y = read();
		g[x].push_back(y), g[y].push_back(x);
	}
	for(int i=next[0]; i<= n; i = next[0]) {
		erase(i);
		num[++cnt] = 1;
		solve(i);
	}
	cout << cnt << endl;
	sort(num+1,num+cnt+1);
	for(int i=1;i<=cnt;++i) printf("%d ",num[i]);
}

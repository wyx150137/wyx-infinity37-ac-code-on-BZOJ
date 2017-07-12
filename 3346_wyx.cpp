
#include <vector>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 10000+5;
const int M = 10 * N;
typedef bitset<N> Int;
Int F[N], standerd;
int n, m, tim[N], deg[N], a[M];

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data{
	int x, y, val;
	bool operator<(const data &z) const{
		if(x != z.x) return x < z.x;
		if(y != z.y) return y < z.y;
		return val < z.val;
	} 
	bool operator != (const data &z) const {
		return x != z.x || y != z.y;
	}
} edge[M];

vector <int> V[N];

inline bool check(int mid) {
	static const int base = 2050;
	if(n > base) {
		for(int i=1;i<=n;++i) {
			deg[i] = 0;
			for(int j=0;j<V[i].size();++j) {
				int temp = V[i][j];
				if(edge[temp].val <= mid) deg[i] ++;
			}
		}
		for(int i=1;i<=n;++i) tim[i] = -1;
		for(int i=1;i<=n;++i) if(deg[i]*2>=n){
			for(int j=0;j<V[i].size();++j) {
				int temp = V[i][j];
				if(edge[temp].val <= mid) tim[edge[temp].y] = i;
			}
			for(int j=1;j<=n;++j) if(deg[i] + deg[j] >= n && deg[i] >= deg[j]) {
				int temp = deg[i];
				for(int k=0;k<V[j].size();++k) {
					int temp2 = V[j][k];
					if(edge[temp2].val <= mid && tim[edge[temp2].y] < i) temp ++;
				}
				if(temp == n) return true;
			}
		}
	}
	else {
		for(int i=1;i<=n;++i) F[i] = standerd;
		for(int i=1;i<=n;++i) {
			deg[i] = 0;
			for(int j=0;j<V[i].size();++j) {
				int temp = V[i][j];
				if(edge[temp].val <= mid) {
					deg[i] ++;
					F[i].reset(edge[temp].y);
				}
			}
		//	cout << F[i] << endl;
		}
		for(int i=1;i<=n;++i) if(deg[i] * 2 >= n){
			for(int j=1;j<=n;++j) if(deg[j] + deg[i] >= n && deg[i] >= deg[j]) {
				Int temp = F[i]&F[j];
				if(!temp.any()) return true;
			}
		}
	}
	return false;
}

int main() {
//	freopen("tt.in","r",stdin);
	n = read(), m = read();
	for(int i=1;i<=n;++i) standerd.set(i);
	for(int i=1;i<=m;++i) {
		edge[i].x = read(), edge[i].y = read(), edge[i].val = read();
	}
	sort(edge+1,edge+m+1);
	int top = 1;
	for(int i=2;i<=m;++i) if(edge[i] != edge[i-1]) edge[++top] = edge[i];
	m = top;
	for(int i=1;i<=m;++i) a[i] = edge[i].val;	
	sort(a+1,a+m+1);
	for(int i=1;i<=m;++i) V[edge[i].x].push_back(i);
	int l = 1, r = m + 1;
	while(l<r) {
		int mid = (l+r) >> 1;
		if(check(a[mid])) r = mid;
		else l = mid + 1;
	}
	if(l ==  m + 1) puts("No solution");
	else cout << a[l] << endl;
}

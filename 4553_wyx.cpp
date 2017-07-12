
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int lmt = 1e5;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N], Min[N], Max[N], F[N];
int stack1[N], stack2[N], top;


bool cmp1(int x,int y) {
	return Max[x] != Max[y] ? Max[x] < Max[y] : x < y;
}

bool cmp2(int x,int y) {
	return a[x] != a[y] ? a[x] < a[y] : x < y;
}

#define lowbit(x) ((x)&(-x))

int tr[N];

inline void updata(int x,int val) {
	while(x <= lmt) {
		tr[x] = max(tr[x], val);
		x += lowbit(x);
	} 
}

inline void clear(int x) {
	while(x <= lmt) {
		tr[x] = 0;
		x += lowbit(x);
	}
}

inline int ask(int x) {
	int ans = 0;
	while(x) {
		ans = max(ans, tr[x]);
		x -= lowbit(x);
	}
	return ans;
}

inline void solve(int L, int R) {
	if(L > R) return;
	if(L == R) {
		F[L] ++;
		return;
	}
	int mid = (L+R) >> 1;
	solve(L, mid);
	int top1 = 0, top2 = 0;
	for(int i=L;i<=mid;++i) stack1[++top1] = i;
	sort(stack1+1,stack1+top1+1,cmp1); 
	for(int i=mid+1;i<=R;++i) stack2[++top2] = i;
	sort(stack2+1,stack2+top2+1,cmp2); 
	int j = 0;
	for(int i = 1; i <= top2; ++i) {
		int tt = stack2[i];
		while(Max[stack1[j+1]] <= a[tt] && j < top1) {
			updata(a[stack1[j+1]], F[stack1[j+1]]); ++ j;
		}
		F[tt] = max(F[tt], ask(Min[tt]));
	}
	for(int i=1;i<=top1;++i) clear(a[stack1[i]]);
	solve(mid+1, R);
}

int main() {
//	freopen("tt.in","r",stdin);
	int n = read(), m = read();
	for(int i=1;i<=n;++i) a[i] = Max[i] = Min[i] = read();
	for(int i=1;i<=m;++i) {
		int x = read(), y = read();
		Min[x] = min(Min[x], y);
		Max[x] = max(Max[x], y);
	}
	solve(1,n);
	int ans = 0;
	for(int i=1;i<=n;++i) ans = max(ans , F[i]);
	cout << ans << endl;
}

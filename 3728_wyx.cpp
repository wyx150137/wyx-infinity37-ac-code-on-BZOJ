
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 5e5+5;
typedef long long LL;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int a[N],b[N];
LL ans;

struct Data {
	int x;
	bool operator < (const Data &z)const {
		return x > z.x;
	}
};

struct data {
	int x;
	bool operator < (const data &z)const {
		return x < z.x;
	}
};

priority_queue<Data>h1;
priority_queue<data>h2;

int main() {
	int n = read(), k = read();
	for(int i=1;i<=n;++i) a[i] = read();
	for(int i=1;i<=n;++i) b[i] = read();
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);
	for(int j=n,i=n;i;--i) {
		for(;a[j]>=b[i];--j) h1.push((Data){a[j]});
		if(!h1.empty()) {
			int tt = h1.top().x;h1.pop();
			ans += tt; h2.push((data){tt-b[i]});
			continue;
		}
		k --; ans += b[i];
		if(k < 0) {
			puts("NIE");
			return 0;
		}
	}
	while(k-- && !h2.empty()) {
		ans -= h2.top().x;
		h2.pop();
	}
	cout << ans << endl;
}

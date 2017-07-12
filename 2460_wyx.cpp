
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000+5;
typedef long long LL;

inline LL read() {
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct data {
	LL x; LL val;
	bool operator < (const data &z) const {
		return val > z.val;
	}
} a[N];

struct Data {
	LL val[65];

	void operator += (LL &z) {
		for(int j=63;~j;--j) {
			if((1ll<<j)&z) {
				if(val[j]) z ^= val[j];
				else {
					val[j] = z;
					break;
				}
			}
		}
	}
} Ans;

int main() {
//	freopen("tt.in", "r", stdin);
	int n = read();
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].val = read();
	sort(a+1,a+n+1);
	LL tmp = 0;
	for(int i=1;i<=n;++i) {
		Ans += a[i].x;
		if(a[i].x) tmp += a[i].val;
	}
	cout << tmp << endl;
}

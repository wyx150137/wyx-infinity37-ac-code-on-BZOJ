
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main() {
	int Q = read(), a, b, c, d, ans = 1;
	for(int i=1;i<=Q;++i,ans = 0) {
		a = read(), b = read(), c = read(), d = read();
		for(int i=1,last;i <= b && i <= d;i=last+1) {
			last = min(b/(b/i),d/(d/i));
			if(b/last>(a-1)/last&&d/last>(c-1)/last) ans=max(ans,last); 
		}
		printf("%d\n",ans);
	}
}


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
LL k,a,b;

inline int calc(LL x){
	int ans = 0;
	while(x) ans += (x%10)*(x%10), x /= 10;
	return ans;
}

int main() {
	register int i, ans = 0;
	cin >> k >> a >> b;
	for(i = min(b/k,1458ll);i;--i) {
		LL n = i*k;
		if(n >= a && i == calc(n)) ++ans;
	}
	cout << ans << endl;
}

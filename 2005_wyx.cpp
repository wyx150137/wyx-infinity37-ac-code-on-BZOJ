
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;  
typedef long long LL;
const int N = 1e5+5;
LL ans,F[N];
int main(){ int n,m;
	cin >> n >> m;
	int tmp = min(m,n);
	for(int i=tmp;i;--i) {
		F[i] = (LL)(n/i)*(m/i);
		for(int j=i*2;j<=tmp;j+=i) F[i] -= F[j];
		ans += 2ll*i*F[i];
	}
	ans -= 1ll*m*n;
	cout << ans << endl;
}

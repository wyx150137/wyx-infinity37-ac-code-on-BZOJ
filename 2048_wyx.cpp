
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
const double eps = 1e-10, r = 0.5772156649;
using namespace std;
long long n,m; double ans;

int main() {
	cin >> n >> m;
	if(n <= 10000) for(int i=1;i<=n;++i) ans += 0.5/i;
	else ans = (log(n+1.0)+r)/2.0;
	printf("%d\n",(int)(ans*m-eps));
}

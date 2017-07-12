
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double f2;
typedef long long LL;
const int N = 1e5+5;
const f2 eps = 1e-7;

int n;

struct poi {
    LL x,y;
} a[N];

inline LL read() {
    LL x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

LL X[N] , Y[N], ans = (1ll<<62);
LL sum_X[N], sum_Y[N];

int main() {
    int pos;
    cin >> n;
    LL tmp1,tmp2;
    for(int i=1;i<=n;++i) {
        tmp1 = read(), tmp2 = read();
        X[i] = a[i].x = tmp1 + tmp2;
        Y[i] = a[i].y = tmp1 - tmp2;
    }
    sort(X+1,X+n+1);
    sort(Y+1,Y+n+1);
    for(int i=1;i<=n;++i) {
        sum_X[i] = sum_X[i-1] + X[i];
        sum_Y[i] = sum_Y[i-1] + Y[i];
    }
    for(int i=1;i<=n;++i) {
        LL tmp = 0;
        pos = lower_bound(X+1,X+n+1,a[i].x) - X;
        tmp += (a[i].x*pos-sum_X[pos]) + (sum_X[n]-sum_X[pos]) - a[i].x * (n-pos);
        pos = lower_bound(Y+1,Y+n+1,a[i].y) - Y;
        tmp += (a[i].y*pos-sum_Y[pos]) + (sum_Y[n]-sum_Y[pos]) - a[i].y * (n-pos);
        ans = min(ans,tmp);
    }
    cout << ans /2 << endl;
}


#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double f2;
const f2 PI = acos(-1);
const int N = 2000000+5;
typedef long long LL;
inline int read() {
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

int rev[N], dig[32], n, l;

struct cp {
    f2 a, b;
    cp (f2 _a=0, f2 _b=0):a(_a),b(_b){}
    cp operator + (const cp &z) const {return cp(a+z.a,b+z.b);}
    cp operator - (const cp &z) const {return cp(a-z.a,b-z.b);}
    cp operator * (const cp &z) const {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
} a[N], b[N], A[N], c[N], x, y;

int tmp1[N], tmp2[N];

inline void init(int x) {
    for(n=1,l=0;n<=x;n<<=1,l++);
    for(int i=0;i<n;++i) {
        int len = 0;
        for(int t=i;t;t>>=1) dig[len++] = t & 1;
        for(int j=0;j<l;j++) rev[i] = (rev[i]<<1)|dig[j];
    }
}

inline void FFT(cp *a,int type) {
    for(int i=0;i<n;++i) A[i] = a[rev[i]];
    for(int i=0;i<n;++i) a[i] = A[i];
    for(int i=2;i<=n;i<<=1) {
        cp wn(cos(2*PI/i),type*sin(2*PI/i));
        for(int k=0;k<=n;k+=i) {
            cp w(1,0);
            for(int j=k;j<k+i/2;++j,w=w*wn) {
                x = a[j], y = a[j+i/2] * w;
                a[j] = x + y, a[j+i/2] = x - y;
            }
        }
    }
    if(type == -1) for(int i=0;i<n;++i) a[i].a /= n;
}

int main() {
 //   freopen("tt.in","r",stdin);
    int all = read(), m = read();
    for(int i=0;i<all;++i) tmp1[i] = tmp1[i+all] = read();
    for(int i=0;i<all;++i) tmp2[all-i-1] = read();
    init(all<<1);
    for(int i=0;i<n;++i) a[i] = cp(tmp1[i]);
    for(int i=0;i<n;++i) b[i] = cp(tmp2[i]);
    FFT(a,1); FFT(b,1); for(int i=0;i<n;++i) c[i] = a[i] * b[i]; FFT(c,-1);
    LL tmp = 0;
    for(int i=0;i<all;++i) tmp += tmp1[i]*tmp1[i] + tmp2[i]*tmp2[i];
    LL tmp3 = 0;
    for(int i=0;i<all;++i) tmp3 += tmp1[i] - tmp2[i];
    LL mx = 0;
    for(int i=all-1;i<(all<<1);++i) mx = max(mx, (long long)(c[i].a+0.5));
    tmp -= 2*mx;
    LL ans = 0x3f3f3f3f;
    for(int i=-m;i<=m;++i)  ans = min(ans,all*i*i+i*tmp3*2+tmp);
    cout << ans << endl;
}

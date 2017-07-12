
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double f2;
typedef long long LL;
const f2 PI = acos(-1);
const int N = 50000*20+5;
inline int read() {
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

struct cp{
	f2 a,b;
	cp (f2 _a=0,f2 _b=0):a(_a),b(_b){}
	cp operator + (const cp &z) {return cp(a+z.a,b+z.b);} 
	cp operator - (const cp &z) {return cp(a-z.a,b-z.b);}
	cp operator * (const cp &z) {return cp(a*z.a-b*z.b,a*z.b+b*z.a);}
} a[N], b[N], c[N], A[N], x, y;
 
LL ans[N];
int dig[40];
int rev[N],n,l;

inline void FFT(cp *a,int type) { 
	register int i,j,k;
	for(i=0;i<n;++i) A[i] = a[rev[i]];
	for(i=0;i<n;++i) a[i] = A[i];
	for(i=2;i<=n;i<<=1) {
		cp wn(cos(2*PI/i),type*sin(2*PI/i));
		for(j=0;j<n;j+=i) {
			cp w(1,0);
			for(k=j;k<j+(i>>1);k++, w = w * wn) {
				x = a[k], y = a[k+(i>>1)]*w;
				a[k] = x + y, a[k+(i>>1)] = x - y;
			}
		}
	} 
	if(type == -1) for(i=0;i<n;++i) a[i].a /= n;
} 

LL temp1[N],temp2[N];

inline void solve(int L,int R) {
	if(L==R) {
		ans[0] += temp1[L] * temp2[R];
		return;
	}
	int mid = (L+R) >> 1;
	solve(L,mid);
	solve(mid+1,R);
	int temp, len = max(mid-L+1,R-mid);
	register int i, j;
	for(n=1,l=0;n<=len<<1;n<<=1,l++);
	for(i=0;i<n;++i) rev[i] = 0;
	for(i=0;i<n;++i) a[i] = b[i] = c[i] = cp(0,0);
	memset(dig,0,sizeof dig);
	for(i=0,temp=0;i<n;++i,temp=0) {
		for(j=i;j;j>>=1) dig[temp++] = j&1;
		for(j=0;j<l;++j) rev[i] = (rev[i]<<1)|dig[j];
	}
	for(i=L;i<=mid;++i) a[i-L] = cp(temp1[i],0);
	for(i=mid+1;i<=R;++i)b[i-mid-1] = cp(temp2[i],0);
	FFT(a,1);FFT(b,1);
	for(i=0;i<n;++i) c[i] = a[i] * b[i];
	FFT(c,-1);
	for(i=0;i<n;++i) ans[i+L+mid+1] += (LL)(c[i].a+0.1);
	for(i=0;i<n;++i) a[i] = b[i] = c[i] = cp(0,0);
	for(i=mid+1;i<=R;++i) a[i-mid-1] = cp(temp1[i],0);
	for(i=L;i<=mid;++i) b[mid-i] = cp(temp2[i],0);
	FFT(a,1);
	FFT(b,1);
	for(i=0;i<n;++i) c[i] = a[i] * b[i];
	FFT(c,-1);
	for(i=0;i<n;++i) ans[i+1] += (LL)(c[i].a + 0.1);
}

int main() {
//*	freopen("tt.in","r",stdin);
	int testcases;
	for(cin >> testcases; testcases; testcases --) {
		int n = read(), m = read(), q = read();
		memset(temp1, 0, sizeof temp1);
		memset(temp2, 0, sizeof temp2);
		int Max = 0;
		for(int i=1;i<=n;++i) {
			int temp = read();
			Max = max(Max, temp);
			temp1[temp] ++;
		}
		for(int i=1;i<=m;++i) {
			int temp = read();
			Max = max(Max, temp);
			temp2[temp] ++;
		}
		solve(0,Max);
		for(int i=1;i<=q;++i) {
			int temp = read();
			printf("%lld\n", ans[temp]);
		}
		memset(ans, 0, sizeof ans);
	}
}

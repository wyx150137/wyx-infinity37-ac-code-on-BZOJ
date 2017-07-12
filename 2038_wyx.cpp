
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 5e4+5;
LL sum[N], ans, l, r; int col[N], n, m, sz, i;
struct data { int id,blo, l, r;LL a, b; } a[N];
inline bool cmp2(const data &a,const data &b) { return a.id < b.id; }
inline bool cmp1(const data &a,const data &b) { return a.blo != b.blo ? a.blo < b.blo : a.r < b.r; }
inline void updata(int x,int val) { ans -= sum[col[x]] * sum[col[x]]; sum[col[x]] += val; ans += sum[col[x]] * sum[col[x]]; }
inline int read() {int x=0,f=1;char ch = getchar();while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}return x*f;}
int main() {
	n = read(), m = read(), sz = (int)sqrt(n);
 	for(i=1;i<=n;++i) col[i] = read();
	for(i=1;i<=m;++i) a[i].l = read(), a[i].r = read(), a[i].blo = a[i].l / sz, a[i].id = i;
	sort(a+1,a+m+1,cmp1);
	for(l=1,r=0,i=1;i<=m;++i) {
		while(a[i].r < r) updata(r--,-1);	while(a[i].r > r) updata(++r,+1); 
		while(a[i].l < l) updata(--l,+1);	while(a[i].l > l) updata(l++,-1);
		a[i].a = ans-(r-l+1), a[i].b = (r-l+1)*(r-l);
	} sort(a+1,a+m+1,cmp2);
	for(i=1;i<=m;++i) printf("%lld/%lld\n",a[i].a/__gcd(a[i].a,a[i].b),a[i].b/__gcd(a[i].a,a[i].b));
}

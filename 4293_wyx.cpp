
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 500000+5;
const int M = N << 2;

LL a[N],sum[N];

struct seg{
	LL tmp1,tmp2;
	LL Min,Max;
	LL sum;
}tr[M];

void down(int k,int L,int R) {
	if(L == R) return ;
	int mid = (L+R) >> 1;
	if(tr[k].tmp1 != -1) {
		tr[k<<1].Min = tr[k<<1].Max = tr[k<<1|1].Min = tr[k<<1|1].Max = tr[k].tmp1;
		tr[k<<1].sum = (mid-L+1) * tr[k].tmp1;
		tr[k<<1|1].sum = (R-mid) * tr[k].tmp1;
		tr[k<<1].tmp1 = tr[k<<1|1].tmp1 = tr[k].tmp1;
		tr[k<<1].tmp2 = tr[k<<1|1].tmp2 = 0;
		tr[k].tmp1 = -1;
	}
	if(tr[k].tmp2) {
		tr[k<<1].Min += a[L]*tr[k].tmp2;
		tr[k<<1].Max += a[mid]*tr[k].tmp2;
		tr[k<<1|1].Min += a[mid+1]*tr[k].tmp2;
		tr[k<<1|1].Max += a[R]*tr[k].tmp2;
		tr[k<<1].sum += (sum[mid]-sum[L-1])*tr[k].tmp2;
		tr[k<<1|1].sum += (sum[R]-sum[mid])*tr[k].tmp2;
		tr[k<<1].tmp2 += tr[k].tmp2;
		tr[k<<1|1].tmp2 += tr[k].tmp2;
		tr[k].tmp2 = 0;
	}
}

inline void updata(int k){
	tr[k].sum = tr[k<<1].sum + tr[k<<1|1].sum;
	tr[k].Min = min(tr[k<<1].Min,tr[k<<1|1].Min);
	tr[k].Max = max(tr[k<<1].Max,tr[k<<1|1].Max);
}

inline LL change(int k,int L,int R,LL val){
	if(tr[k].Min >= val) {
		tr[k].Min = tr[k].Max = val;
		tr[k].tmp1 = val;
		tr[k].tmp2 = 0;
		LL tmp = tr[k].sum - (R-L+1)*val;
		tr[k].sum = (R-L+1)*val;
		return tmp;
	}
	else if(tr[k].Max < val) return 0;
	down(k,L,R);
	int mid = (L+R) >> 1;
	LL G = change(k<<1,L,mid,val) + change(k<<1|1,mid+1,R,val);
	updata(k);return G;
}

inline LL read(){
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main(){
	int n = read(), m = read();
	for(int i=1;i<=n;++i) a[i] = read();
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i) sum[i] = sum[i-1] + a[i];
	LL last = 0;
	LL day,lmt;
	for(int i=1;i<=m;++i) {
		day = read(), lmt = read();
		tr[1].tmp2 += day - last;
		tr[1].Min += (day-last)*a[1];
		tr[1].Max += (day-last)*a[n];
		tr[1].sum += (day-last)*sum[n];
		last = day;
		printf("%lld\n",change(1,1,n,lmt));
	}
}

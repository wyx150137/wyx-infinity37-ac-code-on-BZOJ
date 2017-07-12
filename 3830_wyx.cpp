
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
#define lowbit(x) ((x)&(-x))
using namespace std;
const int N = 1e6+5;
const int inf  = 0x7fffffff;

int n;
LL T[N],f[N],a[N],s;

inline void Min(LL &a,LL b)
{
	if(a > b) a = b;
}

inline void updata(int pos,LL x)
{
	while(pos <= n) Min(T[pos],x), pos += lowbit(pos); 
}

inline LL ask(int pos)
{
	LL ans = inf;
	while(pos) Min(ans,T[pos]), pos -= lowbit(pos);
	return ans;
}

inline LL read()
{
	LL x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main(){
	n = read(), s = read();
	a[1] = read();
	for(int i=2;i<=n;++i) a[i] = max(a[i-1]+1,read());
	memset(T,0x3f,sizeof T);
	LL L,R,tt;
	for(int i=1;i<=n;++i){
		L = 1,R = i,tt = a[i]-i;
		while(L < R)
		{
			LL mid = (L+R) >> 1;
			if(f[mid]-mid-1 <=tt) L = mid + 1;
			else R = mid;
		}
		f[i] =  a[i]- (L-1) + 2*s - 1 + i;
		if(L ^ i)  Min(f[i],ask(n+1-L)+2*s+2*i);
//		cout << f[i] << endl;
		updata(n+1-i,f[i]-2*i-2);
	}
	cout << f[n] << endl;
}

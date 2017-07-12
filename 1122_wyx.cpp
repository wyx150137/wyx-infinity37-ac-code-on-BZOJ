
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
typedef long long LL;
const int N = 2000005<<1;
const LL inf = 0x7f7f7f7f7f7f7f7fll;
using namespace std;

char str[N];
LL sum[N];
LL que[N],MIN[N];
LL cal[N];

int main()
{
	LL n,p,q,x,y; cin >> n >> p >> q >> x >> y;
	scanf("%s",str+1);
	for(int i=2*n;i>n;--i) sum[i] = sum[i+1] + ((str[i-n]=='+')?1:-1);
	for(int i=n;i;--i) sum[i] = sum[i+1] + ((str[i]=='+')?1:-1);
	int l = 1,r = 0;
	for(int i=2*n;i;--i)
	{
		while(l<=r && sum[i] > sum[que[r]]) r--;
		que[++r] = i;
		while(l<=r && que[l]-i >= n) l++;
		MIN[i] = sum[i] - sum[que[l]];
	}
//	for(int i=1;i<=2*n;++i)
//		cout << MIN[i] << " ";	
	LL ans = inf,tmp = q-p-sum[n+1];
	tmp >>= 1;cal[1] = 1;
	for(int i=2;i<=n;++i) cal[i] = n-i+2;
	for(int i=0;i<n;++i)
	{
		LL now = (LL)i*y+abs(tmp)*x;
		MIN[cal[i+1]] += p + max(tmp,0ll)*2ll;
		if(MIN[cal[i+1]] < 0)
			now += 2ll*x*((1-MIN[cal[i+1]])/2ll);
		ans = min(ans,now);
	}
	cout << ans << endl;
}



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6+5;
const LL INF = 1e18;
LL c[N];
LL f[N],a[N];
int n;
LL s;
void update(int x,LL t)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i] = min(c[i],t);
}
LL getans(int x)
{
	LL ans = INF;
	for(int i = x;i>0;i-=i&(-i))
		ans = min(ans,c[i]);
	return ans;
}
int main()
{
	memset(c,0x3f,sizeof(c));
	scanf("%d%lld",&n,&s);
	for(int i = 1;i<= n;i++)
		scanf("%lld",&a[i]);
	for(int i = 2;i<= n;i++)
		a[i] = max(a[i],a[i-1]+1);
	int L,R,mid;
	for(int i = 1;i<= n;i++)
	{
		L = 1,R = i;
		while(L<R)
		{
			mid = (L+R)>>1;
			if(f[mid]-mid-1<=a[i]-i)
				L = mid+1;
			else R = mid;
		}
		f[i] = a[i]-L+i+s*2;
		if(L!=i)f[i] = min(f[i],getans(n-L+1)+s*2+i*2);
		update(n-i+1,f[i]-2*i-2);
	}
	printf("%lld\n",f[n]);
	return 0;
}

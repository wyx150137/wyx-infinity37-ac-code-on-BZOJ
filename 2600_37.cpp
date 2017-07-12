
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1000005;
int n,x;
LL p;
LL pos[N];
bool check(int len)
{
	int i,l,r,mid;
	LL now=0;
	l=1,r=len,mid=(l+r)>>1;
	for(i=l;i<mid;i++)now+=(pos[mid]-pos[i]);
	for(i=mid+1;i<=r;i++)now+=(pos[i]-pos[mid]);
	if(now<=p)return true;
	for(;r<n;)
	{
		now-=(pos[mid]-pos[l++]);
		now+=(pos[++r]-pos[mid]);
		mid=(l+r)>>1;
		now+=(pos[mid]-pos[mid-1])*(mid-l);
		now-=(pos[mid]-pos[mid-1])*(r-mid+1);
		if(now<=p)return true;
	}
	return false;
}
int main()
{
	scanf("%d%d%lld",&n,&x,&p);
	for(int i = 1;i<= n;i++)
		scanf("%lld",&pos[i]);
	int L = 0,R = n+1;
	while(L<R)
	{
		int mid = (L+R)>>1;
		if(check(mid))L = mid+1;
		else R = mid;
	}
	L--;
	printf("%d\n",L);
	return 0;
}

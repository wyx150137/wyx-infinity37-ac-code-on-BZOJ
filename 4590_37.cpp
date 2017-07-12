
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 100005;
int opt[N],n;
int check(LL l)
{
	LL now = 0;int cnt = 0;
	for(int i = 1;i<= n;i++)
	{
		now+=opt[i];
		if(now<0)now = 0;
		if(now>=l){cnt++;now = 0;}
	}
	return cnt;
}
int main()
{
	int k;
	scanf("%d%d",&n,&k);
	for(int i = 1;i<= n;i++)
		scanf("%d",&opt[i]);
	LL l = 1,r = 1e15,lans = 0,rans = 0;
	while(l<r)
	{
		LL mid = (l+r)>>1;
		if(check(mid)>k)l = mid+1;
		else r = mid;
	}
	lans = l;
	l = 1;r = 1e15;
	while(l<r)
	{
		LL mid = (l+r)>>1;
		if(check(mid)>=k)l = mid+1;
		else r = mid;
	}
	rans = l-1;
	if(check(lans)!=k||check(rans)!=k||lans<=0||rans<=0)printf("-1\n");
	else printf("%lld %lld\n",lans,rans);
	return 0;
}

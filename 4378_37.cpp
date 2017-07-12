
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1e6+5;
int a[N],num[N],cnt;
LL cn[N],cs[N];
struct opt
{int kind;LL x,y;}Opt[N];
int Find(int x)
{
	int l = 1,r = cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(num[mid]<x)l = mid+1;
		else r = mid;
	}
	return l;
}
void update(int pos,int xn,int xs)
{
	for(int i = pos;i<N;i+=i&(-i))
		cn[i]+=xn,cs[i]+=xs;
	return ;
}
LL getn(int pos)
{
	LL ans = 0;
	for(int i = pos;i>0;i-=i&(-i))
		ans+=cn[i];
	return ans;
}
LL gets(int pos)
{
	LL ans = 0;
	for(int i = pos;i>0;i-=i&(-i))
		ans+=cs[i];
	return ans;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	char o[3];
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",o);
		if(o[0]=='U')
			Opt[i].kind = 1;
		else
			Opt[i].kind = 2;
		scanf("%lld%lld",&Opt[i].x,&Opt[i].y);
		num[++cnt] = Opt[i].y;
	}
	memset(a,-1,sizeof(a));
	sort(num+1,num+cnt+1);
	for(int i = 1;i<= m;i++)
	{
		if(Opt[i].kind==1)
		{
			int tmp = a[Opt[i].x];
			if(tmp!=-1)update(Find(tmp),-1,-tmp);
			update(Find(Opt[i].y),1,Opt[i].y);
			a[Opt[i].x] = Opt[i].y;
		}else
		{
			LL tmp = getn(cnt)-getn(Find(Opt[i].y)-1);
			if(tmp>=Opt[i].x)printf("TAK\n");
			else if(gets(Find(Opt[i].y)-1)>=(Opt[i].x-tmp)*Opt[i].y)printf("TAK\n");
			else printf("NIE\n");
		}
	}
	return 0;
}

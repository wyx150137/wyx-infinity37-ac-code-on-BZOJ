
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
const int INF = 0x3f3f3f3f;
int er[N],la[N],beg[N],lef[N],now[N];
int who[N],when[N],how[N],n,m;
bool check(int e)
{
	memset(er,0x3f,sizeof(er));
	memset(la,0,sizeof(la));
	memset(beg,0,sizeof(beg));
	memset(lef,0,sizeof(lef));
	memset(now,0,sizeof(now));
	int maxn = 0;
	for(int i=1;i<= e;i++)
	{
		er[who[i]] = min(er[who[i]],when[i]);
		la[who[i]] = max(la[who[i]],when[i]);
		maxn = max(maxn,when[i]);
		if(!now[when[i]]||now[when[i]]==how[i]+1)now[when[i]] = how[i]+1;
		else return false;
	}
	for(int i = 1;i<= n;i++)
		if(er[i]!=INF)
			beg[er[i]]++,lef[la[i]]++;
	int tot=0,peop = 0,ended = 0,notbegin = 0;
	for(int i=1;i<=maxn;i++)
	if(now[i])
	{
		peop+=beg[i];
		if(peop>now[i])return false;
		if(beg[i]<=notbegin)notbegin-=beg[i];
		else tot+=beg[i]-notbegin,notbegin = 0;
		if(peop+notbegin+ended<now[i])tot += now[i]-peop-notbegin-ended,notbegin = now[i]-peop-ended;
		else
		{
			if(peop+notbegin>now[i])notbegin=now[i]-peop,ended=0;
			else ended=now[i]-peop-notbegin;
		}
		peop-=lef[i];ended+=lef[i];
	}
	if(tot>n)return false;
	return true;
}
void work()
{
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
		scanf("%d%d%d",&when[i],&who[i],&how[i]);
	int l = 1,r = m+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(check(mid))l = mid+1;
		else r = mid;
	}
	printf("%d\n",l-1);
}	
int main()
{
	int c;
	scanf("%d",&c);
	while(c--)
		work();
	return 0;
}

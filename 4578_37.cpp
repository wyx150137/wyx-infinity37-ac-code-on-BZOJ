
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 5e4+5;
const int INF = 0x3f3f3f3f;
int pmx[N],hmx[N],pmn[N],hmn[N],n;
struct Pos
{int x,y;}pos[N];
bool cmp1(Pos a,Pos b){return a.x<b.x;}
bool cmp2(Pos a,Pos b){return a.y<b.y;}
void init1()
{
	pmn[0] = INF,hmn[n+1] = INF;
	for(int i = 1;i<= n;i++)
	{
		pmx[i] = max(pmx[i-1],pos[i].x);
		pmn[i] = min(pmn[i-1],pos[i].x);
	}for(int i = n;i>= 1;i--)
	{
		hmx[i] = max(hmx[i+1],pos[i].x);
		hmn[i] = min(hmn[i+1],pos[i].x);
	}
}
void init2()
{
	pmn[0] = INF,hmn[n+1] = INF;
	for(int i = 1;i<= n;i++)
	{
		pmx[i] = max(pmx[i-1],pos[i].y);
		pmn[i] = min(pmn[i-1],pos[i].y);
	}for(int i = n;i>= 1;i--)
	{
		hmx[i] = max(hmx[i+1],pos[i].y);
		hmn[i] = min(hmn[i+1],pos[i].y);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&pos[i].x,&pos[i].y);
	sort(pos+1,pos+n+1,cmp1);
	init2();
	LL ans = 1e18+5;
	for(int i = 1;i< n;i++)
	{
		LL tmp = (LL)(pos[i].x-pos[1].x)*(pmx[i]-pmn[i]);
		tmp+=(LL)(pos[n].x-pos[i+1].x)*(hmx[i+1]-hmn[i+1]);
		ans = min(ans,tmp);
	}
	sort(pos+1,pos+n+1,cmp2);
	init1();
	for(int i = 1;i< n;i++)
	{
		LL tmp = (LL)(pos[i].y-pos[1].y)*(pmx[i]-pmn[i]);
		tmp+=(LL)(pos[n].y-pos[i+1].y)*(hmx[i+1]-hmn[i+1]);
		ans = min(ans,tmp);
	}
	printf("%lld\n",(LL)(pos[n].y-pos[1].y)*(hmx[1]-hmn[1])-ans);
	return 0;
}

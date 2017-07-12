
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 200005;
const int M = 500005;
struct P
{int x,y,num,opt,no;}p[N<<2],np[N<<2];
int ans[N];
bool cmp(const P &a,const P &b)
{
	if(a.x==b.x)
	{
		if(a.y==b.y)return a.no<b.no;
		return a.y<b.y;
	}
	return a.x<b.x;
}
int c[M];
void update(int x,int y)
{
	for(int i = x;i<M;i+=i&(-i))
		c[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
void clear(int x)
{
	for(int i = x;i<M;i+=i&(-i))
		c[i] = 0;
}
void CDQ(int l,int r)
{
	int mid = (l+r)>>1;
	if(l==r)return ;
	for(int i = l;i<= r;i++)
	{
		if(p[i].no<=mid&&p[i].opt==0)
			update(p[i].y,p[i].num);
		else if(p[i].no>mid&&p[i].opt!=0)
		{
			ans[p[i].num]+=p[i].opt*getans(p[i].y);
		}
	}
	for(int i = l;i<=r;i++)
		if(p[i].no<=mid&&p[i].opt==0)
			update(p[i].y,-p[i].num);
	int t1 = l,t2 = mid+1;
	for(int i = l;i<= r;i++)
		if(p[i].no<=mid)np[t1++] = p[i];
		else np[t2++] = p[i];
	for(int i = l;i<= r;i++)
		p[i]=np[i];
	CDQ(l,mid);CDQ(mid+1,r);
}
int main()
{
	int n,opt,x,y,a,b,cnt = 0,ask = 0;
	scanf("%d",&n);
	while(scanf("%d",&opt))
	{
		if(opt==3)break;
		else if(opt==1)
		{
			scanf("%d%d%d",&x,&y,&a);
			++cnt;p[cnt] = (P){x,y,a,0,cnt};
		}else
		{
			ask++;
			scanf("%d%d%d%d",&x,&y,&a,&b);
			++cnt;p[cnt] = (P){a,b,ask,1,cnt};
			if(y!=1){++cnt;p[cnt] = (P){a,y-1,ask,-1,cnt};}
			if(x!=1){++cnt;p[cnt] = (P){x-1,b,ask,-1,cnt};}
			if(x!=1&&y!=1){++cnt;p[cnt] = (P){x-1,y-1,ask,1,cnt};}
		}
	}
	sort(p+1,p+cnt+1,cmp);
	CDQ(1,cnt);
	for(int i=1;i<= ask;i++)
		printf("%d\n",ans[i]);
	return 0;
}

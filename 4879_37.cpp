
#include <stdio.h>
#include <set>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
set<int>sx[N],sy[N];
set<int>::iterator it;
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int n,m,K,opt[N],d[N];
ll L,R;
char s[N];
char ask(int x,int y,int flag)
{
	if(flag)swap(x,y);
	return s[x*m+y];
}
void solve(set<int> &s,int st,int end,ll tl,int wh,bool flag)
{
	int l = st,r = end;
	if(l>r)swap(l,r);
	for(it = s.lower_bound(l);it!=s.end()&&*it<=r;)
	{
		if(flag) sx[*it].erase(sx[*it].find(wh));
        else sy[*it].erase(sy[*it].find(wh));
        if(ask(wh,*it,flag)=='#') L=max(L,tl-abs(*it-st));
        else R=min(R,tl-abs(*it-st)-1);
        s.erase(it++);
	}
}
void debug()
{
	for(int i = 0;i<n&&L<=R;i++)
	{
		for(it=sx[i].begin();it!=sx[i].end();it++)
			printf("%d ",*it);
		puts("");
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i = 0;i<n;i++)
		scanf("%s",s+i*m);
	char op[10];
	for(int i = 1;i<= K;i++)
	{
		scanf("%s",op);
		if(op[0]=='l')opt[i] = 3;
		else if(op[0]=='r')opt[i] = 1;
		else if(op[0]=='u')opt[i] = 2;
		else opt[i] =0;
		scanf("%d",&d[i]);
	}
	for(int i = 0;i<n;i++)for(int j = 0;j<m;j++)sx[i].insert(j);
	for(int i = 0;i<n;i++)for(int j = 0;j<m;j++)sy[j].insert(i);
	int curx = n-1,cury = 0;ll t = 1;
	for(int i = 1;i<= K;i++)
	{
		t+=d[i];
		curx+=d[i]*dx[opt[i]],cury+=d[i]*dy[opt[i]];
	}
	R = t;
	for(int i = K;i;i--)
	{
		int tp = (opt[i]+2)%4;
		int nx = curx+d[i]*dx[tp],ny = cury+d[i]*dy[tp];
		if(tp%2)solve(sx[curx],cury,ny,t,curx,false);
		else solve(sy[cury],curx,nx,t,cury,true);
		t-=d[i],curx=nx,cury=ny;
	}
	for(int i = 0;i<n&&L<=R;i++)
		for(it=sx[i].begin();it!=sx[i].end();it++)
		{
			if(ask(i,*it,false)=='#')
			{
				L = R+1;break;
			}
		}
	if(L>R)L = R = -1;
	printf("%lld %lld\n",L,R);
	return 0;
}

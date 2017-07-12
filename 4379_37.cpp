
#include<iostream>
#include<cstdio>
#include<cstring>
#include <cctype>
#define N 1000010
using namespace std;
int to[N],nxt[N],pre[N],cnt;
char getc()
{
	static const int LEN = 4096;
	static char buf[LEN],*S=buf,*T=buf;
	if(S == T)
	{
		T = (S=buf)+fread(buf,1,LEN,stdin);
		if(S == T)return EOF;
	}
	return *S++;
}
int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc()));
	for(D=ch-'0'; isdigit(ch=getc());)
		D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
void ae(int ff,int tt)
{
	cnt++;
	to[cnt]=tt;
	nxt[cnt]=pre[ff];
	pre[ff]=cnt;
}
int fa[N],d1[N],fir[N],sec[N],thr[N];
int fd[N],sd[N];
void dfs(int x)
{
	int i,j;
	for(i=pre[x];i;i=nxt[i])
	{
		j=to[i];
		if(j==fa[x]) continue;
		fa[j]=x;
		dfs(j);
		thr[x]=max(fir[j]+1,thr[x]);
		if(thr[x]>sec[x]) swap(thr[x],sec[x]);
		if(sec[x]>fir[x]) swap(sec[x],fir[x]);
		d1[x]=max(d1[x],d1[j]);
		sd[x]=max(d1[j],sd[x]);
		if(sd[x]>fd[x]) swap(sd[x],fd[x]);
	}
	d1[x]=max(d1[x],fir[x]+sec[x]);
}
int minn=707185547,x4,y4;
int maxn,x5,y5;
int cal(int x,int y)
{
	if(x>y) swap(x,y);
	int yy=y;
	x=x/2+x%2;y=y/2+y%2;
	return max(x+y+1,yy);
}
void solve(int x,int d2,int lg)
{
//	cout<<d1[x]<<' '<<x<<' '<<d2<<' '<<lg<<endl;
	int t,tmp;
	if(x!=1)
	{
		t=cal(d1[x],d2);
	//	cout<<fa[x]<<' '<<x<<' '<<d1[x]<<' '<<d2<<endl;
		if(t<minn) minn=t,x4=fa[x],y4=x;
		if(d1[x]+d2+1>maxn) maxn=d1[x]+d2+1,x5=fa[x],y5=x;
	}
	int i,j;
	for(i=pre[x];i;i=nxt[i])
	{
		j=to[i];
		if(j==fa[x]) continue;
		t=fir[x];tmp=fd[x];
		if(tmp==d1[j]) tmp=sd[x];
		if(t==fir[j]+1)
		{
			t=sec[x];
			tmp=max(tmp,sec[x]+max(thr[x],lg));
		}
		else if(sec[x]==fir[j]+1) tmp=max(tmp,fir[x]+max(thr[x],lg));
		else tmp=max(tmp,fir[x]+max(sec[x],lg));
		t=max(lg,t);tmp=max(tmp,d2);
		solve(j,tmp,t+1);
	}
}
int t[5],T,ma;
bool del[N];
void dfs1(int x,int ff,int dd)
{
	int i,j;
	if(dd>ma) ma=dd,t[T]=x;
	for(i=pre[x];i;i=nxt[i])
	{
		j=to[i];
		if(j==ff||del[i]) continue;
		dfs1(j,x,dd+1);
	}
}
int ans[3],TT;
bool getans(int x,int ff,int dd)
{
	if(x==t[T])
	{
		if(ma==0) ans[TT]=x;
		return true;
	}
	int i,j;
	for(i=pre[x];i;i=nxt[i])
	{
		j=to[i];
		if(j==ff||del[i]) continue;
		if(getans(j,x,dd+1))
		{
			if(dd==ma/2) ans[TT]=x;
			return true;
		}
	}
	return false;
}
void findmin(int x,int y)
{
	int i;
	for(i=pre[x];i;i=nxt[i])
	if(to[i]==y) del[i]=true;
	for(i=pre[y];i;i=nxt[i])
	if(to[i]==x) del[i]=true;
	ma=-1;T=1;
	dfs1(x,y,0);
	ma=-1;T=2;
	dfs1(t[1],0,0);
	TT=1;
	getans(t[1],0,0);
	ma=-1;T=3;
	dfs1(y,x,0);
	ma=-1;T=4;
	dfs1(t[3],0,0);
	TT=2;
	getans(t[3],0,0);
	printf("%d %d %d %d %d\n",minn,x,y,ans[1],ans[2]);
	for(i=pre[x];i;i=nxt[i])
	if(to[i]==y) del[i]=false;
	for(i=pre[y];i;i=nxt[i])
	if(to[i]==x) del[i]=false;
}
void findmax(int x,int y)
{
	int i;
	for(i=pre[x];i;i=nxt[i])
	if(to[i]==y) del[i]=true;
	for(i=pre[y];i;i=nxt[i])
	if(to[i]==x) del[i]=true;
	ma=-1;T=1;
	dfs1(x,y,0);
	ma=-1;T=2;
	dfs1(t[1],0,0);
	ma=-1;T=3;
	dfs1(y,x,0);
	ma=-1;T=4;
	dfs1(t[3],0,0);
	printf("%d %d %d %d %d",maxn,x,y,t[1],t[3]);
}
int main()
{
	int n,m;
	n = read();
	int i,j,x,y;
	for(i=1;i<n;i++)
	{
		x = read();y = read();
		ae(x,y);ae(y,x);
	}
	dfs(1);
	solve(1,0,0);
	findmin(x4,y4);
	findmax(x5,y5);
}

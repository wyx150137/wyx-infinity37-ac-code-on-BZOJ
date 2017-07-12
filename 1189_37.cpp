
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define mid (l+r)/2
#define inf 0x3f3f3f3f
#define T n*n*m*m+2
const int N=25;
const int M=200000;
char s[N];
bool use[N][N],flag[N][N];
struct S{int x,y,c;}l[N*N];
struct Q{int st,en,va;}aa[M*2];
int n,m,map[N][N],f[N][N][N][N],sum,point[M],next[M*2],cur[M],dis[M],pre[M],gap[M],tot;
const int xi[4]={-1,0,0,1},yi[4]={0,-1,1,0};
inline void bfs(int xa,int ya)
{
	int i,h,t,k,x,y;
	memset(use,1,sizeof(use));
	h=t=1;l[h].x=xa;l[h].y=ya;l[h].c=0;
	while(h<=t){
		x=l[h].x;y=l[h].y;
		for(i=0;i<4;++i)
		{
			int xx=x+xi[i],yy=y+yi[i];
			if(xx>0&&xx<=n&&yy>0&&y<=m&&map[xx][yy]==1&&use[xx][yy])
			{
				l[++t].x=xx;l[t].y=yy;l[t].c=l[h].c+1;
				use[xx][yy]=false;
				f[xx][yy][xa][ya]=l[t].c;
				flag[xx][yy]=true;
			}
		}
		h+=1;
	}
}
inline void add(int x,int y,int z)
{
	tot+=1;next[tot]=point[x];point[x]=tot;
	aa[tot].st=x;aa[tot].en=y;aa[tot].va=z;
	tot+=1;next[tot]=point[y];point[y]=tot;
	aa[tot].st=y;aa[tot].en=x;aa[tot].va=0;
}
inline int ISAP(int ss,int tt)
{
	bool f;
	int minn,ans=0,i,u,y;
	memset(dis,0,sizeof(dis));
	memset(gap,0,sizeof(gap));
	memset(pre,0,sizeof(pre));
	gap[0]=tt-ss+1; u=ss;
	for(i=ss;i<=tt;++i) cur[i]=point[i];
	while(dis[ss]<tt-ss+1)
	{
		f=false;
		for(i=cur[u];i;i=next[i])
			if(aa[i].va>0&&dis[u]==dis[aa[i].en]+1)
			{
			cur[u]=i;f=true;break;
			}
		if(f)
		{
			pre[u=aa[i].en]=i;
			if(u==tt)
			{
				minn=inf;
				for(i=u;i!=ss;i=aa[pre[i]].st)
					minn=min(minn,aa[pre[i]].va);
				ans+=minn;
				for(i=u;i!=ss;i=aa[pre[i]].st)
				{
					aa[pre[i]].va-=minn;
					aa[pre[i]^1].va+=minn;
				}
				u=ss;
			}   
		}
		else
		{
			--gap[dis[u]];
			if(!gap[dis[u]]) return ans;
			y=2*tt; cur[u]=point[u];
			for(i=point[u];i;i=next[i])
				if(aa[i].va>0) y=min(y,dis[aa[i].st]);
			++gap[dis[u]=y+1];
			if(u!=ss) u=aa[pre[u]].st;
		}
	}
	return ans;
}
inline bool check(int x)
{
	int i,j,p,q;
	tot=1;
	memset(point,0,sizeof(point));
	memset(next,0,sizeof(next));
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
		{
		int now=((i-1)*m+j-1)*n*m;
		if(map[i][j]==0)
		{
			for(p=1;p<x;++p)
				add(now+p+1,now+p+2,inf),add(now+p+1,T,1);
			add(now+x+1,T,1);
		}
		if(map[i][j]==1)
		{
			add(1,now+1,1);
			for(p=1;p<=n;++p)
				for(q=1;q<=m;++q)
				if(f[i][j][p][q])
					add(now+1,((p-1)*m+q-1)*n*m+f[i][j][p][q]+1,1);
		}
		}
	return ISAP(1,T)==sum;
}
int main()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
	{
		scanf("%s",&s);
		for(j=0;j<m;++j)
		{
			if(s[j]=='D') map[i][j+1]=0;
			if(s[j]=='.') map[i][j+1]=1,sum+=1;
			if(s[j]=='X') map[i][j+1]=2;
		}
	}
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
		if(map[i][j]==0)
			bfs(i,j);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
		if(!flag[i][j]&&map[i][j]==1)
		{
			printf("impossible\n");
			return 0;
		}
	int l=1,r=n*m,ans=inf;
	while(l<r)
	{
		if(check(mid)) ans=min(ans,mid),r=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
}

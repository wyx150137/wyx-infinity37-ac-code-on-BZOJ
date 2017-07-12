
#include <cstdio>
#include <cctype>
#include <algorithm>
const int maxn=400010,inf=2000000010;
int ans,n,x,y,z,i,m,l,r,c[maxn*3],cnt;
inline int max(int a,int b)
{
	return a>b?a:b; 
}
inline void up(int&a,const int&b)
{
	if(a<b)a=b;
}
struct edge{int from,to,color;}e[maxn<<1];
struct data{int dep,sum;};
struct node{int v,lc,rc;}a[maxn*5];
int merge(int x,int y)
{
	if(!x || !y )return x|y;
	a[x].lc=merge(a[x].lc,a[y].lc);
	a[x].rc=merge(a[x].rc,a[y].rc);
	up(a[x].v,a[y].v);
	return x;
}
void add(int&i,int rl,int rr,int x,int v)
{
	if(!i)a[i=++cnt]=(node){v,0,0};
		else up(a[i].v,v);
	if(rl<rr)
	{
		int m=(rl+rr)>>1;
		if(x>m)add(a[i].rc,m+1,rr,x,v);
			else add(a[i].lc,rl,m,x,v);
	}
}
int query(int i,int rl,int rr,int l,int r)
{
	if(!i)return -inf;
	if(rl==l && rr==r)return a[i].v;
	int m=(rl+rr)>>1;
	if(l>m)return query(a[i].rc,m+1,rr,l,r);
		else if(r<=m)return query(a[i].lc,rl,m,l,r);
			else return max(query(a[i].lc,rl,m,l,m),query(a[i].rc,m+1,rr,m+1,r));
}
struct tree
{
	int xb,h[maxn],n,size[maxn],f[maxn],rt,sum,dep[maxn],ll,ss[maxn];
	bool b[maxn];
	data w[maxn];
	void addedge(int x,int y,int z)
	{
		e[++xb]=(edge){y,x,z};
		e[++xb]=(edge){x,y,z};
	}
	void dfs(int x,int fa)
	{
		size[x]=f[x]=1;
		for(int i=h[x];i<h[x+1];++i)
		{
			int y=e[i].to;
			if(y!=fa && !b[y])
			{
				dfs(y,x);
				size[x]+=size[y];
				up(f[x],size[y]);
			}
		}
		up(f[x],sum-size[x]);
		if(f[rt]>f[x])rt=x;
	}
	void got(int x,int fa,int dep,int color,int sum)
	{
		for(int y,i=h[x];i<h[x+1];++i)
		{
			y=e[i].to;
			if(y!=fa && !b[y])
			{
				if(e[i].color==color)w[++ll]=(data){dep+1,sum};
					else w[++ll]=(data){dep+1,sum+c[e[i].color]};
				got(e[i].to,x,dep+1,e[i].color,w[ll].sum);
			}
		}
	}
	void solve(int x)
	{
		b[x]=1;
		int i,rt1=0,rt2=cnt=0,j;
		for(i=h[x];i<h[x+1];++i)
		{   
			if(i>h[x] && e[i].color>e[i-1].color)rt1=merge(rt1,rt2),rt2=0;         
			if(!b[e[i].to])
			{
				w[ll=1]=(data){1,c[e[i].color]};
				got(e[i].to,x,1,e[i].color,c[e[i].color]);
				ss[i]=ll;
				for(j=1;j<=ll;++j)if(w[j].dep<=r)
				{
					if(w[j].dep>=l)up(ans,w[j].sum);
					if(w[j].dep<r)
					{
						up(ans,query(rt1,1,n,max(1,l-w[j].dep),r-w[j].dep)+w[j].sum);
						up(ans,query(rt2,1,n,max(1,l-w[j].dep),r-w[j].dep)-c[e[i].color]+w[j].sum);
					}
				}
				for(j=1;j<=ll;++j)if(w[j].dep<=r)add(rt2,1,n,w[j].dep,w[j].sum);
			}
		}
		for(i=h[x];i<h[x+1];++i)
			if(!b[e[i].to])
			{
				sum=ss[i];
				rt=0;
				dfs(e[i].to,x);
				solve(rt);
			}
	}
}t;
bool cmp(const edge&a,const edge&b)
{
	return a.from==b.from?a.color<b.color:a.from<b.from;
}
int main()
{
	a[0].v=-inf;
	scanf("%d%d%d%d",&n,&m,&l,&r);
	t.n = n;
	for(i=1;i<=m;++i)scanf("%d",&c[i]);
	for(i=1;i<n;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		t.addedge(x,y,z);
	}
	std::sort(e+1,e+((n-1)*2)+1,cmp);
	for(i=1;i<=((n-1)<<1);++i)
		if(!t.h[e[i].from])t.h[e[i].from]=i;
	t.h[n+1]=(n-1)<<1|1; 
	t.f[t.rt=0]=inf;
	t.sum=n;
	ans=-inf;
	t.dfs(1,0);
	t.solve(t.rt);
	printf("%d\n",ans);
}

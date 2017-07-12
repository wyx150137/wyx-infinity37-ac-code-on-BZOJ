
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int M = 1e5+5;
const int INF = 0x3f3f3f3f;
struct E
{int next,to,val;}e[M];
struct Ask
{
	int id;
	int x1,y1,x2,y2;
	Ask(){}
}a[M],b[M];
int head[M],tot;
int n,m;
inline int getid(int i,int j)
{
	return i*m-m+j;
}
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
bool cmp(const int &a,const int &b)
{
	return a>b;
}
int d[M],id[M],cnt,ans[M],q[M];
void goup(int x)
{
	int y=q[x],t=d[y];
	for (; x>1 && t<d[q[x>>1]]; x>>=1)
	{
		q[x]=q[x>>1]; id[q[x]]=x;
	}
	q[x]=y; id[y]=x;
}
void godown(int x)
{
	int y=x<<1,z=q[x],t=d[z];
	if (y<cnt && d[q[y|1]]<d[q[y]]) y|=1;
	while (y<=cnt && d[q[y]]<t)
	{
		q[x]=q[y]; id[q[x]]=x;
		x=y; y<<=1; if (y<cnt && d[q[y|1]]<d[q[y]]) y|=1;
	}
	q[x]=z; id[z]=x;
}
void dijk(int s,int x1,int y1,int x2,int y2)
{
	register int i,j;
	d[s] = 0,id[s] =1,cnt=0;
	q[++cnt] =s;
	for(i = x1;i<= x2;i++)
		for(j = y1;j<= y2;j++)
			if(getid(i,j)!=s)
			{
				int no = getid(i,j);
				q[++cnt] = no;
				d[no] = INF;id[no] = cnt;
			}
	while(cnt)
	{
		int x=q[1];
		q[1]=q[cnt--];
		id[q[1]]=1;
		godown(1);
		for(i = head[x];i;i=e[i].next)
		{
			int to = e[i].to,u = (to-1)/m+1,v = (to-1)%m+1;
			if(u<=x2&&u>=x1&&v<=y2&&v>=y1&&d[x]+e[i].val<d[to])
				{d[to]=d[x]+e[i].val;goup(id[to]);}
		}
	}
}
/*queue<int>Q;
bool vis[M];
void dijk(int s,int x1,int y1,int x2,int y2)
{
	for(int i = x1;i<=x2;i++)
		for(int j = y1;j<= y2;j++)
			d[getid(i,j)] = INF;
	Q.push(s);d[s] = 0;vis[s] =true;
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		vis[x] =false;
		for(int i = head[x];i;i=e[i].next)
		{
			int no = e[i].to;
			int u = (no-1)/m+1,v = (no-1)%m+1;
			if(u<=x2&&u>=x1&&v<=y2&&v>=y1&&d[no]>d[x]+e[i].val)
			{
				d[no] =d[x]+e[i].val;
				if(!vis[no])
					Q.push(no);
			}
		}
	}
}*/
void solve(int x1,int y1,int x2,int y2,int l,int r)
{
	int i,j,k;
	int mid;
	if(l>r)return ;
	if(x2-x1>y2-y1)
	{
		mid = (x1+x2)>>1;
		for(i = y1;i<= y2;i++)
		{
			dijk(getid(mid,i),x1,y1,x2,y2);
			for(j = l;j<= r;j++)
				ans[a[j].id] = min(ans[a[j].id],d[getid(a[j].x1,a[j].y1)]+d[getid(a[j].x2,a[j].y2)]);
		}
		j = l-1,k = r+1;
		for(i = l;i<= r;i++)
			if(a[i].x1<mid&&a[i].x2<mid)b[++j]=a[i];
			else if(a[i].x1>mid&&a[i].x2>mid)b[--k]=a[i];
		for(i = l;i<= j;i++)a[i]=b[i];solve(x1,y1,mid-1,y2,l,j);
		for(i = r;i>= k;i--)a[i]=b[i];solve(mid+1,y1,x2,y2,k,r);
	}else
	{
		mid = (y1+y2)>>1;
		for(i = x1;i<= x2;i++)
		{
			dijk(getid(i,mid),x1,y1,x2,y2);
			for(j = l;j<= r;j++)
				ans[a[j].id] = min(ans[a[j].id],d[getid(a[j].x1,a[j].y1)]+d[getid(a[j].x2,a[j].y2)]);
		}
		j = l-1,k = r+1;
		for(i = l;i<= r;i++)
			if(a[i].y1<mid&&a[i].y2<mid)b[++j]=a[i];
			else if(a[i].y1>mid&&a[i].y2>mid)b[--k]=a[i];
		for(i = l;i<= j;i++)a[i]=b[i];solve(x1,y1,x2,mid-1,l,j);
		for(i = r;i>= k;i--)a[i]=b[i];solve(x1,mid+1,x2,y2,k,r);
	}
}
int main()
{
	//freopen("ex_tourist3.in","r",stdin);
	memset(ans,0x3f,sizeof(ans));
	int q,x;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= n;i++)
		for(int j = 1;j<m;j++)
		{
			scanf("%d",&x);
			add(getid(i,j),getid(i,j+1),x);
			add(getid(i,j+1),getid(i,j),x);
		}
	for(int i = 1;i< n;i++)
		for(int j = 1;j<= m;j++)
		{
			scanf("%d",&x);
			add(getid(i,j),getid(i+1,j),x);
			add(getid(i+1,j),getid(i,j),x);
		}
	scanf("%d",&q);
	for(int i = 1;i<= q;i++)
	{
		scanf("%d%d%d%d",&a[i].x1,&a[i].y1,&a[i].x2,&a[i].y2);
		a[i].id = i;
	}
	solve(1,1,n,m,1,q);
	for(int i = 1;i<= q;i++)
		printf("%d\n",ans[i]);
	return 0;
}

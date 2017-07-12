
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 5e4+5;
const int M = 1e5+5;
struct E
{
	int x,y,a,b;
	bool operator <(const E &s)const
	{
		return a<s.a;
	}
}e[M];
int Fa[N];
int getfa(int x)
{
	if(Fa[x]==x||!Fa[x])return Fa[x]=x;
	else   return Fa[x] = getfa(Fa[x]);
}
void merge(int x,int y)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	Fa[x] = y;
}
int ch[N+M][2],fa[N+M],size[N+M],val[N+M],mx[N+M];
bool rev[N+M];
inline bool is_root(int p)
{
	return ch[fa[p]][0]!=p&&ch[fa[p]][1]!=p;
}
inline void init(int p,int v)
{
	ch[p][0]=ch[p][1]=fa[p]=0;
	val[p]=v,mx[p] = p;
}
inline void reverse(int p)
{
	rev[p]^=1;
	swap(ch[p][0],ch[p][1]);
}
inline void Push_down(int p)
{
	if(!is_root(p))Push_down(fa[p]);
	if(rev[p])
	{
		if(ch[p][0])reverse(ch[p][0]);
		if(ch[p][1])reverse(ch[p][1]);
		rev[p] = false;
	}
}
inline void Push_up(int p)
{
	size[p] = size[ch[p][0]]+1+size[ch[p][1]];
	int ls = mx[ch[p][0]],rs = mx[ch[p][1]];
	if(val[ls]>=val[p]&&val[ls]>=val[rs])mx[p] = ls;
	else if(val[rs]>=val[p]&&val[rs]>=val[ls])mx[p] = rs;
	else mx[p] = p;
}
void rotate(int x)
{
	int y = fa[x],z = fa[y];
	int d = ch[y][1]==x;
	if(!is_root(y))
	{
		if(ch[z][0]==y)ch[z][0] = x;
		else if(ch[z][1]==y)ch[z][1] = x;
	}
	fa[y] = x,fa[x] = z,fa[ch[x][d^1]] = y;
	ch[y][d] = ch[x][d^1],ch[x][d^1] = y;
	Push_up(y),Push_up(x);
}
void splay(int x)
{
	Push_down(x);
	while(!is_root(x))
	{
		int y = fa[x],z = fa[y];
		if(!is_root(y))
		{
			if((ch[z][0]==y)^(ch[y][0]==x))rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	Push_up(x);
}
void access(int x)
{
	int t = 0;
	while(x)
	{
		splay(x);
		ch[x][1] = t;
		Push_up(x);
		t = x;
		x = fa[x];
	}
}
void move_to_root(int x)
{
	access(x);
	splay(x);
	reverse(x);
}
void link(int x,int y)
{
	move_to_root(x);
	fa[x] = y;
}
void cut(int x,int y)
{
	move_to_root(x);
	access(y);
	splay(y);
	fa[x] = 0;
	ch[y][0] = 0;
	Push_up(y);
}
int getans(int x,int y)
{
	move_to_root(x);
	access(y);splay(y);
	return mx[y];
}
int main()
{
	int n,m,x,y;
	scanf("%d%d",&n,&m);
	for(int i = 1;i<= m;i++)
		scanf("%d%d%d%d",&e[i].x,&e[i].y,&e[i].a,&e[i].b);
	sort(e+1,e+m+1);
	for(int i = 1;i<= m;i++)val[i+n] = e[i].b;
	int ans = 0x3f3f3f3f;
	for(int i = 1;i<= m;i++)
	{
		x = e[i].x,y = e[i].y;
		int fx = getfa(x),fy = getfa(y);
		if(fx!=fy)
		{
			link(x,i+n);link(i+n,y);
			merge(fx,fy);
		}else
		{
			int k = getans(x,y);
			if(val[k]>e[i].b)
			{
				cut(e[k-n].x,k);
				cut(k,e[k-n].y);
				link(x,i+n);link(i+n,y);
			}
		}
		if(getfa(1)==getfa(n))
			ans = min(ans,e[i].a+val[getans(1,n)]);
	}
	if(ans!=0x3f3f3f3f)printf("%d\n",ans);
	else puts("-1");
	return 0;
}

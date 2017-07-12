
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct Edge
{
	int x,y,st,ed;
	Edge(int _x,int _y,int _s,int _e):x(_x),y(_y),st(_s),ed(_e){}
};
const int N = 100005;
int fa[N],rnk[N],stack[N<<2],a[N],top;
int getfa(int x)
{
	while(fa[x]!=x)x=fa[x];
	return fa[x]=x;
}
int getdis(int x)
{
	int res = 0;
	while(fa[x]!=x&&fa[x])res^=a[x],x=fa[x];
	return res;
}
void uni(int x,int y,int z)
{
	x = getfa(x),y = getfa(y);
	if(x==y)return ;
	if(rnk[x]>rnk[y])swap(x,y);
	if(rnk[x]==rnk[y])
		rnk[y]++,stack[++top] = y;
	fa[x] = y,a[x] = z;stack[++top] = x;
}
void reset(int bot)
{
	while(top>bot)
	{
		if(stack[top]<0)
			rnk[-stack[top]]--;
		else 
			fa[stack[top]] = stack[top],a[stack[top]] = 0;
		top--;
	}
}
void solve(int l,int r,vector<Edge> &e)
{
	int mid = (l+r)>>1,bot = top;
	vector<Edge>L,R;
	for(int i = 0;i<e.size();i++)
	{
		if(e[i].st==l&&e[i].ed==r)
		{
			int _x = getfa(e[i].x),_y = getfa(e[i].y);
			int _z =getdis(e[i].x)^getdis(e[i].y)^1;
			if(_x!=_y)uni(_x,_y,_z);
			else if(_z&1)
			{
				for(int i = l;i<= r;i++)
					printf("No\n");
				reset(bot);
				return ;
			}
		}
		else if(e[i].ed<=mid)L.push_back(e[i]);
		else if(e[i].st>mid)R.push_back(e[i]);
		else
			L.push_back(Edge(e[i].x,e[i].y,e[i].st,mid)),
			R.push_back(Edge(e[i].x,e[i].y,mid+1,e[i].ed));
	}
	if(l==r)printf("Yes\n");
	else 
		solve(l,mid,L),solve(mid+1,r,R);
	reset(bot);
}
int main()
{
	int n,m,T,x,y,s,e;
	scanf("%d%d%d",&n,&m,&T);
	for(int i = 1;i<= n;i++)fa[i]=i;
	vector<Edge>E;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d%d%d%d",&x,&y,&s,&e);
		s++;
		if(s>e)continue;
		E.push_back(Edge(x,y,s,e));
	}
	solve(1,T,E);
	return 0;
}

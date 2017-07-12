
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int mod = 51061;
int ch[N][2],add[N],mul[N],size[N],fa[N],val[N],sum[N];
bool rev[N];
bool is_root(int p)
{
	return ch[fa[p]][0]!=p&&ch[fa[p]][1]!=p;
}
void init(int p,int v)
{
	ch[p][0]=ch[p][1]=fa[p]=0;
	size[p]=1;
	mul[p] = 1,add[p]=0,rev[p]=false;
	sum[p]=val[p]=v;
}
void Multiply(int p,int c)
{
	if(!p)return ;
	mul[p] = (ll)mul[p]*c%mod;
	sum[p] = (ll)sum[p]*c%mod;
	val[p] = (ll)val[p]*c%mod;
	add[p] = (ll)add[p]*c%mod;
}
void Add(int p,int c)
{
	if(!p)return ;
	(add[p]+=c)%=mod;
	(val[p]+=c)%=mod;
	(sum[p]+=(ll)size[p]*c%mod)%=mod;
}
void Reverse(int p)
{
	rev[p]^=1;
	swap(ch[p][0],ch[p][1]);
}
void Push_down(int p)
{
	if(!is_root(p))Push_down(fa[p]);
	if(mul[p]!=1)
	{
		Multiply(ch[p][0],mul[p]);
		Multiply(ch[p][1],mul[p]);
		mul[p] = 1;
	}
	if(add[p])
	{
		Add(ch[p][0],add[p]);
		Add(ch[p][1],add[p]);
		add[p] = 0;
	}
	if(rev[p])
	{
		Reverse(ch[p][0]);
		Reverse(ch[p][1]);
		rev[p] = false;
	}
}
void Push_up(int p)
{
	if(!p)return ;
	size[p] = size[ch[p][0]]+1+size[ch[p][1]];
	sum[p] = (sum[ch[p][0]]+val[p]+sum[ch[p][1]])%mod;
}
void rotate(int x)
{
	int y = fa[x],z = fa[y];
	int d = ch[y][1]==x;
	if(!is_root(y))
	{
		if(ch[z][0]==y)ch[z][0] = x;
		if(ch[z][1]==y)ch[z][1] = x;
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
			if((ch[y][0]==x)^(ch[z][0]==y))rotate(x);
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
	Reverse(x);
}
void Link(int x,int y)
{
	move_to_root(x);
	fa[x] = y;
}
void Cut(int x,int y)
{
	move_to_root(x);
	access(y);
	splay(y);
	fa[x] = 0;ch[y][0] = 0;
	Push_up(y);
}
struct E
{
	int next,to;
}e[N<<1];
int head[N],tot;
void adde(int x,int y)
{
	e[++tot].to = y;e[tot].next = head[x];head[x] = tot;
	e[++tot].to = x;e[tot].next = head[y];head[y] = tot;
}
queue<int>Q;
void bfs()
{
	Q.push(1);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i=e[i].next)
			if(e[i].to!=fa[x])
			{
				fa[e[i].to] = x;
				Q.push(e[i].to);
			}
	}
}
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)init(i,1);
	int u,v;
	for(int i = 1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		adde(u,v);
	}
	bfs();
	char opt[3];
    int x,y,a,b,c;
    while(q--)
    {
        scanf("%s",opt);
        if(opt[0]=='+')
        {
            scanf("%d%d%d",&x,&y,&c);
            move_to_root(x);
            access(y);splay(y);
            Add(y,c);
        }else if(opt[0]=='-')
        {
            scanf("%d%d%d%d",&x,&y,&a,&b);
            Cut(x,y);
            Link(a,b);
        }else if(opt[0]=='*')
        {
            scanf("%d%d%d",&x,&y,&c);
            move_to_root(x);
            access(y),splay(y);
            Multiply(y,c);
        }else
        {
            scanf("%d%d",&x,&y);
            move_to_root(x);
            access(y),splay(y);
            printf("%d\n",sum[y]);
        }
    }
	return 0;
}

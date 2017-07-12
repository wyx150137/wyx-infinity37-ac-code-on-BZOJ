
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int mod = 10007;
struct data
{
	int k,b;
	data(int _k=1,int _b=0):k(_k%mod),b(_b%mod){}
	data operator +(const data &s)const
	{
		data res;
		res.k = k*s.k%mod;
		res.b = (b*s.k+s.b)%mod;
		return res;
	}
	int cal(int x){x%=mod;return (k*x+b)%mod;}
};
void ex_gcd(int a,int b,int &x,int &y)
{
	if(!b)y=0,x=1;
	else
	{
		ex_gcd(b,a%b,y,x);
		y-=a/b*x;
	}
}
const int N = 6e4+5;
int ch[N][2],fa[N],sp_fa[N],size[N];
data sum[N],val[N];
bool vis[N],ins[N];
void dfs(int x)
{
	ins[x] = vis[x] = true;
	int v = fa[x];
	if(ins[v])
	{
		sp_fa[x] = v;
		fa[x] = 0;
	}
	if(!vis[v])dfs(v);
	ins[x] = false;
}
bool is_root(int x)
{
	return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}
void Push_up(int x)
{
	sum[x] = sum[ch[x][0]]+val[x]+sum[ch[x][1]];
}
void rotate(int x)
{
	int y = fa[x],z = fa[y];
	int d = ch[y][1]==x;
	if(!is_root(y))
	{
		if(ch[z][0]==y)ch[z][0] = x;
		else ch[z][1] = x;
	}
	fa[y] = x;fa[x] = z;fa[ch[x][d^1]] = y;
	ch[y][d] = ch[x][d^1],ch[x][d^1] = y;
	Push_up(y);
}
void splay(int x)
{
	while(!is_root(x))
	{
		int y = fa[x],z = fa[y];
		if(!is_root(y))
		{
			if((ch[y][0]==ch[x][0])^(ch[z][0]==ch[y][0]))rotate(x);
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
int Find_root(int x)
{
	access(x);
	splay(x);
	int rot = x;
	while(ch[rot][0])rot = ch[rot][0];
	splay(rot);return rot;
}
int Getans(int x)
{
	access(x);
	splay(x);
	data v1 = sum[x];
	int rot = Find_root(x),f = sp_fa[rot];
	access(f);splay(f);
	data v2 = sum[f];
	if(v2.k==1)return v2.b?-1:-2;
	if(v2.k==0)return v1.cal(v2.b);
	int X,Y;
	ex_gcd(v2.k-1,mod,X,Y);
	int tmp = (mod-X)%mod*v2.b%mod;
	return v1.cal(tmp);
}
void Cut(int x)
{
	access(x);
	splay(x);
	fa[ch[x][0]] = 0;
	ch[x][0] = 0;
	Push_up(x);
}
void Link(int x,int y)
{
	access(x);splay(x);
	fa[x] = y;
}
bool in_circle(int x,int rot)
{
	int f = sp_fa[rot];
	if(x==f)return true;
	access(f);
	splay(f);splay(x);
	return !is_root(f);
}
void update(int u,int f,int k,int b)
{
    access(u);
    splay(u);
    val[u]=data(k,b);
    Push_up(u);
    int ro=Find_root(u);
    if(u==ro)
    {
        int rf=Find_root(f);
        if(rf==ro)sp_fa[u]=f;
        else
        {
            sp_fa[u]=0;
            Link(u,f);
        }
    }else
    {
        if(in_circle(u,ro))
        {
            Cut(u);
            Link(ro,sp_fa[ro]);
            sp_fa[ro]=0;
            int rf=Find_root(f);
            if(rf==u)sp_fa[u]=f;
            else Link(u,f);
        }else
        {
            Cut(u);
            int rf=Find_root(f);
            if(rf==u)sp_fa[u]=f;
            else Link(u,f);
        }   
    }
}
int main()
{
	int n,k,b;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d%d%d",&k,&fa[i],&b);
		val[i] = sum[i] = data(k,b);
	}
	for(int i = 1;i<= n;i++)if(!vis[i])dfs(i);
	int q,x,f;
	char opt[3];
	scanf("%d",&q);
	while(q--)
	{
		scanf("%s%d",opt,&x);
		if(opt[0]=='A')printf("%d\n",Getans(x));
		else
		{
			scanf("%d%d%d",&k,&f,&b);
			update(x,f,k,b);
		}
	}
	return 0;
}

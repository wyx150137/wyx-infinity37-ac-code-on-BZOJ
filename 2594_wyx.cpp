
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define max(a,b) ((a)>(b)?(a):(b))
#define reverse(k) rev[k] ^= 1, swap(ch[k][0],ch[k][1])
const int M = 1100000+5;
const int Maxq = 100010+5;
const int N = M ;
using namespace std;

int ch[N][2],tr[N],pos[N];
int rev[N],val[N],fa[N],root[N];

void updata(int k)
{
	tr[k] = val[k], pos[k] = k;
	if(tr[ch[k][0]] > tr[k]) tr[k] = tr[ch[k][0]], pos[k] = pos[ch[k][0]];
	if(tr[ch[k][1]] > tr[k]) tr[k] = tr[ch[k][1]], pos[k] = pos[ch[k][1]];
}

void push(int k)
{
	if(rev[k])
	{
		rev[k] = 0;
		if(ch[k][0]) reverse(ch[k][0]);
		if(ch[k][1]) reverse(ch[k][1]);
	}
}

inline void down(int k)
{
	if(!k) return;
	if(!root[k]) down(fa[k]);
	push(k);
}

void rotate(int x)
{
	int y = fa[x], k = ch[y][1] == x;
	ch[y][k] = ch[x][!k], fa[ch[y][k]] = y;
	ch[x][!k] = y, fa[x] = fa[y], fa[y] = x;
	if(root[y]) swap(root[x],root[y]);
	else ch[fa[x]][ch[fa[x]][1] == y] = x;
	updata(y);
}

void Splay(int x)
{
	if(!x) return;
	down(x);
	while(!root[x])
	{
		int y = fa[x], z = fa[y];
		if(root[y]) rotate(x);
		else if((ch[z][1] == y) == (ch[y][1] == x)) rotate(y),rotate(x);
		else rotate(x),rotate(x);
	}
	updata(x);
}

void access(int x)
{
	if(!x) return;
	int y = 0;
	while(x)
	{
		Splay(x); root[ch[x][1]] = 1,root[y] = 0;
		ch[x][1] = y; updata(x);y = x ; x = fa[x];
	}
}

inline void move(int x)
{
	access(x);
	Splay(x);
	reverse(x);
}

inline void link(int x,int y)
{
	move(x);
	fa[x] = y;
}

inline void cut(int x,int y)
{
	move(x); access(y); Splay(y);
	ch[y][0] = fa[x] = 0; root[x] = 1;
	updata(y);
}

int n,m,Q;

struct data
{
	int from,to,val,opt;
	bool del;
	int id;
	data () {}
	data (int _from,int _to,int _val = 0,bool _del = 0,int _id = 0)
	:from(_from),to(_to),val(_val),del(_del),id(_id){}
	bool operator < (const data &z)const
	{
		return from ^ z.from ? from < z.from : to < z.to;
	}
}edge[N],q[Maxq];

bool cmp1(const data &a,const data &b)
{
	if(a.val ^ b.val) return a.val < b.val;
	else if(a.from ^ b.from) return a.from < b.from;
	return a.to < b.to;
}

inline int find(int from,int to)
{
	return lower_bound(edge+1,edge+m+1,data(from,to)) - edge;
}


char getc()
{
    static const int LEN = 1<<15;
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

namespace Union_Find_Set
{
	int F[N],sum,size[N];

	void init(int x)
	{
		sum = x;
		for(int i=1;i<=sum;++i) size[F[i] = i] = 1;
	}

	inline int Find(int x)
	{
		return F[x] ^ x ? F[x] = Find(F[x]) : F[x];
	}

	bool Union(int x,int y)
	{
		int fx = Find(x), fy = Find(y);
		if(fx == fy) return 0;
		if(size[fx] < size[fy]) swap(fx,fy);
		size[fx] += size[fy]; F[fy] = fx;
		return 1;
	}
}

using namespace Union_Find_Set;

int ans[N];

int main()
{
	n = read(), m = read(), Q = read();
	Union_Find_Set :: init(n+m);
	for(int i=1;i<=n+m;++i) root[i] = 1, pos[i] = i;

	for(int i=1;i<=m;++i){
		edge[i].from = read(),edge[i].to = read(), edge[i].val = read();
		if(edge[i].from > edge[i].to) swap(edge[i].from,edge[i].to); 
	}

	sort(edge+1,edge+m+1,cmp1);

	for(int i=1;i<=m;++i)
		tr[i+n] = val[i+n] = edge[i].val, edge[i].id = i;
	
	sort(edge+1,edge+m+1);

	for(int i=1;i<=Q;++i){
		q[i].opt = read(),q[i].from = read(), q[i].to = read();
		if(q[i].from > q[i].to) swap(q[i].from,q[i].to);
		if(q[i].opt == 2) {
			int tmp = find(q[i].from,q[i].to);
			edge[tmp].del = 1; q[i].id = edge[tmp].id;
		}
	}

	sort(edge+1,edge+m+1,cmp1);

	for(int i=1;i<=m;++i)
		if(!edge[i].del)
			if(Union_Find_Set::Union(edge[i].from,edge[i].to))
				link(edge[i].from,i+n),link(i+n,edge[i].to);

	for(int i=Q;i;--i)
	{
		int x = q[i].from, y = q[i].to;
		if(q[i].opt == 1)
		{
			move(x);access(y);Splay(y);
			ans[i] = tr[y];
		}
		else
		{
			move(x);access(y);Splay(y);
			int tt = pos[y], tmp = q[i].id;
			if(edge[tmp].val < val[tt])
			{
				cut(edge[tt-n].from,tt);
				cut(tt,edge[tt-n].to);
				link(x,tmp+n), link(tmp+n,y);
			}
		}
	}

	for(int i=1;i<=Q;++i)
		if(q[i].opt == 1)
			printf("%d\n",ans[i]);
}

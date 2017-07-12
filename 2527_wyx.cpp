
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 300000+5;
const int M = N << 2;
using namespace std;

#define min(a,b) ((a)<(b)?(a):(b))
  
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

int lazy[M];

inline void down(int k,int l,int r)
{
	int tmp = lazy[k];
	if( l==r || !tmp) return;
	lazy[k<<1] += tmp;
	lazy[k<<1] = min(lazy[k<<1],(int)1e9);
	lazy[k<<1|1] += tmp;
	lazy[k<<1|1] = min(lazy[k<<1|1],(int)1e9);
	lazy[k] = 0;
}

void change(int k,int l,int r,int x,int y,int z)
{
	if(l==x && r==y)
	{
		lazy[k] += z;
		if(lazy[k] > 1e9)
			lazy[k] = 1e9;
		return;
	}
	down(k,l,r);
	int mid = (l+r)>>1;
	if(y <= mid) change(k<<1,l,mid,x,y,z);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,z);
	else change(k<<1,l,mid,x,mid,z),change(k<<1|1,mid+1,r,mid+1,y,z);
}

int Task(int k,int l,int r,int pos)
{
	if(l==r)
		return min(lazy[k],(int)1e9);
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(pos <= mid)return Task(k<<1,l,mid,pos);
	else return Task(k<<1|1,mid+1,r,pos);
}

struct q
{
	int l,r;
	int need;
	int x;
	void out()
	{
		printf("now = %d l = %d r = %d need = %d\n",x,l,r,need);
	}
}ask[M];

struct country
{
	int next,to;
	country () {}
	country (int _next,int _to)
	:next(_next),to(_to){}
}tmp[M];

int mp[N];

inline void countryadd(int x,int y)
{
	static int cnt = 0;
	tmp[++cnt] = country(mp[x],y);
	mp[x] = cnt;
}

struct data
{
	int next,to;
	data () {}
	data (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

int head[N];
int cnt = 0;

inline void add(int x,int y)
{
	edge[++cnt] = data(head[x],y);
	head[x] = cnt;
}

int tmpcnt;
int tmphead[N];

struct tmpdata
{
	int next,to;
	tmpdata () {}
	tmpdata (int _next,int _to)
	:next(_next),to(_to){}
}tmpedge[M];

inline void tmpadd(int x,int y)
{
	tmpedge[++tmpcnt] = tmpdata(tmphead[x],y);
	tmphead[x] = tmpcnt;
}

int T[N];

struct oper
{
	int l,r;
	int z;
}opt[N];

int ans[N];

int main()
{
//	freopen("16.in","r",stdin);	
	int n = read(), m =read();
	for(int i=1;i<=m;++i)
	{
		int tt = read();
		countryadd(tt,i);
	}
	for(int i=1;i<=n;++i) T[i] = read();
	int k = read();
	for(int i=1;i<=k;++i) opt[i].l = read(),opt[i].r = read(),opt[i].z = read();

	int tttt = k + 1 ;
	tttt >>= 1;
	for(int i=1;i<=n;++i)
	{
		ask[i].x = i;
		ask[i].l = 1;
		ask[i].r = k + 1;
		ask[i].need = T[i];
		add(tttt,i);
	}

	int tot = 21;
	while(tot--)
	{
//		cout << tot << endl;
		memset(lazy,0,sizeof lazy);
		cnt = tmpcnt = 0;
		for(int i=1;i<=k;++i)
		{
			if(opt[i].l <= opt[i].r)
				change(1,1,m,opt[i].l,opt[i].r,opt[i].z);
			else change(1,1,m,1,opt[i].r,opt[i].z),change(1,1,m,opt[i].l,m,opt[i].z);
			for(int j=head[i];j;j=edge[j].next)
			{
				int sum = 0;
				int now = edge[j].to;
	//			ask[now].out();
				if(ask[now].l == ask[now].r)
				{
					ans[now] = i;
					head[i] = edge[j].next;
					continue;
				}

				for(int l=mp[now];l;l=tmp[l].next)
				{
					sum = sum + Task(1,1,m,tmp[l].to);
					if(sum > 1e9) sum = 1e9;
				}

				int nowmid ;
				if(sum >= ask[now].need)
				{
					ask[now].r = i;
					nowmid = (ask[now].r + ask[now].l) >> 1;
					tmpadd(nowmid,ask[now].x);
				}

				else{
					ask[now].l = i + 1;
					nowmid = (ask[now].r + ask[now].l) >> 1;
					tmpadd(nowmid,ask[now].x);	
				}
			}
		}

		memcpy(head,tmphead,sizeof tmphead);
		for(int i=1;i<=tmpcnt;++i)
			edge[i].next = tmpedge[i].next,edge[i].to = tmpedge[i].to;
		memset(tmphead,0,sizeof tmphead);
	}
	for(int i=1;i<=n;++i)
	{
		if(ans[i])
			printf("%d\n",ans[i]);
		else puts("NIE");
	}
} 

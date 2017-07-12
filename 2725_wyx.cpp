
#include <map>
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define mp make_pair
#define fir first
#define sec second
typedef long long LL;
const int N = 2e5+5;
const int M = N << 1;

LL tr[N<<2];

inline void change(int k,int l,int r,int x,int y,LL val) {
	if(l==x && r==y) {
		tr[k] = min(tr[k],val);
		return ;
	}
	int mid = (l+r) >> 1;
	if(y <= mid) change(k<<1,l,mid,x,y,val);
	else if(x > mid) change(k<<1|1,mid+1,r,x,y,val);
	else change(k<<1,l,mid,x,mid,val), change(k<<1|1,mid+1,r,mid+1,y,val);
}

LL ask(int k,int l,int r,int pos) {
	if(l==r) return tr[k];
	int mid = (l+r) >> 1;
	if(pos <= mid) return min(ask(k<<1,l,mid,pos),tr[k]);
	else return min(ask(k<<1|1,mid+1,r,pos),tr[k]);
}

int head[N];

namespace Heap
{
	LL h[N];
	int pos[N],tot;
	inline void up(int x)
	{
		if(x==1)
			return;
		while(h[x]<h[x>>1])
		{
			if(x==1)break;
			swap(h[x],h[x>>1]);
			swap(pos[x],pos[x>>1]);
			x>>=1;
		}
	}
	inline void push(LL x,int y)
	{
		h[++tot]=x;
		pos[tot]=y;
		up(tot);
	}
	inline int pop()
	{
		swap(h[1],h[tot]);
		swap(pos[1],pos[tot--]);
		int i=1;
		while((((i<<1)<=tot)&&(h[i]>h[i<<1]))||(((i<<1)+1<=tot)&&(h[i]>h[(i<<1)+1])))
		{
			if((i<<1)+1>tot)
			{
				swap(h[i],h[i<<1]);
				swap(pos[i],pos[i<<1]);
				i<<=1;
			}
			else
			{
				int tmp=(h[i<<1]<h[(i<<1)+1])?(i<<1):((i<<1)+1);
				swap(h[i],h[tmp]);
				swap(pos[i],pos[tmp]);
				i=tmp;
			}               
		}
		return pos[tot+1];    
	}
	inline bool empty()
	{
		return tot == 0;
	}
}

struct graph {
	int next,to; LL val;
	graph () {}
	graph (int _next,int _to,LL _val)
	:next(_next),to(_to),val(_val){}
}edge[M<<1];

inline void add(int x,int y,int z) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z); 
	head[x] = cnt;
}

int n, m, q, s, t, from1[N], from2[N], from3[N], pos[N], stack[N], top;
LL f[N], g[N];
map <pair<int,int>, int > relable;

bool in[N];


void dij1() {
	memset(in,false,sizeof in);
	memset(f,0x3f,sizeof f); f[s]=0;
	Heap :: push(0,s);
	while(!Heap :: empty())
	{
		int now  = Heap :: pop();
		//cout << now << endl;
		if(in[now])continue;  in[now]=1;
		for(int i=head[now];i;i=edge[i].next)
		{
			if(f[edge[i].to]>f[now]+edge[i].val)
			{
				f[edge[i].to]=f[now]+edge[i].val;
				from1[edge[i].to] = now;
				Heap :: push(f[edge[i].to],edge[i].to);
			}
		}
	}
}

void dij2() {
	memset(in,false,sizeof in);
	memset(f,0x3f,sizeof f); f[s]=0;
	Heap :: push(0,s);
	while(!Heap :: empty())
	{
		int now  = Heap :: pop();
		if(pos[now]) from2[now] = now;
		if(in[now])continue;  in[now]=1;
		for(int i=head[now];i;i=edge[i].next)
		{
			if(f[edge[i].to]>f[now]+edge[i].val)
			{
				f[edge[i].to]=f[now]+edge[i].val;
				from2[edge[i].to] = from2[now];
				Heap :: push(f[edge[i].to],edge[i].to);
			}
		}
	}
}

void dij3() {
	memset(in,false,sizeof in);
	memset(f,0x3f,sizeof f); f[t]=0;
	Heap :: push(0,t);
	while(!Heap :: empty())
	{
		int now  = Heap :: pop();
		if(pos[now]) from3[now] = now;
		if(in[now]) continue;  in[now]=1;
		for(int i=head[now];i;i=edge[i].next)
		{
			if(f[edge[i].to]>f[now]+edge[i].val)
			{
				f[edge[i].to]=f[now]+edge[i].val;
				from3[edge[i].to] = from3[now];
				Heap :: push(f[edge[i].to],edge[i].to);
			}
		}
	}
	memcpy(g,f,sizeof g);
}

inline char getc()
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
 
inline int read()
{
	static char ch;
	static int D;
	while(!isdigit(ch=getc()));
	for(D=ch-'0'; isdigit(ch=getc());)
		D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
int  X[N],  Y[N], Z[N];
LL ans;

int main() {
	memset(tr,0x3f,sizeof tr);
	int x, y, z;
	n = read(), m = read();
	for(int i=1;i<=m;++i) {
		x = read(), y = read(), z = read();
		if(x > y) swap(x,y); 
		add(x,y,z); add(y,x,z);
		X[i] = x, Y[i] = y, Z[i] = z;
	}
	s = read(), t = read();
	if(s == t) {
		cin >> q;
		for(int i=1;i<=q;++i) puts("0");
		return 0;
	}
	dij1();
//	for(int i=1;i<=n;++i) cout << f[i] << " "; puts(""); return 0;
	for(int i=t;i;i=from1[i]) stack[++top] = i;
	for(int i=top;i;--i) pos[stack[i]] = top - i + 1;
	for(int i=top;i>1;--i) {
		x = stack[i], y = stack[i-1];
		if(x > y) swap(x,y);
		relable[mp(x,y)] = top - i + 1;
	}
	dij3();
	dij2();
	for(int i=1;i<=m;++i) {
		if(relable.find(mp(X[i],Y[i])) != relable.end()) continue;
		x = pos[from2[X[i]]];
		y = pos[from3[Y[i]]] - 1;
		if(x <= y) change(1,1,top-1,x,y,f[X[i]]+g[Y[i]]+Z[i]);
		swap(X[i], Y[i]);
		x = pos[from2[X[i]]];
		y = pos[from3[Y[i]]] - 1;
		if(x <= y) change(1,1,top-1,x,y,f[X[i]]+g[Y[i]]+Z[i]);
	}
	q = read();
	for(int i=1;i<=q;++i) {
		x = read(), y = read();
		if(x > y) swap(x,y);
		if(relable.find(mp(x,y)) == relable.end()) ans = f[t];
		else ans = ask(1,1,top-1,relable[mp(x,y)]);
		if(ans == 0x3f3f3f3f3f3f3f3fll) puts("Infinity");
		else printf("%lld\n", ans);
	}
}

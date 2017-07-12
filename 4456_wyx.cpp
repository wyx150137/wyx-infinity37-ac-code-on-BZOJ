
#include <queue>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define fir first
#define sec second
#define mp make_pair
#define pb push_back
#define in(x,a,b) ((x)>=(a)&&(x)<=(b))
const int N = 4e4+5;
const int M = N << 1;
const int inf = 0x7fffffff;

  
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
  
int n, m;

vector <int> id[N];

struct graph {
	graph *next; int to,val;
}edge[M], *head[N], *C = edge;
/*
struct graph {
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];*/

inline void add(int x,int y,int z) {
	C ++; C -> to = y; C -> val = z; C -> next = head[x]; head[x] = C;
	C ++; C -> to = x; C -> val = z; C -> next = head[y]; head[y] = C;
}
/*
inline void add(int x,int y,int z) {
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z); head[x] = cnt;
	edge[++cnt] = graph(head[y],x,z); head[y] = cnt;
}
*/
namespace Heap
{
    int h[N<<1],tot;
    int pos[N<<1];
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
    inline void push(int x,int y)
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

using namespace Heap;

int dis[N], X[N], Y[N];
bool vis[N];

inline void dij (int s,int x1,int x2,int y1,int y2) {
	for(int i=x1;i<=x2;++i)
		for(int j=y1;j<=y2;++j) 
			dis[id[i][j]] = inf;
	for(int i=x1;i<=x2;++i)
		for(int j=y1;j<=y2;++j)
			vis[id[i][j]] = false;
	push(0,s); dis[s] = 0;
	static graph *p;
	static int To;
	while(!empty()) {
		int tt = pop();
		if(vis[tt]) continue;
		vis[tt] = 1;/*
		for(int i=head[tt];i;i=edge[i].next) {
			if(in(X[edge[i].to],x1,x2) && in(Y[edge[i].to],y1,y2)) {
				if(dis[edge[i].to] > dis[tt] + edge[i].val && !vis[edge[i].to]) {
					dis[edge[i].to] = dis[tt] + edge[i].val;
					push(dis[edge[i].to],edge[i].to);
				}
			}
		}*/
		for(p=head[tt];p;p=p->next) {
			if(in(X[(To = p->to)],x1,x2) && in(Y[To],y1,y2)) {
				if(dis[To] > dis[tt] + p->val && !vis[To]) {
					dis[To] = dis[tt] + p->val;
					push(dis[To],To);
				}
			}
		}
	}
}

int ans[N*10];

struct data {
	int x0,y0,x1,y1, u, v, id;
}ask[N*10], tmp[N*10];

inline void solve(int x1,int x2,int y1,int y2,int L,int R) {
	if(L > R) return;
	bool flag = false;
	int l, r;
	if(x2 - x1 < y2 - y1) l = y1, r = y2, flag = 1;
	else l = x1, r = x2, flag = 0;
	int mid = (l+r) >> 1;
	if(flag) {
		for(int i=x1;i<=x2;++i) {
			dij(id[i][mid],x1,x2,y1,y2);
			for(int j=L;j<=R;++j) {
				ans[ask[j].id] = min(ans[ask[j].id], dis[ask[j].u] + dis[ask[j].v]);
			}
		}
	}
	else {
		for(int i=y1;i<=y2;++i) {
			dij(id[mid][i],x1,x2,y1,y2);
			for(int j=L;j<=R;++j) {
				ans[ask[j].id] = min(ans[ask[j].id], dis[ask[j].u] + dis[ask[j].v]);
			}
		}
	}
	int tmpl = L - 1, tmpr = R + 1;
	for(int i=L;i<=R;++i)  {
		if(flag) {
			if(ask[i].y0 < mid && ask[i].y1 < mid) tmp[++tmpl] = ask[i];
			else if(ask[i].y0 > mid && ask[i].y1 > mid) tmp[--tmpr] = ask[i];
		} 
		else {
			if(ask[i].x0 < mid && ask[i].x1 < mid) tmp[++tmpl] = ask[i];
			else if(ask[i].x0 > mid && ask[i].x1 > mid) tmp[--tmpr] = ask[i];
		}
	}
	for(int i=L;i<=tmpl;++i) ask[i] = tmp[i];
	for(int i=tmpr;i<=R;++i) ask[i] = tmp[i];
	if(flag) solve(x1,x2,y1,mid-1,L,tmpl), solve(x1,x2,mid+1,y2,tmpr,R);
	else solve(x1,mid-1,y1,y2,L,tmpl), solve(mid+1,x2,y1,y2,tmpr,R);
}

int main() {
//	freopen("02.in","r",stdin);
//	freopen("02.out","w",stdout);
	n = read(), m = read();
	for(int i=1;i<=n;++i) id[i].pb(0);
	int cnt = 0;	
	for(int i=1;i<=n;++i) {
		for(int j=1;j<=m;++j) {
			id[i].pb(++cnt);
			X[cnt] = i, Y[cnt] = j;
		}
	}
	for(int i=1;i<=n;++i) {
		for(int j=1;j<m;++j) {
			add(id[i][j],id[i][j+1],read());
		}
	}
	for(int i=1;i<n;++i)
		for(int j=1;j<=m;++j) {
			add(id[i][j],id[i+1][j],read());
		}
	int  T = read();
	for(int i=1;i<=T;++i) {
		ask[i].id = i;
		ask[i].x0 = read(), ask[i].y0 = read(), ask[i].x1 = read(), ask[i].y1 = read();
		ask[i].u = id[ask[i].x0][ask[i].y0];  ask[i].v = id[ask[i].x1][ask[i].y1];
		if(ask[i].u == ask[i].v) ans[i] = 0;
		else ans[i] = inf;
	}
//	puts("yes");
	solve(1,n,1,m,1,T);
	for(int i=1;i<=T;++i) printf("%d\n", ans[i]);
}

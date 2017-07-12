
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 2000000;
const int M = 2000000;
const int inf = 1e9;
using namespace std;

int hash[N];

int tr[M];
int head[N];

char getc()
{
    static const int LEN = 1<<15	;
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

 /*   inline int read()
    {
    	int x = 0, f = 1; char ch = getchar();
    	while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    	while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    	return x * f;
    }*/


struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

int in[M],MIN[M];

inline void add(int x,int y,int z)
{
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y,z);
	in[y] ++;
	head[x] = cnt;
}

int cnt;

void build(int k,int l,int r)
{
	tr[k] = ++cnt;
	if(l==r){hash[l] = cnt;return;}
	int mid = (l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	add(tr[k],tr[k<<1],0);
	add(tr[k],tr[k<<1|1],0);
}

struct data
{
	int k,l,r,x,y;
	data () {}
	data (int _k,int _l,int _r,int _x,int _y)
	:k(_k),l(_l),r(_r),x(_x),y(_y){}
	void out()
	{
		cout << l << " " << r << " " << x << " " << y << " " << k <<endl;
	}
};

void ask(int k,int l,int r,int x,int y)
{
	static data stack[1000];
	static int top = 0;
	int tmpl,tmpr,tmpk,tmpx,tmpy;
	stack[++top] = data(k,l,r,x,y);
//	cout << k << endl;
	while(top)
	{
		data tmp = stack[top--];
//		tmp.out();
		tmpl = tmp.l,tmpr = tmp.r,tmpk = tmp.k,tmpx = tmp.x , tmpy = tmp.y;
		if(tmpl != tmpx || tmpr != tmpy)
		{
			int mid = (tmpl+tmpr) >> 1;
			if(tmpy<=mid)stack[++top] = data(tmpk<<1,tmpl,mid,tmpx,tmpy);
			else if(tmpx>mid)
				stack[++top] = data(tmpk<<1|1,mid+1,tmpr,tmpx,tmpy);
			else 
				stack[++top] = data(tmpk<<1,tmpl,mid,tmpx,mid),stack[++top] = data(tmpk<<1|1,mid+1,tmpr,mid+1,tmpy);
		}
		else add(cnt,tr[tmpk],1);
	}
	/*
	if(l==x && r==y){add(cnt,tr[k],1);return;}
	int mid = (l+r)>>1;
	if(y <= mid)ask(k<<1,l,mid,x,y);
	else if(x > mid)ask(k<<1|1,mid+1,r,x,y);
	else ask(k<<1,l,mid,x,mid),ask(k<<1|1,mid+1,r,mid+1,y);*/
}

queue <int> q;

int a[N];

int main()
{
	register int i,j;
	int n = read(),s = read(), m = read();
	build(1,1,n);
	for(i=1;i<=s;++i)
	{
		int tmp1 = read(),tmp2 = read();
		a[tmp1] = tmp2;
		MIN[hash[tmp1]] = tmp2;
	}
	for(i=1;i<=m;++i)
	{
		++cnt;
		int l = read(),r = read(),k = read();
		int lastL = l - 1,lastR = r + 1;
		int pos;
		for(j=1;j<=k;++j)
		{
			pos = read();
			add(hash[pos],cnt,0);
			if(pos - lastL > 1)
				ask(1,1,n,lastL+1,pos-1);
			lastL = pos;
		}
		if(lastR - lastL > 1)
			ask(1,1,n,lastL + 1, lastR - 1);
	}

	for(i=1;i<=cnt;++i)
	{
		if(!MIN[i]) MIN[i] = inf;
		if(!in[i]) q.push(i);
	}

	while(!q.empty())
	{
		int tt = q.front();q.pop();
		for(i=head[tt];i;i=edge[i].next)
		{
			MIN[edge[i].to] = min(MIN[edge[i].to],MIN[tt] - edge[i].val);
			if(!--in[edge[i].to])
				q.push(edge[i].to);
		}
	}

	bool flag = 0;

	for(i=1;i<=cnt;++i)
		if(in[i])
			flag = 1;

	for(i=1;i<=n;++i)
		if(MIN[hash[i]] < 1)
			flag = 1;
	for(i=1;i<=n;++i)
		if(a[i] > MIN[hash[i]])
			flag = 1;
	if(flag)
		puts("NIE");
	else
	{
		puts("TAK");
		for(i=1;i<n;++i)
			printf("%d ",MIN[hash[i]]);
		cout << MIN[hash[n]] << endl;
	}

}


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N=20005;
const int M=2005;
#define lowbit(x) ((x)&(-x))

struct node {
	int a,id;
}A[N];

struct Node{
	int a,b,c,id,No;
}p[N<<2],q[N<<2];

int n,m,tot;
int Q;
int h[N],tr[N];
int ans[M];


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

bool cmp2(const node &a,const node &b){
	return a.a < b.a;
}

bool cmp(const Node &a,const Node &b){
	return a.a ^ b.a ? a.a < b.a : a.b < b.b;
}

void updata(int x,int val){
	while(x < N){
		tr[x] += val;
		x += lowbit(x);
	}
}

int ask(int x){
	int ans = 0;
	while(x) {
		ans += tr[x];
		x -= lowbit(x);
	}
	return ans;
}

void add(int x,int y,int z,int Q){
	p[++tot].id = tot;
	p[tot].No = Q; p[tot].a = x;
	p[tot].b = y; p[tot].c = z;
}

void solve(int l,int r)
{
	if(l==r) return;
	int mid = (l+r) >> 1;
	for(int i=l;i<=r;++i){
		if(p[i].id <= mid) updata(p[i].b,p[i].c);
		else ans[p[i].No] += p[i].c * (ask(N) - ask(p[i].b));
	}
	for(int i=l;i<=r;++i) if(p[i].id <= mid) updata(p[i].b,-p[i].c);
	for(int i=r;i>=l;--i){
		if(p[i].id <= mid) updata(p[i].b,p[i].c);
		if(p[i].id > mid) ans[p[i].No] += p[i].c * ask(p[i].b-1);
	}
	for(int i=l;i<=r;++i) if(p[i].id <= mid) updata(p[i].b,-p[i].c);
	int L = l, R = mid + 1;
	for(int i=l;i<=r;++i)  if(p[i].id <= mid) q[L++] = p[i]; else q[R++] = p[i];
	for(int i=l;i<=r;++i) p[i] = q[i];
	solve(l,mid); solve(mid+1,r);
}
int main()
{
	n = read();
	for(int i=1;i<=n;++i) A[i].a = read(), A[i].id = i;
	sort(A+1,A+n+1,cmp2);
	int k = 1; h[A[1].id] = 1;
	for(int i=2;i<=n;++i){
		if(A[i].a != A[i-1].a) k ++;
		h[A[i].id] = k;
	}
	for(int i=1;i<=n;++i) p[++tot].id = tot, p[tot].a = i, p[tot].b = h[i], p[tot].c = 1;
	int m = read();
	for(int i=1;i<=m;i++)
	{
		int x = read(), y = read();
		add(x,h[x],-1,++Q);
		add(y,h[y],-1,Q);
		add(x,h[y],1,Q);
		add(y,h[x],1,Q);
		swap(h[x],h[y]);
	}
	sort(p+1,p+tot+1,cmp);
	solve(1,tot); printf("%d\n",ans[0]);
	for(int i=1;i<=m;i++)  ans[i]+=ans[i-1],printf("%d\n",ans[i]);
	return 0;
}

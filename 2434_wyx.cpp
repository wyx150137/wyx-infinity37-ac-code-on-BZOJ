
#include <queue>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#define lowbit(x) ((x)&(-x))
const int N = 1e5+5;
const int M = N << 1;
using namespace std;
int head[N];
int ch[N][26],fail[N],cnt[N],fa[N];

struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y){
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y); head[x] = cnt;
	edge[++cnt] = graph(head[y],x); head[y] = cnt;
}

int in[N],out[N];

inline void DFS(int x,int fa){
	static int dfn = 0;
	in[x] = ++dfn;
	for(int i=head[x];i;i=edge[i].next)
		if(edge[i].to != fa)
			DFS(edge[i].to,x);
	out[x] = dfn;
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int ans[N];

struct Q{
	int x,y;
	int id;
	inline bool operator < (const Q &z)const{
		return y < z.y;
	}
}a[N];

int root;

int sz;
int pos[N],num;

void build(char *str){
	int p = root;
	for(int i=0;str[i];++i)if(str[i] >= 'a' && str[i] <= 'z'){
		if(!ch[p][str[i]-'a']) ch[p][str[i]-'a'] = ++sz;
		fa[ch[p][str[i]-'a']] = p; p = ch[p][str[i]-'a'];
	}
	else if(str[i] == 'B') p = fa[p];
	else pos[++num] = p;
}

queue <int> q;

void get(){
	for(int i=0;i<26;++i)
		if(ch[root][i]){
			add(root,ch[root][i]);
			fail[ch[root][i]] = root;
			q.push(ch[root][i]);
		}
	while(!q.empty()){
		int tt = q.front(); q.pop();
		for(int i=0;i<26;++i){
			if(!ch[tt][i])
				ch[tt][i] = ch[fail[tt]][i];
			else{
				int p = ch[tt][i];
				fail[p] = ch[fail[tt]][i];
				add(p,fail[p]);
				q.push(p);
			}
		}
	}
}

int tr[N];

inline void change(int x,int val){
	while(x < N){
		tr[x] += val;
		x += lowbit(x);
	}
}

int ask(int x){
	int ans = 0;
	while(x){
		ans += tr[x];
		x -= lowbit(x);
	}
	return ans;
}

char str[N];

int main(){ //freopen("03.in","r",stdin);
	scanf("%s",str);
	build(str); get(); DFS(0,0);
	int n = read();
	for(int i=1;i<=n;++i) a[i].x = read(), a[i].y = read(), a[i].id = i;
	sort(a+1,a+n+1);
	int p = root,k = 1, cnt = 0;
	for(int i=0;str[i];++i){
		if(str[i] >= 'a' && str[i] <= 'z'){
			p = ch[p][str[i]-'a'];
			change(in[p],1);
		}
		else if(str[i]=='B'){
			change(in[p],-1);
			p = fa[p];
		}
		else if(str[i] == 'P'){
			++cnt;
			if(cnt == a[k].y)
				for(int j=k;a[j].y == cnt;++j,++k)
					ans[a[j].id] = ask(out[pos[a[j].x]]) - ask(in[pos[a[j].x]]-1);
		}
	}
	for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
}   

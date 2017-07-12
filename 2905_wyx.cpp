
#include <queue>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 300000+5;
const int M = N << 3;
using namespace std;
queue <int> q;
int ch[N][26],cnt,fail[N],in[N],out[N];

struct Graph{
	int cnt;
	int head[N];
	struct graph{
		int next,to;
		graph () {}
		graph (int _next,int _to)
		:next(_next),to(_to){}
	}edge[M];

	inline void add(int x,int y){
		edge[++cnt] = graph(head[x],y); head[x] = cnt;
	}
}w,g;

int root;

void insert(char *str,int y){
	int p = root;
	register int i = 0;
	for(i=0;str[i];++i){
		if(!ch[p][str[i]-'a'])
			ch[p][str[i]-'a'] = ++cnt;
		w.add(y,(p=ch[p][str[i]-'a']));
	}
}

int dfn;

void DFS(int x){
	in[x] = ++dfn;
	for(int i=g.head[x];i;i=g.edge[i].next) DFS(i);
	out[x] = dfn;
}

void build(){
	register int i;
	for(i=0;i<26;++i) if(ch[root][i]) q.push(ch[root][i]);
	while(!q.empty()){
		int tt = q.front(); q.pop();
		for(i=0;i<26;++i)
			if(!ch[tt][i]) ch[tt][i] = ch[fail[tt]][i];
			else fail[ch[tt][i]] = ch[fail[tt]][i],q.push(ch[tt][i]);
	}
}

int tr[M],lazy[M];

inline void cover(int k,int val){
	tr[k] = max(tr[k],val);
	lazy[k] = max(lazy[k],val);
}

inline void down(int k,int l,int r){
	if(l==r || !lazy[k]) return;
	int tmp = lazy[k]; lazy[k] = 0;
	cover(k<<1,tmp); cover(k<<1|1,tmp);
}

inline void change(int k,int l,int r,int x,int y,int val){
	if(x <= l  && r <= y) {
		cover(k,val);
		return ;
	}
	down(k,l,r);
	int mid = (l+r) >> 1;
	if(x <= mid) change(k<<1,l,mid,x,y,val);
	if(y > mid) change(k<<1|1,mid+1,r,x,y,val);
}

inline int ask(int k,int l,int r,int pos){
	if(l==r)return tr[k];
	int mid = (l+r) >> 1;
	down(k,l,r);
	if(pos <= mid)return ask(k<<1,l,mid,pos);
	else return ask(k<<1|1,mid+1,r,pos);
}

char str[N];
int val[N],F[N];

void init(){
	memset(tr,0,sizeof tr);
	memset(ch,0,sizeof ch);
	memset(lazy,0,sizeof lazy);
	memset(w.head,0,sizeof w.head);
	memset(g.head,0,sizeof g.head);
	memset(fail,0,sizeof fail);
	w.cnt = g.cnt = cnt = dfn = 0;
}

int main(){ 
//	freopen("51book.in","r",stdin); //freopen("51book.out","w",stdout);
	int cases ; cin >> cases; while(cases--){
		int i,j;
		init(); int n; cin >> n;
		for(i=1;i<=n;++i){
			scanf("%s%d",str,&val[i]);
			insert(str,i);
		}
		build();
		fail[0] = -1;
//		for(i=1;i<=cnt;++i) g.add(fail[i],i);
		for(i=1;i<=cnt;++i) g.edge[i].next = g.head[fail[i]], g.head[fail[i]] = i;
//		for(i=1;i<=cnt;++i) cout << fail[i] << " ";
		DFS(0);
//		for(i=1;i<=dfn;++i) cout << in[i] << " ";
		int ans = 0;
		for(i=1;i<=n;++i){
			F[i] = 0;
			for(j=w.head[i];j;j=w.edge[j].next)
				F[i] = max(F[i],ask(1,1,dfn,in[w.edge[j].to]));
			F[i] += val[i];
//			cout << w.head[i] << " ";
			change(1,1,dfn,in[w.edge[w.head[i]].to],out[w.edge[w.head[i]].to],F[i]);
			ans = max(ans,F[i]);
		}
		cout << ans << endl;
	}
}

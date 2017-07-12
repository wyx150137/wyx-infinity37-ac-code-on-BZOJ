
#include <map>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 200010+5;
const int M = N ;
#define lowbit(x) ((x)&(-x))
using namespace std;

int n,m;

struct Graph{
	int head[N];
	struct  graph {
		int next,to;
		graph () {}
		graph (int _next,int _to)
		:next(_next),to(_to){}
	}edge[M];

	inline void add(int x,int y){
		static int cnt = 0;
		edge[++cnt] = graph(head[x],y); head[x] = cnt;
	}
}w,g;

char str[N<<1];
int depth[N],fa[N];
int root,last,cnt;

inline int newnode(int _){
	depth[++cnt] = _;
	return cnt;
}

map <char,int>son[N];
int in[N],out[N],seq[N];
int dfn;

void DFS(int x){
	in[x] = ++ dfn;
	seq[dfn] = x;
	for(int j=g.head[x];j;j=g.edge[j].next)
		DFS(g.edge[j].to);
	out[x] = dfn;
}

int pre[10000+5];

struct Ask{
	int times;
	int l,r;
	Ask () {}
	Ask (int _,int __,int ___)
	:times(_),l(__),r(___){}
	bool operator < (const Ask&z)const{
		return r < z.r;
	}
}ask[60000+5];

int tr[N];

void updata(int x,int val){
	while(x <= cnt){
		tr[x] += val;
		x += lowbit(x);
	}
}


int get(int x){
	int ans = 0;
	while(x){
		ans += tr[x];
		x -= lowbit(x);
	}
	return ans;
}

int lastins[10000+5],ans[60000+5];

int main(){
	cin >> n >> m;
	register int i, j, k;
	int p,np,q,nq,tmp,last;
	root = newnode(0);
	for(i = 1; i <= n; ++i){
		scanf("%s",str);
		for(last = root,j = 0; str[j]; ++j){
			if((q = son[last][str[j]])!=0)
			{
				if(depth[q] == depth[last]+1) last = q;
				else
				{
					nq = newnode(depth[last]+1);
					fa[nq] = fa[q]; fa[q] = nq; son[nq] = son[q];
					for(tmp=last;tmp&&son[tmp][str[j]]==q;tmp = fa[tmp]) son[tmp][str[j]] = nq;
					last = nq;
				}
			}
			else
			{
				p = last; np = newnode(depth[p]+1); 
				while(p && !son[p][str[j]]) son[p][str[j]] = np, p = fa[p];
				if(!p) fa[np] = root;
				else {
					q = son[p][str[j]];
					if(depth[q] == depth[p] + 1) fa[np] = q;
					else{
						nq = newnode(depth[p]+1);
						fa[nq] = fa[q];
						fa[q] = nq;
						fa[np] = nq;
						son[nq] = son[q];
						while(p && son[p][str[j]] == q) son[p][str[j]] = nq, p = fa[p];
					}
				}
				last = np;
			}
			w.add(last,i);
		}
	}
	for(i=1;i<=cnt;++i) if(fa[i]) g.add(fa[i],i);
	DFS(root);
	bool flag;
	for(int i=1;i<=m;++i){
		scanf("%s",str);
		flag = true;
		for(p=root,j=0;str[j];++j)
			if(!son[p][str[j]]){
				flag = false;
				break;
			}
			else p = son[p][str[j]];
		if(flag) ask[i] = Ask(i,in[p],out[p]);
		else ask[i] = Ask(i,-1,-1);
	}
	sort(ask+1,ask+m+1);
	int tt; k = 1;
	while(k <= m && ask[k].l == -1) k ++;
	for(i=1;i<=cnt;++i){
		for(j=w.head[seq[i]];j;j=w.edge[j].next){
			tt = w.edge[j].to;
			updata(i,1);
			if(lastins[tt]) updata(lastins[tt],-1);
			lastins[tt] = i;
		}
		while(ask[k].r == i){
			ans[ask[k].times] = get(ask[k].r) - get(ask[k].l-1);
			k ++;
		}
	}
	for(int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
}	


#include <bits/stdc++.h>
using namespace std;
#define N 1000100
using namespace std;
int n,cnt, a[N], du[N], head[N], vis[N], v[N], fir[N];
struct node {
		int from,to,next;
}edge[N<<1];

int belong[N], cnt_du[N], siz[N], tot;

inline void init() {
		memset(head,-1,sizeof(head));
		cnt=1;
}

inline void edgeadd(int from,int to) {
		edge[cnt].from=from,edge[cnt].to=to,edge[cnt].next=head[from];
		head[from]=cnt++;
}

void dfs(int now,int ff) {
		vis[now]=1,belong[now]=tot,siz[tot]++;
		for(int i=head[now];i!=-1;i=edge[i].next) {
				int to=edge[i].to;
				if(to==now||to==ff||vis[to])continue;
				dfs(to,now);
		}
}

inline bool check(int now,int num) {
		v[now]=1;
		int t=now,cntt=1;
		while(!v[a[t]]) {
				v[a[t]]=1;
				t=a[t];
				cntt++;
		}
		t=a[t];
		if(t==now&&cntt==num) return 1;
		return 0;
}

int main() {
		init();
		scanf("%d",&n);
		for(int i=1;i<=n;i++) {
				scanf("%d",&a[i]);
				du[a[i]]++;
				edgeadd(i,a[i]);
				edgeadd(a[i],i);
		}
		for(int i=1;i<=n;i++) if(!vis[i]) tot++,dfs(i,0),fir[tot]=i;
		for(int i=1;i<=n;i++) if(du[i]==0)cnt_du[belong[i]]++;
		int ansma=0,ansmi=0;
		for(int i=1;i<=tot;i++) {
				if(siz[i]==1)ansma++;
				if(check(fir[i],siz[i])) ansma+=siz[i]-1;
				else ansma+=siz[i]-cnt_du[i];
		}
		memset(v,0,sizeof(v));
		memset(vis,0,sizeof(vis));
		queue<int>q;
		for(int i=1;i<=n;i++) if(!du[i]) q.push(i);
		while(!q.empty()) {
				int u=q.front(); q.pop(); v[u]=1;
				if(!vis[a[u]]) {
						v[a[u]]=vis[a[u]]=1,ansmi++;
						du[a[a[u]]]--;
						if(!du[a[a[u]]]) q.push(a[a[u]]);
				}
		}
		for(int i=1;i<=n;i++) {
				if(!v[i]) {
						int t=i,cnt=0;
						while(!v[t]) {
								v[t]=1;
								cnt++;
								t=a[t];
						}
						ansmi+=(cnt+1)/2;
				}
		}
		printf("%d %d\n",ansmi,ansma);
}

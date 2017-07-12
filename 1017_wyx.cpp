
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
const int inf = 0x7fffff;
const int N = 50+5;
const int M = N << 1;
using namespace std;

int head[N];

struct graph
{
	int next,to,val;
	graph () {}
	graph (int _next,int _to,int _val)
	:next(_next),to(_to),val(_val){}
}edge[M];

int in[N];

inline void add(int x,int y,int z){
	static int cnt = 0;in[y] ++;
	edge[++cnt] = graph(head[x],y,z);
	head[x] = cnt;
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
} 

int p[N],n,m;
int cost[N],lmt[N];
int f[N][105][2000+5];
int tmp[105][2000+5];

void DFS(int x){
	if(!head[x]){
		lmt[x] = min(lmt[x],m/cost[x]);
		for(int i=0;i<=lmt[x];++i)
			for(int j=i;j<=lmt[x];++j)
				f[x][i][j*cost[x]] = (j-i)*p[x];
		return;
	}
	lmt[x] = inf;
	for(int i=head[x];i;i=edge[i].next){
		DFS(edge[i].to);
		lmt[x] = min(lmt[x],lmt[edge[i].to]/edge[i].val);
		cost[x] += edge[i].val * cost[edge[i].to];
	}
	lmt[x] = min(lmt[x],m/cost[x]);
	memset(tmp,-0x3f3f3f3f,sizeof tmp);tmp[0][0] = 0;
	for(int l = lmt[x];~l;--l){
		int tot = 0;
		for(int i=head[x];i;i=edge[i].next){
			++tot;
			for(int j=0;j<=m;++j)
				for(int k=0;k<=j;++k)
					tmp[tot][j] = max(tmp[tot][j],tmp[tot-1][j-k]+f[edge[i].to][l*edge[i].val][k]);
		} 
		for(int j=0;j<=l;++j)
			for(int k=0;k<=m;++k)
				f[x][j][k] = max(f[x][j][k],tmp[tot][k]+p[x]*(l-j));
	}	
}

int main()
{
//	freopen("06.in","r",stdin);
	memset(f,-0x3f3f3f3f,sizeof f);
	n = read(),m = read();
	char str[10];
	for(int i=1;i<=n;++i){
		p[i] = read();
		scanf("%s",str);
		if(str[0]=='A'){
			int c = read();
			for(int j=1;j<=c;++j){
				int t = read(),num = read();
				add(i,t,num);
			}
		}	
		else cost[i] = read(),lmt[i] = read();

	}

	int ans = 0;
	for(int i=1;i<=n;++i)
		if(!in[i])
		{
			DFS(i);
			for(int j=0;j<=m;++j)
				for(int k=0;k<=lmt[i];++k)
					ans = max(ans,f[i][k][j]);
		}
	cout << ans << endl;
}

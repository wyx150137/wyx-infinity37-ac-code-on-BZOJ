
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 2000+5;
const int M = N << 2;
int n,m;
int head[N];
struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

int Cnt = 0;

inline void add(int x,int y){
	edge[++Cnt] = graph(head[x],y);
	head[x] = Cnt;
}

int cnt = 0 ,scc, dfn[N],low[N],stack[N],top;
int belong[N];
bool in[N];
char str1[5],str2[N];

void DFS(int x){
	dfn[x] = low[x] = ++cnt;
	in[x] = 1; stack[++top] = x;
	for(int i=head[x];i;i=edge[i].next)
		if(!dfn[edge[i].to]){
			DFS(edge[i].to);
			low[x] = min(low[x],low[edge[i].to]);
		}
		else if(in[edge[i].to])
			low[x] = min(low[x],dfn[edge[i].to]);
	if(low[x] == dfn[x]){
		int now = 0;
		scc ++;
		while(now  ^ x){
			now = stack[top--];
			belong[now] = scc;
			in[now] = false;
		}
	}
}

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int main(){
	int T = read();
	while(T--){
		n = read(), m = read();
		cnt = top = Cnt = scc = 0;
		memset(head,0,sizeof head);
		memset(belong,0,sizeof belong);
		for(int i=1;i<=m;++i){
			int tmp1,tmp2,x,y;
		//	scanf("%c%d%c%d",&str1[0],&tmp1,&str2[0],&tmp2);
			cin >> str1[0]; tmp1 = read();
			cin >> str2[0]; tmp2 = read();
			if(str1[0] == 'h') tmp1 = (tmp1 << 1)- 1;
			else tmp1 <<= 1;
			if(str2[0] == 'h') tmp2 = (tmp2 << 1)- 1;
			else tmp2 <<= 1;
			if(tmp1 %2 == 0)x = tmp1 - 1;
			else x = tmp1 + 1;
			if(tmp2 % 2== 0)y = tmp2 - 1;
			else y = tmp2 + 1;
			add(x,tmp2); add(y,tmp1);
		}
		memset(low,0,sizeof low);
		memset(dfn,0,sizeof dfn);
		for(int i=1;i<=2*n;++i) if(!dfn[i]) DFS(i);
		bool flag = true;
		for(int i=1;i<=n;++i)
			if(belong[(i<<1)-1] == belong[i<<1])
				flag = false;
		if(!flag) puts("BAD");
		else puts("GOOD");		
                                                                                                           	}
}

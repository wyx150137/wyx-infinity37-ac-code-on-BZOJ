
#include <stdio.h>
#include <string.h>
#include <algorithm>
const int N = 5000+5;
const int M = N << 1;
using namespace std;

int head[N];

struct graph{
	int next,to;
	graph () {}
	graph (int _next,int _to)
	:next(_next),to(_to){}
}edge[M];

inline void add(int x,int y){
	static int cnt = 0;
	edge[++cnt] = graph(head[x],y);
	head[x] = cnt;
}

int change[N],in[N],out[N];

inline int read(){
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}

int col[N],n;

void Col(int x){
	col[x] = 1;
	for(int i=head[x];i;i=edge[i].next)
		if(!col[edge[i].to]) Col(edge[i].to);
}

bool check(int x){
	memset(col,0,sizeof col);
	Col(x);
	for(int i=1;i<=n;++i)
		if(col[in[i]]&&col[out[i]])
			return false;
	return true;
}

char str1[5],str2[N];
int ans[N];

int main(){
	n = read();
	int m = read();
	for(int i=1;i<=n;++i) in[i] = i, out[i] = i + n ,change[i] = i + n, change[i+n]	= i;
	int x,y;
	for(int i=1;i<=m;++i){
		scanf("%d%s%d%s",&x,str1,&y,str2);
		x = str1[0] == 'Y' ? in[x] : out[x];
		y = str2[0] == 'Y' ? in[y] : out[y];
		add(change[x],y);
		add(change[y],x);
	}
	bool flag1,flag2;
	for(int i=1;i<=n;++i){
		flag1 = check(in[i]), flag2 = check(out[i]);
		if(!flag1 && !flag2) return puts("IMPOSSIBLE"),0;
		else if(!(flag1&&flag2)) ans[i] = flag1 ? 1 : 2;
	}
	char tmp[]="?YN";
	for(int i=1;i<=n;++i)
		putchar(tmp[ans[i]]);
	puts("");
}

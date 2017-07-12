
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 5e5+5;
const int M = N << 1;

inline int read() {
    int x=0,f=1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
    while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
    return x*f;
}

 
struct graph {
    int next,to;
    graph () {}
    graph (int _next,int _to)
    :next(_next),to(_to){}
}edge[M];

int head[N], n, K, size[N];

double F[N];
 
inline void add(int x,int y) {
    static int cnt = 0; edge[++cnt] = graph(head[x],y); head[x] = cnt;
}
 
void DFS(int x) {
    size[x] = 1;
    bool flag = false;
    for(int i=head[x];i;i=edge[i].next) 
        DFS(edge[i].to), size[x] += size[edge[i].to], flag = true;
    if(!flag) {
        F[x] = 1; return ;
    }
    for(int i=head[x];i;i=edge[i].next) 
        F[x] = max(F[x],min(F[edge[i].to],(double)size[edge[i].to]/(double)(size[x]-1)));
}

int main () {
    n = read(), K = read(); 
    for(int i=2;i<=n;++i) add(read(),i);
    DFS(1);
    double ans = 0;
    for(int i=1;i<=n;++i) 
        if(size[i] > K) 
            ans = max(ans,F[i]);
    printf("%.7lf\n",ans);
}

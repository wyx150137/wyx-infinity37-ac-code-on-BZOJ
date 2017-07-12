
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 505;
//int map[N][N][4];
struct E{int to,next,val;}e[N*N*9];
int head[N*N],tot,cnt,st,end,n;
struct H{int v;long long p;}P[N*N*4];
void go_up(int x)
{
	int i = x;
	while((i>>1)>=1&&P[i].v<P[i>>1].v)
	{
		swap(P[i],P[i>>1]);
		i = i>>1;
	}
}
int getnum(int i,int j){return (i-1)*n+j;}
bool cmp(H a,H b){return a.v>b.v;}
void go_down(int x)
{
	int i = x;
	while(((i<<1)|1)<=cnt)
	{
		if(P[i].v>P[i<<1].v&&P[i].v>P[(i<<1)|1].v)
		{
			swap(P[i],P[i<<1].v>P[(i<<1)|1].v?P[(i<<1)|1]:P[i<<1]);
			i = P[i<<1].v>P[(i<<1)|1].v?((i<<1)|1):(i<<1);
		}else if(P[i].v>P[i<<1].v)
		{
			swap(P[i],P[i<<1]);
			i = i<<1;
		}
		else if(P[i].v>P[i<<1|1].v)
		{
			swap(P[i],P[i<<1|1]);
			i = i<<1|1;
		}
		else break;
	}
	if((i<<1)<=cnt&&P[i<<1].v<P[i].v)
		swap(P[i],P[i<<1]);
}
void insert(int per,long long lth)
{
	H tmp;
	tmp.v = lth;tmp.p = per;
	P[++cnt] = tmp;
	go_up(cnt);
}
int pop()
{
	int tmp = P[1].p;
	swap(P[1],P[cnt]);
	cnt--;
	go_down(1);
	return tmp;
}
long long f[N*N];
bool in[N*N];
void dijk()
{
	memset(f,0x3f,sizeof(f));
	f[st] = 0;
	P[1].v = 0,P[1].p = st;
	cnt++;
	//insert(st,0);
	while(cnt)
	{
		int x = P[1].p;
		pop_heap(P+1,P+cnt+1,cmp);
		cnt--;
		if(in[x])continue;
		in[x] = true;
		for(int i = head[x];i;i = e[i].next)
		{
			int y = e[i].to;
			if(f[x]+e[i].val<f[y])
			{
				f[y] = f[x]+e[i].val;
				cnt++;
				P[cnt].p = y;P[cnt].v = f[y];
				push_heap(P+1,P+cnt+1,cmp);
				//insert(y,f[y]);
			}
		}
	}
	return ;
}
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val = f;
	head[x] = tot;
}
void show_edge(int x)
{
    for(int i = head[x];i;i = e[i].next)
        printf("%d %d:%d\n",x,e[i].to,e[i].val);
}
int main()
{
	scanf("%d",&n);
	int a;
	st = n*n+1,end = n*n+2;
    for(int i=1;i<=n;i++){scanf("%d",&a);add(st,getnum(1,i),a);}
    for(int i=1;i<n;i++)
        for(int j=1;j<=n;j++) 
            {scanf("%d",&a);add(getnum(i,j),getnum(i+1,j),a);}
    for(int i=1;i<=n;i++)
        {scanf("%d",&a);add(getnum(n,i),end,a);}
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        add(getnum(i,1),end,a);
        for(int j=2;j<=n;j++) {scanf("%d",&a);add(getnum(i,j),getnum(i,j-1),a);}
        scanf("%d",&a);
    	add(st,getnum(i,n),a);
    }
    for(int i=1;i<=n;i++) scanf("%d",&a);
    for(int i=1;i<n;i++)
        for(int j=1;j<=n;j++) 
        	{scanf("%d",&a);add(getnum(i+1,j),getnum(i,j),a);}
    for(int i=1;i<=n;i++) scanf("%d",&a);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        for(int j=2;j<=n;j++){scanf("%d",&a);add(getnum(i,j-1),getnum(i,j),a);}
        scanf("%d",&a);
    }
	dijk();
	printf("%lld\n",f[end]);
	return 0;
}

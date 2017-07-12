
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const unsigned ll inf = ~0ull;
using namespace std;


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
const int N = 200000+5;
const int M = 8000005;

int n,m,K,cnt;
int val[N],b[N],rt[N];
int sum[M],a[M][2];
unsigned ll H[N];
void insert(int x,int &y,unsigned ll val)
{
	y=++cnt;int tmp=y;
	sum[y]=sum[x]+1;
	unsigned ll l=0,r=inf,mid;
	while(l!=r)
	{
		mid=l/2+r/2;
		if((l&1)&&(r&1))mid++;
		int t=0;
		if(val>mid)t=1,l=mid+1;
		else r=mid-1;
		a[y][t]=++cnt;
		a[y][t^1]=a[x][t^1];
		x=a[x][t];y=a[y][t];sum[y]=sum[x]+1;
	}
	y=tmp;
}
bool query(int x,int y,unsigned ll val)
{
	unsigned ll l=0,r=inf,mid;
	while(l!=r)
	{
		mid=l/2+r/2;
		if((l&1)&&(r&1))mid++;
		int t=0;
		if(val>mid)t=1,l=mid+1;
		else r=mid-1;
		x=a[x][t];y=a[y][t];
	}
	return (sum[y]-sum[x])!=0;
}
int main()
{
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++)val[i]=read();
	for(int i=1;i<=n;i++)H[i]=H[i-1]*107+val[i];
	unsigned ll M=1;for(int i=1;i<=K;i++)M*=107;
	for(int i=K;i<=n;i++)
		insert(rt[i-1],rt[i],H[i]-H[i-K]*M);
	while(m--)
	{
		int x=read(),y=read();
		for(int i=1;i<=K;i++)b[i]=read();
		unsigned ll now=0;
		for(int i=1;i<=K;i++)now=now*107+b[i];
		if(query(rt[x+K-2],rt[y],now))puts("No");
		else puts("Yes");
	}		
	return 0;
}

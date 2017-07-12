
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
const int N = 1e6+5;
const int M = N << 1;
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

int fa[N],size[N],stack[N],from[M],to[M];

int find(int x)
{
	static int top = 0;
	while(fa[x]!=x)
	{
		stack[++top] = x;
		x = fa[x];
	}
	while(top)
		fa[stack[top--]] = x;
	return x;
}
/*
inline int read()
{
	int x=0,f=1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f=-1;ch = getchar();}
	while(ch >='0' && ch <='9'){x=(x<<1)+(x<<3)+ch-'0';ch = getchar();}
	return x*f;
}*/

void Union(int x,int y)
{
	int fx = find(x),fy = find(y);
	if(fx == fy) return;
	if(size[fx] < size[fy]) swap(fx,fy);
	fa[fy] = fx,size[fx] += size[fy];
}

int main()
{


	int n = read(), m = read(), k = read(),cnt = 0;
	register int i;
	for(i=1;i<=n;++i) size[fa[i]=i] = 1;
	for(i=1;i<=m;++i)
	{
		int x = read(),y = read();
		if(x<=k || y<=k)
			from[++cnt] = x , to[cnt] = y;
		else Union(x,y);
	}
	int ans = 0;
	for(i=1;i<=cnt;++i){
		int fx = find(from[i]),fy = find(to[i]);
		if(fx == fy) ans ++;
		else{
			if(size[fx] < size[fy]) swap(fx,fy);
			fa[fy] = fx,size[fx] += size[fy];
		}
	}
	cout << ans << endl;
}

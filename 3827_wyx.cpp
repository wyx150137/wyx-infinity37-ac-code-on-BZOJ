
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000001;
const int inf = 2147483647;
#define min(a,b) ((a)<(b) ? (a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
int l[N],next[N<<1],depth[N<<1],n,s,d;

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

int calc(int x)
{
	register int fa = x, now = x;
	while(fa - x < n)
		fa = next[fa];
	int k ;
	while(now - x < n)
	{
		k = next[now];
		next[now] = fa;
		now = k;
	}
	return depth[x] - depth[now];
}

int MIN = 0;

int main()
{
	n = read(), s = read();
	for(int i=1;i<=n;++i)
		l[i] = read(),MIN = max(MIN,l[i]);
	while(s--)
	{
		d = read();
		if(d < MIN)
		{
			puts("NIE");
			continue;
		}
		int sum = 0;
		register int j = 1, i = 1;
		int tmp = n << 1;
		for(i = 1; i <= tmp; ++i)
		{
			while( j < tmp && sum + l[(j>n) ? j-n : j] <= d)
				sum = sum + l[j>n ? (j-n) : j],j ++;
			next[i] = j;
			sum -= l[i>n ? (i-n) : i];
		}
		j = inf,depth[tmp] = 0;
		for(i = tmp;i >= 1; --i)
			depth[i] = depth[next[i]] + 1;
		for(i = 1;i <= n; ++i)
			j = min(j,calc(i));
		printf("%d\n",j);
	}
}

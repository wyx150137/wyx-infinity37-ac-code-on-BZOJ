
#include <stdio.h>
#include <cctype>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 1000005;
struct E
{int next,to;}e[N<<1];
int head[N],tot;
int d[N];
void add(int x,int y)
{
	d[x]++;
	e[++tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}
LL low[N],upn[N],a[N],maxa;
bool v[N];
queue<int>Q;
void bfs(int x)
{
	v[x] = true;
	Q.push(x);
	while(!Q.empty())
	{
		int x = Q.front();
		Q.pop();
		for(int i = head[x];i;i = e[i].next)
			if(!v[e[i].to])
			{
				Q.push(e[i].to);
				v[e[i].to] = true;
				if(low[x]*(d[x]-1)>maxa)low[e[i].to] = maxa+1;
				else low[e[i].to] = low[x]*(d[x]-1);
				if(upn[x]*(d[x]-1)+d[x]-2>maxa)upn[e[i].to] = maxa+1;
				else upn[e[i].to] = upn[x]*(d[x]-1)+d[x]-2;
			}
	}
}
char getc()
{
	static const int LEN = 4096;
	static char buf[LEN],*S=buf,*T=buf;
	if(S == T)
	{
		T = (S=buf)+fread(buf,1,LEN,stdin);
		if(S == T)return EOF;
	}
	return *S++;
}
LL read()
{
	static char ch;
	static LL D;
	while(!isdigit(ch=getc()));
	for(D=ch-'0'; isdigit(ch=getc());)
		D=(D<<3)+(D<<1)+(ch-'0');
	return D;
}
int main()
{
	int n,g,k;
	n = read(),g = read(),k =read();
	for(int i = 1;i<= g;i++)
	{
		a[i] = read();
		maxa = max(maxa,a[i]);
	}
	int s,t,x,y;
	for(int i = 1;i<n;i++)
	{
		x = read();y = read();
		add(x,y),add(y,x);
		if(i==1)s = x,t = y;
	}
	v[s] = v[t] = true;
	low[s] = low[t] = upn[s] = upn[t] = k;
	bfs(s);bfs(t);
	sort(a+1,a+g+1);
	LL ans = 0;
	for(int i = 1;i<= n;i++)
		if(d[i]==1)
		{
			int l = lower_bound(a+1,a+g+1,low[i])-a;
			int r = upper_bound(a+1,a+g+1,upn[i])-a;
			if(r>g||a[r]>upn[i])r--;
			ans+=(r-l+1);
		}
	printf("%lld\n",ans*k);
	return 0;
}

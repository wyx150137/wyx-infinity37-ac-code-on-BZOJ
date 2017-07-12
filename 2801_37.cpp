
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int N = 500005;
const int M = 3000005;
char BB[1<<15],*K=BB,*T=BB;
#define getc() (K==T&&(T=(K=BB)+fread(BB,1,1<<15,stdin),K==T)?0:*K++)
inline long long read()
{
    long long x=0;char ch=getc();
    while(ch<'0'||ch>'9')ch=getc();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getc();
    return x;
}
struct F
{
	LL k,c;
	F()
	{k = c = 0;}
	void operator -=(const F &S)
	{k-=S.k;c-=S.c;}
}f[N];
struct E
{int next,to,val;}e[M<<1];
int head[N],tot;
LL p[N];
void add(int x,int y,int f)
{
	e[++tot].to = y;
	e[tot].next = head[x];
	e[tot].val  = f;
	head[x] = tot;
}
bool v[N];
LL l,r;
LL O,V,X;
int line[N],h,t;
int dfs(int s)
{
	O = V= 0;
	h = 0,t = -1;
	l = 0,r = p[s];
	line[++t] = s;
	v[s] = true;
	f[s].k = 1,f[s].c = 0;
	while(h<=t)
	{
		int x = line[h++];
		O-=f[x].k,V+=p[x]-f[x].c;
		for(int i = head[x];i;i = e[i].next)
		{
			int j = e[i].to;
			if(!v[j])
			{
				line[++t] = j;
				v[j] = true;
				f[j].k = -f[x].k;
				f[j].c = e[i].val-f[x].c;
				if(f[e[i].to].k==1)
				{
					r=min(r,p[j]-f[j].c);
					l=max(l,-f[j].c);
				}
				else
				{
					r=min(r,f[j].c);
					l=max(l,f[j].c-p[j]);
				}
				if(r<l)return -1;
			}else
			{
				if(f[j].k==f[x].k)
				{
					X = f[j].c+f[x].c-e[i].val;
					if(X%2!=0)return -1;
					r = min(r,(e[i].val-f[x].c-f[e[i].to].c)/2/f[x].k);
					l = max(l,(e[i].val-f[x].c-f[e[i].to].c)/2/f[x].k);
					if(r<l)return -1;
				}else
				{
					if(e[i].val!=f[x].c+f[j].c)
						return -1;
				}
			}
		}
	}
	return 0;
}
int main()
{
	//freopen("bez.in","r",stdin);
	//freopen("bez.out","w",stdout);
	long long n,m,x,y,z;
	n = read(),m = read();
	for(int i = 1;i<= n;i++)
		p[i] = read();
	for(int i = 1;i<= m;i++)
	{
		x = read(),y = read(),z = read();
		add(x,y,z),add(y,x,z);
	}
	LL minn = 0,maxn = 0;
	for(int i = 1;i<= n;i++)
	{
		if(!v[i])
		{
			int tmp = dfs(i);
			if(tmp==-1){printf("NIE\n");return 0;}
			else if(O>0)
				minn+=l*O+V,maxn+=r*O+V;
			else minn+=r*O+V,maxn+=l*O+V;
		}
	}
	printf("%lld %lld\n",minn,maxn);
	return 0;
}

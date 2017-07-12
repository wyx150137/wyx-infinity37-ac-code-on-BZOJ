
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 1e5+5;
const int M = N*64;
struct data
{
	int t,i,f;
	data(int _t=0,int _i=0,int _f=0):t(_t),i(_i),f(_f){}
	bool operator <(const data &s)const
	{
		return t<s.t;
	}
}s[N<<1];
int ans[N];
struct Trie
{
	int lazy,s,f;
	int ch[2];
}tr[M];
void Push_down(int p)
{
	int ls = tr[p].ch[0],rs = tr[p].ch[1];
	if(tr[p].lazy)
	{
		if(!tr[ls].f)
		{
			tr[ls].lazy+=tr[p].lazy;
			tr[ls].s+=tr[p].lazy;
		}
		if(!tr[rs].f)
		{
			tr[rs].lazy+=tr[p].lazy;
			tr[rs].s+=tr[p].lazy;
		}
		tr[p].lazy = 0;
	}
}
char opt[N][10],str[N][35];
char ip[N][35];
int l[N],r[N],top=1;
void Update(int now)
{
	int kind = 1;
	if(opt[now][0]=='D')kind = -1;
	int l = strlen(str[now]+1);
	int j = 1;
	for(int i = 1;i<= l;i++)
	{
		if(!tr[j].ch[0])tr[j].ch[0] = ++top;
		if(!tr[j].ch[1])tr[j].ch[1] = ++top;
		Push_down(j);
		j = tr[j].ch[str[now][i]-'0'];
	}
	tr[j].lazy++,tr[j].s++,tr[j].f+=kind;
}
int Getans(int now)
{
	int j = 1;
	for(int i = 1;i<= 32;i++)
	{
		if(!tr[j].ch[0])tr[j].ch[0]=++top;
		if(!tr[j].ch[1])tr[j].ch[1]=++top;
		Push_down(j);
		j = tr[j].ch[ip[now][i]-'0'];
	}
	return tr[j].s;
}
int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i = 1;i<= n;i++)
		scanf("%s%s",opt[i],str[i]+1);
	for(int i = 1;i<= q;i++)
	{
		scanf("%s%d%d",ip[i]+1,&l[i],&r[i]);
		s[(i<<1)-1] = data(l[i],i,-1);
		s[i<<1] = data(r[i],i,1);
	}
	sort(s+1,s+q*2+1);
	int j = 1;
	for(int i = 1;i<= 2*q;i++)
	{
		while(j<=s[i].t)
		{
			Update(j);
			j++;
		}
		ans[s[i].i]+=s[i].f*Getans(s[i].i);
	}
	for(int i = 1;i<= q;i++)
		printf("%d\n",ans[i]);
	return 0;
}

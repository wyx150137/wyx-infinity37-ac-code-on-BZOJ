
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 2300000+5;
char s[N];
int trs[N][2],len[N],fa[N];
int cnt,last,maxlen;
void insert(int x)
{
	int p = last;
	if(trs[p][x])
	{
		int q = trs[p][x];
		if(len[q]==len[p]+1)last = q;
		else
		{
			int nq = ++cnt;
			last = nq;
			fa[nq] = fa[q];len[nq]=len[p]+1;
			memcpy(trs[nq],trs[q],sizeof(trs[q]));
			fa[q] = nq;
			for(;p&&trs[p][x]==q;p=fa[p])trs[p][x] = nq;
		}
	}else
	{
		int np = ++cnt,q,nq;
		last = np;len[np] = len[p]+1;
		for(;p&&!trs[p][x];p=fa[p])trs[p][x]=np;
		if(!p)fa[np]=1;
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)fa[np] = q;
			else
			{
				fa[nq=++cnt]=fa[q];
				len[nq]=len[p]+1;
				memcpy(trs[nq],trs[q],sizeof(trs[q]));
				fa[np] = fa[q] = nq;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x]=nq;
			}
		}
	}
}
int mtc[N];
void match(int n)
{
	int tmp = 0,p = 1;
	for(int i = 1;i<= n;i++)
	{
		int x = s[i]-'0';
		if(trs[p][x])p=trs[p][x],tmp++;
		else
		{
			while(p&&!trs[p][x])p=fa[p];
			if(!p)tmp = 0,p=1;
			else tmp = len[p]+1,p = trs[p][x];
		}
		mtc[i] = tmp;
	}
}
int Q[N],H,T,f[N],tmp[N];
bool check(int x,int n)
{
	f[0] = 0;
	H = 0,T = -1;
	//for(int i=1;i<=n;i++)tmp[i]=i-mtc[i];
	for(int i = 1;i<= n;i++)
	{
		f[i] = f[i-1];
		int p = i-x;  
        while(p>=0&&H<=T&&f[p]-p>f[Q[H]]-Q[H])
        	H++;
		if(p>=0)Q[++T] = p;
        while(H<=T&&i-mtc[i]>Q[H])H++;  
        if(H<=T)f[i] = max(f[i], f[Q[H]]+i-Q[H]);
	}
	return f[n]*10>=n*9;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	cnt = 1;
	for(int i = 1;i<= m;i++)
	{
		last = 1;
		scanf("%s",s+1);int lth = strlen(s+1);
		maxlen = max(maxlen,lth);
		for(int j = 1;j<= lth;j++)
			insert(s[j]-'0');
	}
	while(n--)
	{
		scanf("%s",s+1);
		int lth = strlen(s+1);
		match(lth);
		int l = 0,r = lth,ans=0;
		while(l<=r)
		{
			int mid = (l+r)>>1;
			if(check(mid,lth))l=mid+1,ans = mid;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}

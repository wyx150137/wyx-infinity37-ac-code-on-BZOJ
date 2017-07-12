
#include <stdio.h>
#include <queue>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+500;
char s[N];
int size[N<<1],pos[205];
queue<int>q;
struct SAM
{
	int trs[N<<1][27],fa[N<<1],len[N<<1],ind[N<<1],size[N<<1];
	int cnt,last;
	int end[N<<1];
	void init(){cnt=last=1;}
	int insert(int x)
	{
		int p = last,np = ++cnt,q,nq;
		last = np,len[np]=len[p]+1;
		size[np]++;
		for(;p&&!trs[p][x];p=fa[p])trs[p][x]=np;
		if(!p)fa[np]=1;
		else
		{
			q = trs[p][x];
			if(len[q]==len[p]+1)fa[np]=q;
			else
			{
				fa[nq=++cnt]=fa[q];
				len[nq]=len[p]+1;
				memcpy(trs[nq],trs[q],sizeof(trs[q]));
				fa[np] = fa[q] = nq;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x]=nq;
			}
		}
		return np;
	}
	void build()
	{
		for(int i=1;i<=cnt;i++)ind[fa[i]]++;
		for(int i=1;i<=cnt;i++)
			if(!ind[i])q.push(i);
		while(!q.empty())
		{
			int t=q.front();q.pop();
			if((--ind[fa[t]])==0)q.push(fa[t]);
			size[fa[t]]+=size[t];
		}
	}
}sam;
int beg[205],lth[205];
int main()
{
	int n,ll=0;
	sam.init();
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s+ll+1);
		beg[i] = ll+1;
		ll+=(lth[i]=strlen(s+ll+1));
		s[++ll]='a'-1;
	}
	for(int i=1;i<=ll;i++)
        sam.insert(s[i]-'a'+1);
    sam.build();
	for(int i=1;i<=n;i++)
    {
        int now=1;
        for(int j=beg[i];j<=beg[i]+lth[i]-1;j++)
            now=sam.trs[now][s[j]-'a'+1];
        printf("%d\n",sam.size[now]);
    }
	return 0;
}

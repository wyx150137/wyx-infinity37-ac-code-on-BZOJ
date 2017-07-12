
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 3e5+5;
int ch[N][26],tot=1;
char s[N];
vector<int>end[N];
void insert(int no)
{
	int i = strlen(s+1),p = 1;
	while(i)
	{
		if(!ch[p][s[i]-'a'])ch[p][s[i]-'a'] = ++tot;
		p = ch[p][s[i]-'a'];
		i--;
	}
	end[p].push_back(no);
}
int ls[N*20],rs[N*20],root[N],sum[N*20],cnt;
int a[N],in[N],out[N],Dfn;
void dfs(int x)
{
	int num = Dfn;
	for(int i= 0;i<end[x].size();i++)a[++Dfn] = end[x][i];
	for(int i = 0;i<26;i++)
		if(ch[x][i])
			dfs(ch[x][i]);
	for(int i = 0;i<end[x].size();i++)
		in[end[x][i]] = num,out[end[x][i]] = Dfn;
}
void update(int &p,int pre,int l,int r,int pos)
{
	p = ++cnt;
	if(l==r)
	{
		sum[p] = sum[pre]+1;
		return ;
	}
	ls[p] = ls[pre],rs[p] = rs[pre];
	int mid = (l+r)>>1;
	if(pos<=mid)update(ls[p],ls[pre],l,mid,pos);
	else update(rs[p],rs[pre],mid+1,r,pos);
	sum[p] = sum[ls[p]]+sum[rs[p]];
}
int getans(int x,int y,int l,int r,int k)
{
	int mid = (l+r)>>1;
	if(l==r)return l;
	if(sum[y]-sum[x]<k)return -1;
	if(sum[ls[y]]-sum[ls[x]]>=k)return getans(ls[x],ls[y],l,mid,k);
	else return getans(rs[x],rs[y],mid+1,r,k-sum[ls[y]]+sum[ls[x]]);
}
int main()
{
	int n,k;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%s",s+1);
		insert(i);
	}
	dfs(1);
	root[0]=ls[0]=rs[0]=sum[0]=0;
	for(int i = 1;i<= n;i++)
		update(root[i],root[i-1],1,n,a[i]);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&k);
		printf("%d\n",getans(root[in[i]],root[out[i]],1,n,k));
	}
	return 0;
}

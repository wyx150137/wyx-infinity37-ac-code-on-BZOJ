
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 600005;
const int INF = 0x3f3f3f3f;
struct Trie
{
	int cnt;
	int s[N*24][2],sum[N*24];
	int insert(int x,int val)
	{
		int tmp,y;tmp=y=++cnt;
		for(int i = 23;i>=0;i--)
		{
			s[y][0] = s[x][0];
			s[y][1] = s[x][1];
			sum[y]= sum[x]+1;
			int t = val&(1<<i);t = t>>i;
			x=s[x][t];
			s[y][t] = ++cnt;
			y = s[y][t];
		}
		sum[y]=sum[x]+1;
		return tmp;
	}
	int getans(int l,int r,int val)
	{
		int ans = 0;
		for(int i = 23;i>= 0;i--)
		{
			int t = val&(1<<i);t = t>>i;
			if(sum[s[r][t^1]]-sum[s[l][t^1]])
				ans+=(1<<i),r = s[r][t^1],l = s[l][t^1];
			else r = s[r][t],l = s[l][t];
		}
		return ans;
	}
}trie;
int a[N],b[N],root[N];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);n++;
	for(int i = 2;i<= n;i++)scanf("%d",&a[i]);
	for(int i = 1;i<= n;i++)b[i] = b[i-1]^a[i];
	for(int i = 1;i<= n;i++)
		root[i]=trie.insert(root[i-1],b[i]);
	char opt[3];
	int l,r,x;
	for(int i = 1;i<= m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='A')
		{
			n++;
			scanf("%d",&a[n]);
			b[n] = b[n-1]^a[n];
			root[n] = trie.insert(root[n-1],b[n]);
		}else
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",trie.getans(root[l-1],root[r],b[n]^x));
		}
	}
	return 0;
}

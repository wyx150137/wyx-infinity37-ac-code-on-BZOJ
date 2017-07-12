
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 4e5+5;
const int M = 35*N;
struct Trie
{
	int ch[M][2],sum[M];
	int cnt;
	int insert(int x,int num)
	{
		int tmp,y;
		tmp=y=++cnt;
		for(int i = 30;i>=0;i--)
		{
			int t = num&(1<<i);t = t>>i;
			ch[y][0]=ch[x][0],ch[y][1]=ch[x][1];
			x = ch[x][t];
			y = ch[y][t]=++cnt;
			sum[y] = sum[x]+1;
		}
		return tmp;
	}
	int getans(int l,int r,int val)
	{
		int ans = 0;
		for(int i = 30;i>= 0;i--)
		{
			int t = val&(1<<i);t=t>>i;
			if(sum[ch[r][t^1]]-sum[ch[l][t^1]]>0)
				l=ch[l][t^1],r=ch[r][t^1],ans+=(1<<i);
			else l = ch[l][t],r=ch[r][t];
		}
		return ans;
	} 
}trie;
int z[N],y[N],a[N],root[N];
int main()
{
	int n;
	scanf("%d",&n);
	n++;
	a[1] = 0;
	for(int i = 2;i<= n;i++)
	{
		scanf("%d",&a[i]);
		a[i] = a[i-1]^a[i];
	}
	for(int i = 1;i<= n;i++)
		root[i] = trie.insert(root[i-1],a[i]);
	for(int i = 2;i<=n;i++)
	{
		z[i] = trie.getans(root[0],root[i],a[i]);
		y[i] = trie.getans(root[i-1],root[n],a[i]);
	}
	for(int i = 1;i<= n;i++)z[i] = max(z[i],z[i-1]);
	for(int i = n;i>= 1;i--)y[i] = max(y[i],y[i+1]);
	int ans = 0;
	for(int i = 2;i<=n;i++)
		ans = max(ans,z[i]+y[i]);
	printf("%d\n",ans);
	return 0;
}

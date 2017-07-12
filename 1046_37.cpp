
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 10005;
const int M = 1005;
int f[N],c[N],pos[N],a[N],cnt,n,m;
int find(int x)
{
	int l = 1,r = cnt+1;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(pos[mid]<x)l = mid+1;
		else r =mid;
	}
	return l;
}
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i] = max(c[i],y);
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans = max(ans,c[i]);
	return ans;
}
int t_ans = 0;
void pre()
{
	for(int i = n;i>=1;i--)
	{
		int tmp = find(a[i]);
		tmp = n-tmp+1;
		f[i] = getans(tmp-1)+1;
		update(tmp,f[i]);
		t_ans = max(t_ans,f[i]);
	}
}
void solve(int x)
{
	int last = 0;
	for(int i = 1;i<= n;i++)
		if(f[i]>=x&&a[i]>last)
		{
			printf("%d",a[i]);
			if(x!=1)printf(" ");
			last = a[i];
			x--;
			if(!x)break;
		}
	printf("\n");
}
int main()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		scanf("%d",&a[i]);
		pos[i] = a[i];
	}
	sort(pos+1,pos+n+1);
	for(int i = 1;i<= n;i++)
		if(pos[i]!=pos[cnt])
			pos[++cnt] = pos[i];
	pre();
	scanf("%d",&m);
	int x;
	for(int i = 1;i<= m;i++)
	{
		scanf("%d",&x);
		if(x>t_ans)printf("Impossible\n");
		else solve(x);
	}
	return 0;
}

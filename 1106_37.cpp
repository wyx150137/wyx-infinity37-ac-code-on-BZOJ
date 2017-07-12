
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 100005;
int c[N],mark[N];
void update(int x,int y)
{
	for(int i = x;i<N;i+=i&(-i))
		c[i]+=y;
}
int getans(int x)
{
	int ans = 0;
	for(int i = x;i>0;i-=i&(-i))
		ans+=c[i];
	return ans;
}
int main()
{
	int n,x,ans = 0;
	scanf("%d",&n);
	for(int i = 1;i<= 2*n;i++)
	{
		scanf("%d",&x);
		if(mark[x])
		{
			ans += getans(i-1)-getans(mark[x]);
			update(mark[x],-1);
		}else
		{
			mark[x] = i;
			update(i,1);
		}
	}
	printf("%d\n",ans);
	return 0;
}

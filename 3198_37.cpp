
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

#define md 1234567
#define ll long long
#define inf (int) 1e9
#define eps 1e-8
#define N 1234590
#define cg 23333LL
#define M 500010
using namespace std;
int n;
int a[N][6],c[10][10];
ll ans[7];
bool same(int x,int y,int opt)
{
	for (int i=0;i<=5;i++) if ((opt&(1<<i))&&a[x][i]!=a[y][i]) return 0;
	return 1;
}
	
struct ha
{
	ll a[N];
	int q[N],is[N];
	int sz;
	ll clear()
	{
		ll ans=0;
		for (int i=1;i<=sz;i++)
		{
			int x=q[i];
			ans+=a[x]*(a[x]-1)/2;
			a[x]=is[x]=0;
		}
		sz=0;
		return ans;
	}
	void insert(int k,int x,int opt)
	{
		int pos=k;
		while (a[pos]&&(!same(x,is[pos],opt))) pos=(pos+1)%md; 
		if (!a[pos]) q[++sz]=pos,is[pos]=x;
		a[pos]++;
	}
} hash;

ll solve(int opt)
{
	for (int i=1;i<=n;i++)
	{
		ll ha=0;
		for (int j=0;j<=5;j++)
		{
			ha=ha*cg%md;
			if (opt&(1<<j)) { ha=(ha+a[i][j]+1)%md;}
		}
		hash.insert(ha,i,opt);
	}
	return hash.clear();
}
int cal(int i)
{
	int sum=0;
	for (int j=0;j<=5;j++) sum+=(i>>j)&1;
	return sum;
}
int main()
{
	int k;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		for(int j=0;j<=5;j++)
			scanf("%d",&a[i][j]);
	for (int i=0;i<=63;i++) ans[cal(i)]+=solve(i);
	c[0][0]=1;
	for (int i=1;i<=6;i++)
		for (int j=0;j<=i;j++)
			c[i][j]=c[i-1][j-1]+c[i-1][j];
	for (int i=6;i>=k;i--)
		for (int j=0;j<i;j++)
			ans[j]-=ans[i]*c[i][j];
	printf("%lld\n",ans[k]);
	return 0;
}

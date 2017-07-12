
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 2001;
const int mod = 1e9+7;
const int S = 1e7;
int gcd[N][N],pow[N][N],f[N][N],sum[N],b[N];
int g[S+5],tmp[S+5];
bool vis[S+5];
int prime[S/10],cnt,a[100005],n,K,p;
void Pre()
{
	sum[n] = 1;
	for(int i = 1;i<= n;i++)
	{
		for(int j = 1;j<= n;j++)
		{
			if(i==1||j==1)f[i][j] = 1;
			else if(i==j)f[i][j] = (f[i][j-1]+1)%mod;
			else if(i<j)f[i][j] = f[i][j-1];
			else f[i][j] = (f[i-j][j]+f[i][j-1])%mod;
		}
		sum[n-i]=f[i][i];
	}
	g[0] = 0,g[1] = 1;
	for(int i = 2;i<= S;i++)
	{
		if(!vis[i])
		{
			prime[++cnt]=tmp[i]=i;
			g[i] = 2*i-2;
		}
		for(int j = 1;j<= cnt&&i*prime[j]<=S;j++)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j])
			{
				tmp[i*prime[j]] = prime[j];
				g[i*prime[j]] = (ll)g[i]*g[prime[j]]%mod; 
			}else
			{
				tmp[i*prime[j]] = tmp[i]*prime[j];
				if(tmp[i]!=i)g[i*prime[j]] = (ll)g[i/tmp[i]]*g[tmp[i]*prime[j]]%mod;
				else g[i*prime[j]] = ((ll)g[i]*prime[j]+i*(prime[j]-1))%mod;
				break;
			}
		}
	}
	for(int i = 1;i<= n;i++)gcd[i][0]=gcd[0][i]=gcd[i][i]=i,gcd[i][1]=gcd[1][i]=1;
	for(int i = 2;i<= n;i++)
		for(int j = 2;j<= i;j++)
		{
			if(!gcd[i][j])gcd[i][j] = gcd[j][i-j];
			gcd[j][i] = gcd[i][j];
		}
	for(int i = 1;i<= n;i++)pow[i][0]=1,pow[i][1] = i;
	for(int i = 1;i<= n;i++)
		for(int j = 2;j<= n;j++)
			pow[i][j] = 1ll*pow[i][j-1]*i%K;
}
int F(int x,int y)
{
	if(p==1)return 1%K;
	if(p==2)return gcd[x][y]%K;
	if(p==3)return (pow[x][y]+pow[y][x]+(x^y))%K;
}
inline void add(int &x,const int &y)
{
	x+=y;
	if(x>=mod)x-=mod;
}
int Cnt[S+5];
int main()
{
	scanf("%d%d%d",&p,&n,&K);
	for(int i = 0;i<K;i++)scanf("%d",&a[i]);
	Pre();
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n-i;j++)
            for(int muli=1;muli*i+j<=n;muli++)
                for(int mulj=1;mulj*j+muli*i<=n;mulj++)
                    add(Cnt[F(i,j)],sum[muli*i+mulj*j]);
	int ans = 0;
    for(int i=0;i<K;i++) ans+=1LL*g[a[i]]*Cnt[i]%mod,ans%=mod;
    for(int i=1;i<=n;i++)
    {
        for(int muli=1;muli*i<=n;muli++)
        {
            int Tmp=1LL*muli*(muli-1)/2*(sum[muli*i]-sum[(muli+1)*i]+mod)%mod;
            add(ans,1LL*g[a[F(i,i)]]*Tmp%mod);
        }
    }
    printf("%d\n",ans);
	return 0;
}

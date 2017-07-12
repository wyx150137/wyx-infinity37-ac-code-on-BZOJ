
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
const int sed = 237;
const int N = 3e4+5;
int u[N],v[N];
char s[N];
int hash[N],pow[N];
void pre()
{
	pow[0]=1;
	for(int i =1;i<N;i++)
		pow[i]=(ll)pow[i-1]*sed%mod;
}
int Hash(int l,int r)
{
	return (hash[r]-(ll)hash[l]*pow[r-l]%mod+mod)%mod;
}
int main()
{
	int cas,p,q,l,r,mid;
	long long ans = 0;
	scanf("%d",&cas);
	pre();
	while(cas--)
	{
		scanf("%s",s+1);int n = strlen(s+1);
		for(int i = 1;i<= n;i++)
			u[i]=v[i]=0,hash[i] = ((ll)hash[i-1]*sed+s[i]-'a')%mod;
		for(int i = 1;2*i<= n;i++)
			for(int j = 1;j+i<= n;j+=i)
			{
				l = 0,r = min(i,j);
				while(l^r)
				{
					mid = (l+r+1)>>1;
					if(Hash(j+i-mid,j+i)==Hash(j-mid,j))l=mid;
					else r = mid-1;
				}
				p = j-l+1;
				l = 0,r = min(i-1,n-j-i);
				while(l^r)
				{
					mid = (l+r+1)>>1;
					if(Hash(j+i,j+i+mid)==Hash(j,j+mid))l=mid;
					else r = mid-1;
				}
				q = j+l+1;
				if(p+i<=q)
				{
					++u[p],--v[q+i];
					--u[q-i+1];++v[p+i*2-1];
				}
			}
		ans = 0;
		for(int i = 1;i<= n;i++)
			u[i]+=u[i-1],v[i]+=v[i-1],ans+=(ll)u[i]*v[i-1];
		printf("%lld\n",ans);
	}
	return 0;
}

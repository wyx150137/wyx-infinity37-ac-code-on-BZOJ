
#include <stdio.h>
#include <math.h>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
typedef long long ll;
struct Ask
{
	int l,r,lpos,id;
	bool operator <(const Ask &s)const
	{
		if(lpos==s.lpos)return r<s.r;
		return lpos<s.lpos;
	}
}ask[N];
ll s[N],cd[N],ba[N],Ans[N];
char str[N];
map<ll,ll>tt;
int main()
{
	ll p;
	int n,m;
	scanf("%lld",&p);
	scanf("%s",str+1);
	scanf("%d",&m);
	n = strlen(str+1);
	if(p!=2&&p!=5)
	{
		ll pow10 = 1;
		for(int i = n;i;i--)
		{
			pow10 = pow10*10%p;
			s[i] = (s[i+1]+(ll)(str[i]-'0')*pow10%p)%p;
			cd[i] = s[i];
		}
		sort(cd+1,cd+n+1);
		for(int i= 1;i<= n+1;i++)
			tt[cd[i]]=i;
		for(int i = 1;i<= n+1;i++)
			s[i] = tt[s[i]];
		int block = sqrt(n);
		for(int i = 1;i<= m;i++)
		{
			scanf("%d%d",&ask[i].l,&ask[i].r);
			ask[i].r++;
			ask[i].lpos = ask[i].l/block;
			ask[i].id = i;
		}
		sort(ask+1,ask+m+1);
		ll ans = 0;
		int l = 1,r = 0;
		for(int i = 1;i<= m;i++)
		{
			while(r<ask[i].r)ans+=ba[s[++r]]++;
			while(r>ask[i].r)ans-=--ba[s[r--]];
			while(l<ask[i].l)ans-=--ba[s[l++]];
			while(l>ask[i].l)ans+=ba[s[--l]]++;
			Ans[ask[i].id] = ans;
		}
		for(int i = 1;i<= m;i++)
			printf("%lld\n",Ans[i]);
	}else
	{
		for(int i = 1;i<= n;i++)
		{
			if(!((str[i]-'0')%p))
				ba[i] = ba[i-1]+1,cd[i] = cd[i-1]+i;
			else ba[i] = ba[i-1],cd[i] = cd[i-1];
		}
		for(int i = 1;i<= m;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",cd[r]-cd[l-1]-(ba[r]-ba[l-1])*(l-1));
		}
	}
	return 0;
}

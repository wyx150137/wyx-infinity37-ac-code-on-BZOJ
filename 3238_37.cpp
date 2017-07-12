
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 500005;
struct E{int next,to;};
char s[N];
ll ans;
struct SAM
{
	int trs[N<<1][26],fa[N<<1],len[N<<1],size[N<<1],f[N<<1],ct[N<<1],rnk[N<<1];
	int cnt,last;
	bool end[N<<1];
	void init(){cnt=last=1;}
	void insert(int x)
	{
		int p = last,np = ++cnt,q,nq;
		last = np,len[np] = len[p]+1;
		end[np] = true;
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
				fa[q] = fa[np] = nq;
				for(;p&&trs[p][x]==q;p=fa[p])trs[p][x]=nq;
			}
		}
	}
	void getans(int n)
	{
		ans=0;
		for(int i = 1;i<= cnt;i++)f[i]=size[i]=end[i];
		for(int i=1;i<=cnt;i++) ct[len[i]]++;
		for(int i=1;i<=n;i++) ct[i]+=ct[i-1];
		for(int i=1;i<=cnt;i++) rnk[ct[len[i]]--]=i;
		for(int i=cnt;i;i--) f[fa[rnk[i]]]+=f[rnk[i]];
		for(int i=1;i<=cnt;i++)
		{
			ans+=(ll)size[fa[i]]*f[i]*len[fa[i]];
			size[fa[i]]+=f[i];
		}
	}
}sam;
int main()
{
	scanf("%s",s+1);
	int n = strlen(s+1);
	sam.init();
	for(int i = n;i>0;i--)
		sam.insert(s[i]-'a');
	sam.getans(n);
	ans = -2*ans;
	for(int i = 1;i<= n;i++)ans+=(ll)(n-1)*i;
	printf("%lld\n",ans);
	return 0;
}

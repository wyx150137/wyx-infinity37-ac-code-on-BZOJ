
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e6+5;
struct E
{
	int pre,nxt;
	E(){}
	E(int _pre,int _nxt):pre(_pre),nxt(_nxt){}
}a[N],b[N];
bool cmp1(const E &x,const E &y)
{return x.pre<y.pre;}
bool cmp2(const E &x,const E &y)
{return x.nxt>y.nxt;}
int main()
{
	int n;
	int cnt1=0,cnt2 = 0;
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)
	{
		int pr,nx;
		scanf("%d%d",&pr,&nx);
		if(nx>pr)a[++cnt1] = E(pr,nx);
		else b[++cnt2] = E(pr,nx);
	}
	sort(a+1,a+cnt1+1,cmp1);
	sort(b+1,b+cnt2+1,cmp2);
	long long ans = 0,rem = 0;
	for(int i = 1;i<= cnt1;i++)
	{
		if(rem<1ll*a[i].pre)
		{
			ans+=a[i].pre-rem;
			rem = 0;
		}
		else rem-=a[i].pre;
		rem+=a[i].nxt;
	}
	for(int i = 1;i<= cnt2;i++)
	{
		if(rem<1ll*b[i].pre)
		{
			ans+=b[i].pre-rem;
			rem = 0;
		}
		else rem-=b[i].pre;
		rem+=b[i].nxt;
	}
	printf("%lld\n",ans);
	return 0;
}

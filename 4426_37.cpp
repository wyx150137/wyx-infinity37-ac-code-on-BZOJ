
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 210;
const int INF = 0x3f3f3f3f;
struct data
{
	int l,r;
	data(){}
	data(int _l,int _r):l(_l),r(_r){}
}s[N],q[2][N];
int cnt[2],ans = -INF;
bool cmp1(const data &a,const data &b)
{return a.l<b.l;}
bool cmp2(const data &a,const data &b)
{return a.r-a.l+1>b.r-b.l+1;}
int f[N][N],sum[N];
void solve(int now,int l,int r,int dl,int dr)
{
	int mid = (l+r)>>1,dmid = dl,maxn = ans;
	for(int i = min(dr,mid-1);i>=dl;i--)
	{
		if(q[0][i+1].r<=q[0][mid].l)break;
		int tmp = f[now-1][i]+q[0][i+1].r-q[0][mid].l;
		if(tmp>=maxn)maxn = tmp,dmid = i;
	}
	f[now][mid] = maxn;
	if(l<mid)solve(now,l,mid-1,dl,dmid);
	if(r>mid)solve(now,mid+1,r,dmid,dr);
}
int main()
{
	int n,p;
	scanf("%d%d",&n,&p);
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&s[i].l,&s[i].r);
	for(int i = 1;i<= n;i++)
	{
		int flag = 0;
		for(int j = 1;j<= n;j++)
			if(s[i].l<=s[j].l&&s[i].r>=s[j].r&&(s[i].l!=s[j].l||s[i].r!=s[j].r||i<j))
				flag = 1;
		q[flag][++cnt[flag]] = s[i];
	}
	sort(q[0]+1,q[0]+cnt[0]+1,cmp1);
	for(int i = 1;i<= cnt[0];i++)f[0][i]=-INF;
	for(int i = 1;i<= p;i++)f[i][0] = -INF;
	for(int i = 1;i<= p;i++)solve(i,1,cnt[0],0,cnt[0]);
	sort(q[1]+1,q[1]+cnt[1]+1,cmp2);
	for(int i = 1;i<= cnt[1];i++)sum[i] = sum[i-1]+q[1][i].r-q[1][i].l;
	for(int i = 1;i<= p;i++)
		if((p-i)<=cnt[1]&&f[i][cnt[0]]>=0)
			ans = max(ans,f[i][cnt[0]]+sum[p-i]);
	printf("%d\n",ans);
	return 0;
}

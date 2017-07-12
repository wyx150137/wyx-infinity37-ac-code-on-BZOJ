
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 5e4+5;
const int B = 500;
const int mod = 1e9+7;
int st[B],end[B],bel[N],n;
struct data
{
	int a,v;
	bool operator <(const data &s)const
	{
		if(a==s.a)return v<s.v;
		return a<s.a;
	}
}ord[B][B+5],num[N];
int sum[B][B+5];
ll tot_ans;
struct Bit_array
{
	int c[N];
	int getans(int x)
	{
		int ans = 0;
		for(int i = x;i;i-=i&(-i))
			(ans+=c[i])%=mod;
		return ans;
	}
	void update(int x,int y)
	{
		for(int i = x;i<N;i+=i&(-i))
			(c[i]+=y)%=mod;
	}
	int getans(int x,int y)
	{
		return (getans(y)-getans(x-1)+mod)%mod;
	}
}c1,c2;
int less_than(int x,int block)
{
	int l = 1,r = end[block]-st[block]+2;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(ord[block][mid].a<x)l = mid+1;
		else r = mid;
	}
	return l-1;
}
int bigger_than(int x,int block)
{
	int l = 1,r = end[block]-st[block]+2;
	while(l<r)
	{
		int mid = (l+r)>>1;
		if(ord[block][mid].a<=x)l = mid+1;
		else r = mid;
	}
	return l-1;
}
void rebuild(int i)
{
	for(int j = st[i];j<=end[i];j++)
			ord[i][j-st[i]+1] = num[j];
	sort(ord[i]+1,ord[i]+end[i]-st[i]+2);
	for(int k = 1;k<= end[i]-st[i]+1;k++)
		sum[i][k] = sum[i][k-1]+ord[i][k].v;
}
int main()
{
	int m;
	scanf("%d%d",&n,&m);
	int bsize = sqrt(0.7*n)+1;
	for(int i = 1;i<= n;i++)
		scanf("%d%d",&num[i].a,&num[i].v);
	for(int i = 1;i<= n;i++)
	{
		tot_ans+=(c2.getans(num[i].a+1,n)+(ll)c1.getans(num[i].a+1,n)*num[i].v%mod)%mod;
		tot_ans = (tot_ans%mod+mod)%mod;
		c1.update(num[i].a,1);
		c2.update(num[i].a,num[i].v);
	}
	int bnum = 0;
	for(int i = 1;i<= n;i+=bsize)
		st[++bnum]=i,end[bnum]=i+bsize-1;
	end[bnum] = n;
	int j;
	for(int i = 1;i<= bnum;i++)
	{
		for(j = st[i];j<=end[i];j++)
			ord[i][j-st[i]+1] = num[j],bel[j]=i;
		sort(ord[i]+1,ord[i]+end[i]-st[i]+2);
		for(int k = 1;k<= end[i]-st[i]+1;k++)
			sum[i][k] = sum[i][k-1]+ord[i][k].v;
	}
	int x,y;
	//scanf("%d",&m);
	while(m--)
	{
		scanf("%d%d",&x,&y);
		if(x>y)swap(x,y);
		int L = bel[x],R = bel[y];
		if(L==R)
		{
			for(int i = x+1;i< y;i++)
				if(num[i].a>num[x].a)
					tot_ans+=num[i].v+num[x].v;
				else if(num[i].a<num[x].a)
					tot_ans-=num[i].v+num[x].v;
			for(int i = x+1;i< y;i++)
				if(num[i].a<num[y].a)
					tot_ans+=num[i].v+num[y].v;
				else if(num[i].a>num[y].a)
					tot_ans-=num[i].v+num[y].v;
			if(num[x].a<num[y].a)tot_ans+=num[x].v+num[y].v;
			else if(num[x].a>num[y].a)tot_ans-=num[x].v+num[y].v;
			swap(num[x],num[y]);
			rebuild(L);
		}else
		{
			for(int i = x+1;i<=end[L];i++)
			{
				if(num[i].a>num[x].a)
					tot_ans+=num[i].v+num[x].v;
				else if(num[i].a<num[x].a)
					tot_ans-=num[i].v+num[x].v;

				if(num[i].a<num[y].a)
					tot_ans+=num[i].v+num[y].v;
				else if(num[i].a>num[y].a)
					tot_ans-=num[i].v+num[y].v;
				tot_ans = (tot_ans%mod+mod)%mod;
			}
			for(int i = st[R];i< y;i++)
			{
				if(num[i].a>num[x].a)
					tot_ans+=num[i].v+num[x].v;
				else if(num[i].a<num[x].a)
					tot_ans-=num[i].v+num[x].v;

				if(num[i].a<num[y].a)
					tot_ans+=num[i].v+num[y].v;
				else if(num[i].a>num[y].a)
					tot_ans-=num[i].v+num[y].v;
				tot_ans = (tot_ans%mod+mod)%mod;
			}
			for(int i = L+1;i<= R-1;i++)
			{
				int lx = less_than(num[x].a,i);
				int bx = bigger_than(num[x].a,i);
				int ly = less_than(num[y].a,i);
				int by = bigger_than(num[y].a,i);
				tot_ans-=sum[i][lx]+(ll)lx*num[x].v%mod;
				tot_ans+=sum[i][end[i]-st[i]+1]-sum[i][bx]+(ll)(end[i]-st[i]+1-bx)*num[x].v%mod;
				tot_ans+=sum[i][ly]+(ll)ly*num[y].v%mod;
				tot_ans-=sum[i][end[i]-st[i]+1]-sum[i][by]+(ll)(end[i]-st[i]+1-by)*num[y].v%mod;
				tot_ans = (tot_ans%mod+mod)%mod;
			}
			if(num[x].a<num[y].a)tot_ans+=num[x].v+num[y].v;
			else if(num[x].a>num[y].a)tot_ans-=num[x].v+num[y].v;
			swap(num[x],num[y]);
			rebuild(L),rebuild(R);
		}
		tot_ans = (tot_ans%mod+mod)%mod;
		printf("%lld\n",tot_ans);
	}
	return 0;
}


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mxs = 30005;
const int N = 1e5+5;
const int size = 1800;
const double PI = 3.14159265358979323;
int n;
struct cp
{
	double x,y;
	cp(double _x=0,double _y=0):x(_x),y(_y){}
	friend cp operator +(const cp &a,const cp &b)
	{
		return cp(a.x+b.x,a.y+b.y);
	}
	friend cp operator -(const cp &a,const cp &b)
	{
		return cp(a.x-b.x,a.y-b.y);
	}
	friend cp operator *(const cp &a,const cp &b)
	{
		return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
	}
}a[524299],b[524299];

int num[N],pos[N],L[N],R[N];
int st[N],end[N],tot,lim;
int cnt[400][60005];
int cnt_nxt[60005],cnt_pre[60005];
ll ans[N];

void FFT(cp *a,int len,int type)
{
	int t = 0;
	for(int i = 0;i<len;i++)
	{
		if(t<i)swap(a[t],a[i]);
		for(int j = len>>1;(t^=j)<j;j>>=1);
	}
	for(int i = 2;i<= len;i<<=1)
	{
		cp wn = cp(cos(PI*2*type/i),sin(PI*2*type/i));
		for(int j = 0;j<len;j+=i)
		{
			cp w(1,0),t;
			for(int k = 0;k<(i>>1);k++,w=w*wn)
			{
				t = a[j+k+(i>>1)]*w;
				a[j+k+(i>>1)] = a[j+k]-t;
				a[j+k] = a[j+k]+t;
			}
		}
	}	
	if(type==-1)
		for(int i = 0;i<len;i++)a[i].x/=len*4,a[i].y/=len;
}

void conv(int len)
{
	memset(a,0,sizeof(cp)*(len+1));
	memset(b,0,sizeof(cp)*(len+1));
	for(int i = 0;i<=lim;i++)a[i] = cp(L[i]+R[i],L[i]-R[i]);
	FFT(a,len,1);
	for(int i = 0;i<len;i++)b[i]=a[i]*a[i];
	FFT(b,len,-1);
	for(int i = 0;i<len;i++)ans[i] = (ll)(b[i].x+0.5);
}

void div_block()
{
	for(int i = 1;i<= n;i++)pos[i] = (i-1)/size+1;
	tot = pos[n];
	for(int i = 1;i<= tot;i++)st[i] = (i-1)*size+1,end[i] = i*size;
	end[tot] =n;
	for(int i = 1;i<= tot;i++)
		for(int j = st[i];j<=end[i];j++)
			cnt[i][num[j]]++;
}
int len;
void init()
{
	scanf("%d",&n);
	for(int i = 1;i<= n;i++)scanf("%d",&num[i]);
	for(int i = 1;i<= n;i++)lim=max(lim,num[i]);
	len = 1;
	for(;len<=2*lim;len<<=1);
}

ll res;
void calc(int p)
{
	int t = num[p]<<1;
	int cur = pos[p];
	for(int i = st[cur];i<p;i++)if(t>=num[i])res+=R[t-num[i]];
	for(int i = p+1;i<= end[cur];i++)
		if(t>=num[i])
		{
			res+=cnt_pre[t-num[i]];
			res+=L[t-num[i]];
			if (cur == 1) continue;
		}
	if (p <= end[1] || p >= st[tot]) return;
    res += ans[t];
}

void solve()
{
	for(int i = 1;i<= n;i++)R[num[i]]++;
	for(int i = 1;i<= tot;i++)
	{
		memset(cnt_pre,0,sizeof(int)*(lim+1));
		for(int j = st[i];j<=end[i];j++)cnt_nxt[num[j]]++;
		for(int j = 0;j<= lim;j++)R[j]-=cnt[i][j];
		if(i!=1&&i!=tot)conv(len);
		for(int j = st[i];j<= end[i];j++)
		{
			cnt_nxt[num[j]]--;
			calc(j);
			cnt_pre[num[j]]++;
		}
		for(int j = 0;j<= lim;j++)L[j]+=cnt[i][j];
		//printf("%lld\n",res);
	}
	printf("%lld\n",res);
}
int main()
{
	//freopen("3509.in","r",stdin);
	//freopen("3509.out","w",stdout);
	init();
	div_block();
	solve();
	return 0;
}

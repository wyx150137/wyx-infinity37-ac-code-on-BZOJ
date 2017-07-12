
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=200005;
int n;
int a[N],b[N];
int Q,x[N],y[N];
int sx[N],icnt;
inline int Bin(int x)
{
	return lower_bound(sx+1,sx+icnt+1,x)-sx;
}
const int BB=505;
int B,lp[BB],rp[BB];
int pos[N],cnt;
int v[N],c[N];
int idx[N];
int pnt[BB],lc[BB][BB]; 
ll svc[BB][BB],sv[BB][BB];
int p[BB],q[BB];
ll ans[BB];
#define Size(x) (rp[x]-lp[x]+1)
inline ll Sum(int x)
{
	return sv[x][p[x]]*q[x]-svc[x][p[x]]+(svc[x][pnt[x]]-svc[x][p[x]])-(sv[x][pnt[x]]-sv[x][p[x]])*q[x];
}
ll Ans=0;
int _c[512];
int tmp[N],t2[N];
void rsort(int l,int r)
{
	for (int i=l;i<=r;i++) c[i]+=50000;

	for (int i=0;i<512;i++) _c[i]=0;
	for (int i=l;i<=r;i++) _c[c[i]&511]++;
	for (int i=1;i<512;i++) _c[i]+=_c[i-1];
	for (int i=r;i>=l;i--) tmp[_c[c[i]&511]--]=i;

	for (int i=0;i<512;i++) _c[i]=0;
	for (int i=1;i<=r-l+1;i++) _c[c[tmp[i]]>>9]++;
	for (int i=1;i<512;i++) _c[i]+=_c[i-1];
	for (int i=r-l+1;i;i--) t2[_c[c[tmp[i]]>>9]--]=tmp[i];

	for (int i=l;i<=r;i++) idx[i]=t2[i-l+1],c[i]-=50000;
}
void Build(int x)
{
	rsort(lp[x],rp[x]);
	Ans-=ans[x]; pnt[x]=0;
	for (int j=lp[x];j<=rp[x];j++)
		if (j==lp[x] || c[idx[j]]!=c[idx[j-1]])
		{
			pnt[x]++,lc[x][pnt[x]]=c[idx[j]];
			sv[x][pnt[x]]=sv[x][pnt[x]-1]+v[idx[j]];
			svc[x][pnt[x]]=svc[x][pnt[x]-1]+(ll)v[idx[j]]*c[idx[j]];
		}
		else
		{
			sv[x][pnt[x]]+=v[idx[j]];
			svc[x][pnt[x]]+=(ll)v[idx[j]]*c[idx[j]];
		}
	q[x]=0;
	p[x]=upper_bound(lc[x]+1,lc[x]+pnt[x]+1,0)-lc[x]-1;
	Ans+=(ans[x]=Sum(x));
}

void Reb(int x,int l,int r,int t)
{
	if (l>r) return;
	for (int i=lp[x];i<=rp[x];i++) c[i]-=q[x];
	for (int i=l;i<=r;i++) c[i]+=t;
	Build(x);
}
void Add(int l,int r,int t)
{
	int lb=pos[l],rb=pos[r];
	if (lb==rb)
	{
		Reb(lb,l,r,t);
		return;
	}
	Reb(lb,l,rp[lb],t);
	Reb(rb,lp[rb],r,t);
	for (int i=lb+1;i<rb;i++)
	{
		Ans-=ans[i];
		q[i]-=t;
		while (p[i]+1<=pnt[i] && lc[i][p[i]+1]<=q[i]) p[i]++;
		while (p[i]>0 && lc[i][p[i]]>q[i]) p[i]--; 
		Ans+=(ans[i]=Sum(i));
	}
}

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) 
		scanf("%d",&a[i]),sx[++icnt]=a[i];
	for (int i=1;i<=n;i++) 
		scanf("%d",&b[i]),sx[++icnt]=b[i];
	scanf("%d",&Q); 
	for (int i=1;i<=Q;i++) 
		scanf("%d%d",&x[i],&y[i]),sx[++icnt]=y[i];
	sort(sx+1,sx+icnt+1); 
	icnt=unique(sx+1,sx+icnt+1)-sx-1;
	for (int i=1;i<icnt;i++) 
		v[i]=sx[i+1]-sx[i];
	B=sqrt(icnt);
	for (int i=1;i<=icnt;i++) 
		pos[i]=(i-1)/B+1; cnt=pos[icnt];
	for (int i=1;i<=cnt;i++) 
		lp[i]=(i-1)*B+1,rp[i]=i*B; rp[cnt]=icnt;
	for (int i=1;i<=n;i++) 
		a[i]=Bin(a[i]),b[i]=Bin(b[i]),c[a[i]]++,c[b[i]]--;
	for (int i=1;i<=icnt;i++) 
		c[i]+=c[i-1];
	for (int i=1;i<=cnt;i++)
		Build(i);
	printf("%lld\n",Ans);
	for (int i=1;i<=Q;i++)
	{
		y[i]=Bin(y[i]);
		if (y[i]<a[x[i]])
			Add(y[i],a[x[i]]-1,1),a[x[i]]=y[i];
		else if (a[x[i]]<y[i])
			Add(a[x[i]],y[i]-1,-1),a[x[i]]=y[i];
		printf("%lld\n",Ans);
	}
	return 0;
}

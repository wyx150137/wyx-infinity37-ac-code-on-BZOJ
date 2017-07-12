
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 1e5+5;
struct E
{int next,to,val;}e[N<<1];
int head[N],tot;
int dis[N],dfn[N],Dfn,size[N];
void add(int x,int y,int f)
{
	e[++tot].to = y;e[tot].next = head[x];e[tot].val = f;head[x] = tot;
}
void dfs(int x)
{
	dfn[x] = ++Dfn;
	size[x] = 1;
	for(int i = head[x];i;i=e[i].next)
	{
		dis[e[i].to] = dis[x]+e[i].val;
		dfs(e[i].to);
		size[x]+=size[e[i].to];
	}
}
const int M = 2e7+5;
const int Bs = 510;
int B;
int n,Q,len;
int pos[N],_a[N],lb[Bs],rb[Bs],mx[Bs],mn[Bs],Size[Bs],cnt,tag[N];
int qo[N],ql[N],qr[N],qk[N];
int F[M];
#define f(i,j) (*(F+Size[(i)-1]+(j)-mn[(i)]))
void Build()
{
	cnt = 0;
	B = sqrt(n);
	for(int i = 1;i<= n;i+=B)
		lb[++cnt] = i,rb[cnt] = i+B-1;
	rb[cnt] = n;
	for(int i = 1;i<= cnt;i++)
		for(int j = lb[i];j<= rb[i];j++)pos[j] = i;
	for(int i = 1;i<= cnt;i++)mx[i]=-1<<30,mn[i]=1<<30;
	for(int i = 1;i<= n;i++)
		mx[pos[i]] = max(mx[pos[i]],_a[i]),mn[pos[i]] = min(mn[pos[i]],_a[i]);
	for(int i = 1;i<= Q;i++)
		if(qo[i]==2)
			mx[pos[ql[i]]]+=qk[i],mx[pos[qr[i]]]+=qk[i];
	for(int i = 1;i<= cnt;i++)
		mn[i]--,Size[i] = Size[i-1]+mx[i]-mn[i];
	for(int i = 1;i<= n;i++)f(pos[i],_a[i])++;
	for(int i = 1;i<= cnt;i++)
		for(int j = mn[i]+2;j<=mx[i];j++)
			f(i,j)+=f(i,j-1);
}
void Add(int l,int r,int d)
{
	int L = pos[l],R = pos[r];
	if(L==R)
	{
		for(int i = l;i<= r;i++)
		{
			for(int j = _a[i]+tag[L];j<= _a[i]+tag[L]+d-1;j++)
				f(L,j)--;
			_a[i]+=d;
		}
		return ;
	}
	for (int i=L+1;i<R;i++) tag[i]+=d,mn[i]+=d;
	for (int i=l;i<=rb[L];i++)
	{
		for (int j=_a[i]+tag[L];j<=_a[i]+tag[L]+d-1;j++)
			f(L,j)--;
		_a[i]+=d;
	}
	for (int i=lb[R];i<=r;i++)
	{
		for (int j=_a[i]+tag[R];j<=_a[i]+tag[R]+d-1;j++)
			f(R,j)--;
		_a[i]+=d;
	}
}
int tmp[N],pnt;

int getans(int l,int r,int K)
{
	if (K>r-l+1) return -1;
	int lbd=pos[l],rbd=pos[r];
	if (lbd==rbd)
	{
		pnt=0;
		for (int i=l;i<=r;i++) tmp[++pnt]=_a[i]+tag[lbd];
		nth_element(tmp+1,tmp+K,tmp+pnt+1);
		return tmp[K];
	}
	pnt=0;
	for (int i=l;i<=rb[lbd];i++) tmp[++pnt]=_a[i]+tag[lbd];
	for (int i=lb[rbd];i<=r;i++) tmp[++pnt]=_a[i]+tag[rbd];
	sort(tmp+1,tmp+pnt+1);
	int L=-1,R=(n+Q)*len;
	while (L+1<R)
	{
		int MID=(L+R)>>1;tot=0;
		if (L<100000 && R>100000) MID=100000;
		for (int i=lbd+1;i<rbd;i++) 
			if (MID>mn[i]) 
				tot+=f(i,min(MID,mx[i]+tag[i]));
		tot+=upper_bound(tmp+1,tmp+pnt+1,MID)-tmp-1;
		if (tot<K)
			L=MID;
		else
			R=MID;
	}
	return R;
}
int main()
{
	scanf("%d%d%d",&n,&Q,&len);
	int p,d;
	for(int i = 2;i<= n;i++)
	{
		scanf("%d%d",&p,&d);
		add(p,i,d);
	}
	dfs(1);
	for(int i = 1;i<= n;i++)_a[dfn[i]]=dis[i];
	for(int i = 1;i<= Q;i++)
	{
		scanf("%d%d%d",&qo[i],&p,&qk[i]);
		ql[i] = dfn[p],qr[i] = dfn[p]+size[p]-1;
	}
	Build();
	for(int i = 1;i<= Q;i++)
		if(qo[i]==2)Add(ql[i],qr[i],qk[i]);
		else printf("%d\n",getans(ql[i],qr[i],qk[i]));
	return 0;
}

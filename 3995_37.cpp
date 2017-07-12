
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
const int N = 6e4+5;
int a[N][2],b[N],n,m;
struct data
{
	int l,r,sum;
	int mx,cnt;
	int lmx,rmx,lv,rv;
	data(){}
	data(int pos)
	{
		int x = b[pos];
		l = r = pos;
		sum = x;
		mx = 0,cnt=1;
		lmx=rmx=lv=rv=x;
	}
	friend data operator+(const data &x,const data &y)
	{
		data res;
		res.l = x.l,res.r = y.r;
		res.mx = max(max(a[x.r][0],a[x.r][1]),max(x.mx,y.mx));
		int max_val = max(max(a[x.r][0],a[x.r][1]),max(x.rmx,y.lmx));
		res.sum = x.sum+y.sum+a[x.r][0]+a[x.r][1]-max_val;
		res.cnt = x.cnt+y.cnt;
		res.lv = x.lv,res.rv = y.rv;
		res.lmx = x.lmx,res.rmx = y.rmx;
		if(x.rv==max_val)
		{
			res.cnt--;
			if(x.cnt==1)
			{
				res.lv = y.lv;
				res.lmx = max(max(x.mx,y.lmx),max(a[x.r][0],a[x.r][1]));
			}
		}else if(y.lv==max_val)
		{
			res.cnt--;
			if(y.cnt==1)
			{
				res.rv = x.rv;
				res.rmx = max(max(y.mx,x.rmx),max(a[x.r][0],a[x.r][1]));
			}
		}
		return res;
	}
}tr[N<<3];
void build(int p,int l,int r)
{
	if(l==r)
	{
		tr[p] = data(l);
		return ;
	}
	int mid = (l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	tr[p] = tr[p<<1]+tr[p<<1|1];
}
void update1(int p,int l,int r,int pos)
{
	if(l==r)
	{
		tr[p] = data(l);
		return ;
	}
	int mid = (l+r)>>1;
	if(pos<=mid)update1(p<<1,l,mid,pos);
	else update1(p<<1|1,mid+1,r,pos);
	tr[p] = tr[p<<1]+tr[p<<1|1];
}
void update2(int p,int l,int r,int pos)
{
	int mid = (l+r)>>1;
	if(mid==pos)
	{
		tr[p] = tr[p<<1]+tr[p<<1|1];
		return ;
	}
	if(pos<=mid)
		update2(p<<1,l,mid,pos);
	else update2(p<<1|1,mid+1,r,pos);
	tr[p] = tr[p<<1]+tr[p<<1|1];
}
data getans(int p,int l,int r,int a,int b)
{
	if(l>=a&&r<=b)return tr[p];
	int mid = (l+r)>>1;
	if(b<=mid)return getans(p<<1,l,mid,a,b);
	else if(a>mid)return getans(p<<1|1,mid+1,r,a,b);
	else return getans(p<<1,l,mid,a,b)+getans(p<<1|1,mid+1,r,a,b);
}
void update(int x0,int y0,int x1,int y1,int z)  
{  
    if(y0==y1)//修改了一条竖边  
    {  
        b[y0]=z;  
        update1(1,1,n,y0);  
    }  
    else//修改了一条横边  
    {  
        if(y0>y1) swap(y0,y1);  
        a[y0][x0-1]=z; 
        update2(1,1,n,y0); 
    }  
}  
int main()
{
	scanf("%d%d",&n,&m);
	for(int j = 0;j<2;j++)
		for(int i = 1;i<= n-1;i++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	build(1,1,n);
	char opt[3];
	int x0,y0,x1,y1,w;
	while(m--)
	{
		scanf("%s",opt);
		if(opt[0]=='C')
		{
			scanf("%d%d%d%d%d",&x0,&y0,&x1,&y1,&w);
			update(x0,y0,x1,y1,w);
		}else
		{
			scanf("%d%d",&x0,&y0);
			data ans = getans(1,1,n,x0,y0);
			printf("%d\n",ans.sum);
		}
	}
	return 0;
}
